// C++ code
//
#include <Adafruit_LiquidCrystal.h>

const short pinAnalogEntradaGen = A0;
const short pinPulsador1 = 2;
const short pinPulsador2 = 3;
short max_val;
short min_val;
short cruces_cero = 0;
// float triangular[2]={0.89721627, 1};
// float senoidal[2]={0.96631579, 1};
short posicionCresta = 0;

Adafruit_LiquidCrystal lcd_1(0);

void calcularDiferenciasCrestas(short *datos)
{
    float dato1 = ((float)datos[posicionCresta] - (float)min_val) / ((float)max_val - (float)min_val);
    float dato2 = ((float)datos[posicionCresta - 1] - (float)min_val) / ((float)max_val - (float)min_val);
    Serial.println("RESTA:");
    Serial.println(dato1);
    Serial.println("RESTA1:");
    Serial.println(dato2);
    Serial.println("RESTA2:");
    Serial.println((dato1 - dato2));
    if ((dato1 - dato2) < 0.11)
    {
        lcd_1.setCursor(0, 0);
        lcd_1.print("                ");
        lcd_1.setCursor(0, 0);
        lcd_1.print("Senal senoidal");
    }
    else if ((dato1 - dato2) < 0.26)
    {
        lcd_1.setCursor(0, 0);
        lcd_1.print("                ");
        lcd_1.setCursor(0, 0);
        lcd_1.print("Senal triangular");
    }
    else
    {
        lcd_1.setCursor(0, 0);
        lcd_1.print("                ");
        lcd_1.setCursor(0, 0);
        lcd_1.print("Senal no identificada");
    }
}

float medirAmplitud(short *datos, short tamano)
{

    max_val = datos[0];
    min_val = datos[0];

    for (int i = 1; i < tamano; i++)
    {

        if (datos[i] > max_val)
        {
            max_val = datos[i];
            posicionCresta = i;
        }
        if (datos[i] < min_val)
        {
            min_val = datos[i];
        }
    }

    float max_val_ = (max_val / 1023.0) * 5;
    float min_val_ = (min_val / 1023.0) * 5;

    return (float)(max_val_ - min_val_); // / 2; // Amplitud en Voltios
}

float calcularFrecuencia(short *senal, short tamano)
{
    cruces_cero = 0;
    float media = 0;

    // Calcular la media de la señal
    for (int i = 0; i < tamano; i++)
    {
        media += senal[i];
    }
    media /= tamano;

    // Contar cruces por cero
    for (int i = 1; i < tamano; i++)
    {
        if ((senal[i - 1] < media && senal[i] >= media) ||
            (senal[i - 1] > media && senal[i] <= media))
        {
            cruces_cero++;
        }
    }

    // Calcular frecuencia
    float periodo = (tamano * 0.01) / (cruces_cero); //(cruces_cero / 2.0);
    return 1.0 / periodo;
}

void clasificarSenal(short *datos, short tamano)
{
    int ascensos = 0, descensos = 0, saltos = 0;
    // float sumaDiferencias=0.0;

    for (int i = 1; i < tamano; ++i)
    {
        float dif = datos[i] - datos[i - 1];
        // sumaDiferencias += abs(dif);
        //  Determinamos si hay un ascenso, descenso o salto
        if (dif > 0)
        {
            ascensos++;
        }
        else if (dif < 0)
        {
            descensos++;
        }

        // Detectamos saltos grandes (señal cuadrada)
        if (abs(dif) > 1.0)
        { // Un umbral arbitrario para distinguir saltos
            saltos++;
        }
    }

    Serial.println("ASCENSOS:");
    Serial.println(ascensos);
    Serial.println("DESCENSOS: ");
    Serial.println(descensos);
    Serial.println("SALTOS: ");
    Serial.println(saltos);
    Serial.println("TAMANO: ");
    Serial.println(tamano);
    // Serial.println("PROMEDIO: ");
    // Serial.println(sumaDiferencias/(tamano-1));
    Serial.println("MAX: ");
    Serial.println(max_val);
    Serial.println("MIN: ");
    Serial.println(min_val);
    Serial.println("CRUCES 0: ");
    Serial.println(cruces_cero);

    // Clasificar la señal en función de las características
    if (ascensos == descensos || abs(ascensos - descensos) == 1)
    {
        lcd_1.setCursor(0, 0);
        lcd_1.print("                ");
        lcd_1.setCursor(0, 0);
        lcd_1.print("Senal cuadrada");
        // Serial.print( "Senal cuadrada");
    } /*else if (ascensos == descensos) {
       lcd_1.setCursor(0, 0);
        lcd_1.print("Senal senoidal");
        //Serial.print( "Senal senoidal");
    } else if (ascensos != descensos) {
       lcd_1.setCursor(0, 0);
        lcd_1.print("Senal triangular");
        //Serial.print( "Senal triangular");
    }*/
    else
    {
        // Serial.print("Senal no identificada");
        // lcd_1.setCursor(0, 0);
        // lcd_1.print("Senal no identificada");
        calcularDiferenciasCrestas(datos);
    }
}

void setup()
{
    pinMode(pinPulsador1, INPUT);
    pinMode(pinPulsador2, INPUT);

    Serial.begin(9600);
    lcd_1.begin(16, 2);

    lcd_1.print("Hello, welcome");
}

void loop()
{
    // Lectura de pulsadores
    /*short estadoPulsador1 = digitalRead(pinPulsador1);
    Serial.println (estadoPulsador1);
    //Serial.println (estadoPulsador2);
    lcd_1.setCursor(0, 1);
    lcd_1.print(seconds);
    lcd_1.setBacklight(1);
    delay(500); // Wait for 500 millisecond(s)
    lcd_1.setBacklight(0);
    delay(500); // Wait for 500 millisecond(s)
    seconds += 1;
    if(estadoPulsador1== HIGH){
      for(short i=0;i<700;i++){

        short valorGenerador = analogRead(pinAnalogEntradaGen);
        datos[i]=valorGenerador;
        short estadoPulsador2 = digitalRead(pinPulsador2);
        if(estadoPulsador2== HIGH){
          break;
          Serial.println("Prueba: "+String(datos[i])+ " pos: "+String(i));
      }
    }
    }*/

    // Serial.println(valorGenerador);
    //  Lectura de pulsadores
    short *datos = new short[470];
    short i = 0;
    bool siEntra = false;
    short estadoPulsador1 = digitalRead(pinPulsador1);
    // Serial.println(estadoPulsador1);

    if (estadoPulsador1 == HIGH)
    {

        for (; i < 470; i++)
        {
            short valorGenerador = analogRead(pinAnalogEntradaGen);
            datos[i] = valorGenerador;
            Serial.println(datos[i]);
            // Leer el segundo pulsador durante el ciclo
            short estadoPulsador2 = digitalRead(pinPulsador2);
            if (estadoPulsador2 == HIGH)
            {

                // Salir del ciclo si se presiona el segundo pulsador

                lcd_1.setCursor(0, 1);
                lcd_1.print(medirAmplitud(datos, i));
                lcd_1.print("V, ");
                lcd_1.print(calcularFrecuencia(datos, i));
                lcd_1.print("HZ");
                clasificarSenal(datos, i);
                // Serial.println(medirAmplitud(datos,i));
                siEntra = true;

                break;
            }
        }
        if (siEntra == false)
        {
            lcd_1.setCursor(0, 1);
            lcd_1.print(medirAmplitud(datos, i));
            lcd_1.print("V, ");
            lcd_1.print(calcularFrecuencia(datos, i));
            lcd_1.print("HZ");
            clasificarSenal(datos, i);
        }
    }

    // Agregar un pequeño retraso para evitar saturar la comunicación serial
    delay(100);
    delete[] datos;
}
