#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura dinámica para almacenar la señal
struct Señal {
    float* datos;  // Puntero dinámico para los valores de la señal
    int tamano;    // Tamaño de la señal
};

string clasificarSeñal(Señal* señal) {
    int ascensos = 0, descensos = 0, saltos = 0;

    for (int i = 1; i < señal->tamano; ++i) {
        float dif = señal->datos[i] - señal->datos[i - 1];

        // Determinamos si hay un ascenso, descenso o salto
        if (dif > 0) {
            ascensos++;
        } else if (dif < 0) {
            descensos++;
        }

        // Detectamos saltos grandes (señal cuadrada)
        if (fabs(dif) > 1.0) {  // Un umbral arbitrario para distinguir saltos
            saltos++;
        }
    }

    // Clasificar la señal en función de las características
    if (saltos > ascensos + descensos) {
        return "Señal cuadrada";
    } else if (ascensos == descensos) {
        return "Señal senoidal";
    } else if (ascensos != descensos) {
        return "Señal triangular";
    }

    return "Señal no identificada";
}

// Función para generar una señal de prueba
Señal* generarSeñal(int tamano, std::string tipo) {
    Señal* señal = new Señal;
    señal->tamano = tamano;
    señal->datos = new float[tamano];

    // Asegurarse de que el tamaño es mayor que cero
    if (tamano <= 0) {
        std::cerr << "El tamaño de la señal debe ser mayor que 0." << std::endl;
        return nullptr;
    }

    // Inicializar la semilla para números aleatorios (si es necesario)
    srand(time(0));

    if (tipo == "senoidal") {
        for (int i = 0; i < tamano; ++i) {
            señal->datos[i] = sin(2 * M_PI * i / float(tamano));  // Señal senoidal
        }
    }
    // Generar señal triangular
    else if (tipo == "triangular") {
        for (int i = 0; i < tamano; ++i) {
            float t = float(i) / (tamano - 1);  // Normalización entre 0 y 1
            if (t < 0.5) {
                señal->datos[i] = 4 * t - 1;   // Subida en la primera mitad
            } else {
                señal->datos[i] = 3 - 4 * t;   // Bajada en la segunda mitad
            }
        }
    }
    // Generar señal cuadrada
    else if (tipo == "cuadrada") {
        for (int i = 0; i < tamano; ++i) {
            señal->datos[i] = (i % (tamano / 2) < (tamano / 4)) ? 1.0 : -1.0;
        }
    }

    return señal;
}

int main() {
    // Generar una señal de prueba
    Señal* miSeñal = generarSeñal(100, "triangular");
    printf("[");
    for (int i = 0; i < 100; i++) {
        printf("%f, ", miSeñal->datos[i]);  // Acceder a los datos de la señal correctamente
    }
    printf("]\n");


    // Clasificar la señal
    string tipoSeñal = clasificarSeñal(miSeñal);
    cout << "Tipo de señal: " << tipoSeñal << endl;

    // Liberar la memoria dinámica
    delete[] miSeñal->datos;
    delete miSeñal;

    return 0;
}

// lectura de pulsadores

// Definición de pines
const int botonPin2 = 2;   // Pin del pulsador 1
const int botonPin3 = 3;   // Pin del pulsador 2

void setup() {
  // Configurar los pines de los botones como entradas
  pinMode(botonPin2, INPUT);
  pinMode(botonPin3, INPUT);

  // Iniciar el puerto serie para la depuración
  Serial.begin(9600);
}

void loop() {
  // Leer el estado de los pulsadores
  int estadoBoton2 = digitalRead(botonPin2);
  int estadoBoton3 = digitalRead(botonPin3);

  // Imprimir el estado de los botones en el monitor serie
  Serial.print("Boton 2: ");
  Serial.print(estadoBoton2);
  Serial.print(" | Boton 3: ");
  Serial.println(estadoBoton3);

  // Si se presiona el botón 2 o el botón 3, encender el LED
  if (estadoBoton2 == HIGH || estadoBoton3 == HIGH) {
    Serial.print("Boton 2 o 3: ");
  } else {
    Serial.print("Sin Boton 2: o 3 ");
  }

  // Pequeño retardo para evitar rebotes
  delay(50);
}


// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
const short pinAnalogEntradaGen = A0;
const short pinPulsador1=2;
const short pinPulsador2=3;

Adafruit_LiquidCrystal lcd_1(0);


float medirAmplitud(short* datos, short tamano) {
  
    short max_val = datos[0];
    short  min_val = datos[0];
   

    for (int i = 1; i<tamano ; i++) {
    
        
        if (datos[i] > max_val) {
            max_val = datos[i];
        }
        if (datos[i] < min_val) {
            min_val = datos[i];
          
        }
    }
   
 
  max_val = (max_val / 1023.0) * 5;
  min_val = (min_val / 1023.0) * 5;

    return (float)(max_val - min_val) / 2; // Amplitud en Voltios
}

void clasificarSenal(short* datos, short tamano) {
    int ascensos = 0, descensos = 0, saltos = 0;

    for (int i = 1; i < tamano; ++i) {
        float dif = datos[i] - datos[i - 1];

        // Determinamos si hay un ascenso, descenso o salto
        if (dif > 0) {
            ascensos++;
        } else if (dif < 0) {
            descensos++;
        }

        // Detectamos saltos grandes (señal cuadrada)
        if (abs(dif) > 1.0) {  // Un umbral arbitrario para distinguir saltos
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

    // Clasificar la señal en función de las características
    if (ascensos == descensos||abs(ascensos-descensos)==1) {
      lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal cuadrada");
        //Serial.print( "Senal cuadrada");
    } else if (ascensos == descensos) {
        Serial.print( "Senal senoidal");
    } else if (ascensos != descensos) {
        Serial.print( "Senal triangular");
    }else
    Serial.print("Senal no identificada");
}


void setup()
{
  pinMode(pinPulsador1, INPUT);
  pinMode(pinPulsador2, INPUT);
  
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  

  lcd_1.print("hello world");
  
}

void loop()
{
  //Lectura de pulsadores
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
  
  
  //Serial.println(valorGenerador);
  // Lectura de pulsadores
  short* datos=new short[600];
  short i = 0;
  short estadoPulsador1 = digitalRead(pinPulsador1);
  //Serial.println(estadoPulsador1);
  
  if (estadoPulsador1 == HIGH) {
    
    for (; i < 600; i++) {
      short valorGenerador = analogRead(pinAnalogEntradaGen);
      datos[i] = valorGenerador;
      Serial.println(datos[i]);
      // Leer el segundo pulsador durante el ciclo
      short estadoPulsador2 = digitalRead(pinPulsador2);
      if (estadoPulsador2 == HIGH) {
        // Salir del ciclo si se presiona el segundo pulsador
        clasificarSenal(datos,i);
        lcd_1.setCursor(0, 1);
  		lcd_1.print(medirAmplitud(datos,i));
        lcd_1.print("Hz");
        //Serial.println(medirAmplitud(datos,i));
        
        
        break;
      }
      
     
    }
    
    
  }
  
  // Agregar un pequeño retraso para evitar saturar la comunicación serial
  delay(100);
  delete[] datos;
}

// versión 16/09/2024
// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
const short pinAnalogEntradaGen = A0;
const short pinPulsador1=2;
const short pinPulsador2=3;
short max_val;
short  min_val;

Adafruit_LiquidCrystal lcd_1(0);


float medirAmplitud(short* datos, short tamano) {
  
     max_val = datos[0];
     min_val = datos[0];
   

    for (int i = 1; i<tamano ; i++) {
    
        
        if (datos[i] > max_val) {
            max_val = datos[i];
        }
        if (datos[i] < min_val) {
            min_val = datos[i];
          
        }
    }
   
 
  float max_val_ = (max_val / 1023.0) * 5;
  float min_val_ = (min_val / 1023.0) * 5;

    return (float)(max_val_ - min_val_) / 2; // Amplitud en Voltios
}

void clasificarSenal(short* datos, short tamano) {
    int ascensos = 0, descensos = 0, saltos = 0;
  float sumaDiferencias=0.0;

    for (int i = 1; i < tamano; ++i) {
        float dif = datos[i] - datos[i - 1];
		sumaDiferencias += abs(dif);
        // Determinamos si hay un ascenso, descenso o salto
        if (dif > 0) {
            ascensos++;
        } else if (dif < 0) {
            descensos++;
        }

        // Detectamos saltos grandes (señal cuadrada)
        if (abs(dif) > 1.0) {  // Un umbral arbitrario para distinguir saltos
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
  Serial.println("PROMEDIO: ");
  Serial.println(sumaDiferencias/(tamano-1));
  Serial.println("MAX: ");
  Serial.println(max_val);
  Serial.println("MIN: ");
  Serial.println(min_val);

    // Clasificar la señal en función de las características
    if (ascensos == descensos||abs(ascensos-descensos)==1) {
      lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal cuadrada");
        //Serial.print( "Senal cuadrada");
    } else if (ascensos == descensos) {
        Serial.print( "Senal senoidal");
    } else if (ascensos != descensos) {
        Serial.print( "Senal triangular");
    }else
    Serial.print("Senal no identificada");
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
  //Lectura de pulsadores
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
  
  
  //Serial.println(valorGenerador);
  // Lectura de pulsadores
  short* datos=new short[500];
  short i = 0;
  short estadoPulsador1 = digitalRead(pinPulsador1);
  //Serial.println(estadoPulsador1);
  
  if (estadoPulsador1 == HIGH) {
    
    for (; i < 500; i++) {
      short valorGenerador = analogRead(pinAnalogEntradaGen);
      datos[i] = valorGenerador;
      Serial.println(datos[i]);
      // Leer el segundo pulsador durante el ciclo
      short estadoPulsador2 = digitalRead(pinPulsador2);
      if (estadoPulsador2 == HIGH) {
        // Salir del ciclo si se presiona el segundo pulsador
        
        lcd_1.setCursor(0, 1);
  		lcd_1.print(medirAmplitud(datos,i));
        lcd_1.print("V");
        clasificarSenal(datos,i);
        //Serial.println(medirAmplitud(datos,i));
        
        
        break;
      }
      
     
    }
    
    
  }
  
  // Agregar un pequeño retraso para evitar saturar la comunicación serial
  delay(100);
  delete[] datos;
}



/// prueba senoidal y triangular usando la varianza 
const int TAMANO_SENAL = 40; // Tamaño de la señal de entrada

// Función para clasificar la señal
String clasificarSenal(float* senal, int tamano) {
  // Calculamos la primera y segunda derivada
  float primera_derivada[TAMANO_SENAL - 1];
  float segunda_derivada[TAMANO_SENAL - 2];
  
  for (int i = 0; i < tamano - 1; i++) {
    primera_derivada[i] = senal[i+1] - senal[i];
  }
  
  for (int i = 0; i < tamano - 2; i++) {
    segunda_derivada[i] = primera_derivada[i+1] - primera_derivada[i];
  }
  
  // Contamos los cruces por cero de la segunda derivada
  int cruces_cero = 0;
  for (int i = 1; i < tamano - 2; i++) {
    if ((segunda_derivada[i-1] < 0 && segunda_derivada[i] > 0) || 
        (segunda_derivada[i-1] > 0 && segunda_derivada[i] < 0)) {
      cruces_cero++;
    }
  }
  
  // Calculamos la varianza de la segunda derivada
  float media = 0;
  for (int i = 0; i < tamano - 2; i++) {
    media += abs(segunda_derivada[i]);
  }
  media /= (tamano - 2);
  
  float varianza = 0;
  for (int i = 0; i < tamano - 2; i++) {
    varianza += pow(abs(segunda_derivada[i]) - media, 2);
  }
  varianza /= (tamano - 2);
  
  // Clasificamos basándonos en los cruces por cero y la varianza
  if (cruces_cero <= 2 && varianza < 0.1) {
    return "Triangular";
  } else {
    return "Senoidal";
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Ejemplo de uso (reemplazar con la lectura real de la señal)
  float senal[TAMANO_SENAL] = {867,823,777,733,690,647,598,550,503,493,514,547,587,633,681,727,773,817,860,905,953,950,922,884,843,802,757,709,661,615,569,525,486,499,532,574,617,661,705,746};
  
  String resultado = clasificarSenal(senal, TAMANO_SENAL);
  Serial.println("La señal es: " + resultado);
  
  delay(5000); // Espera 5 segundos antes de la siguiente clasificación
}



///pruebas usando desviación estándar para clasificar senoidal y triangular
const int TAMANO_SENAL = 40; // Tamaño de la señal de entrada

// Función para calcular la desviación estándar
float calcularDesviacionEstandar(float* arr, int tamano) {
  float suma = 0.0, media, desviacionEstandar = 0.0;
  int i;
  for(i = 0; i < tamano; ++i) {
    suma += arr[i];
  }
  media = suma / tamano;
  for(i = 0; i < tamano; ++i) {
    desviacionEstandar += pow(arr[i] - media, 2);
  }
  return sqrt(desviacionEstandar / tamano);
}

// Función para clasificar la señal
String clasificarSenal(float* senal, int tamano) {
  // Calculamos la primera derivada
  float primera_derivada[TAMANO_SENAL - 1];
  for (int i = 0; i < tamano - 1; i++) {
    primera_derivada[i] = senal[i+1] - senal[i];
  }
  
  // Calculamos la segunda derivada
  float segunda_derivada[TAMANO_SENAL - 2];
  for (int i = 0; i < tamano - 2; i++) {
    segunda_derivada[i] = primera_derivada[i+1] - primera_derivada[i];
  }
  
  // Calculamos la desviación estándar de la primera y segunda derivada
  float std_primera = calcularDesviacionEstandar(primera_derivada, tamano - 1);
  float std_segunda = calcularDesviacionEstandar(segunda_derivada, tamano - 2);
  
  // Contamos los cambios de signo en la primera derivada
  int cambios_signo = 0;
  for (int i = 1; i < tamano - 1; i++) {
    if ((primera_derivada[i-1] > 0 && primera_derivada[i] < 0) || 
        (primera_derivada[i-1] < 0 && primera_derivada[i] > 0)) {
      cambios_signo++;
    }
  }
  
  // Clasificamos basándonos en las características calculadas
  if (cambios_signo <= 2 && std_segunda < 0.1 * std_primera) {
    return "Triangular";
  } else {
    return "Senoidal";
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Señal triangular de ejemplo
  float senal_triangular[TAMANO_SENAL] = {867,823,777,733,690,647,598,550,503,493,514,547,587,633,681,727,773,817,860,905,953,950,922,884,843,802,757,709,661,615,569,525,486,499,532,574,617,661,705,746};
  
  // Señal senoidal de ejemplo
  float senal_senoidal[TAMANO_SENAL] = {952,926,888,838,778,714,651,594,545,510,489,484,499,529,573,627,687,750,812,868,913,943,959,959,942,908,860,803,741,678,618,565,523,496,486,492,514,551,599,659};

  String resultado_triangular = clasificarSenal(senal_triangular, TAMANO_SENAL);
  String resultado_senoidal = clasificarSenal(senal_senoidal, TAMANO_SENAL);
  
  Serial.println("La señal triangular se clasifica como: " + resultado_triangular);
  Serial.println("La señal senoidal se clasifica como: " + resultado_senoidal);
  
  delay(5000); // Espera 5 segundos antes de la siguiente clasificación
}

//Ajustes agregando el cálculo de la frecuencia de la función
// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
const short pinAnalogEntradaGen = A0;
const short pinPulsador1=2;
const short pinPulsador2=3;
short max_val;
short  min_val;


Adafruit_LiquidCrystal lcd_1(0);


float medirAmplitud(short* datos, short tamano) {
  
     max_val = datos[0];
     min_val = datos[0];
   

    for (int i = 1; i<tamano ; i++) {
    
        
        if (datos[i] > max_val) {
            max_val = datos[i];
        }
        if (datos[i] < min_val) {
            min_val = datos[i];
          
        }
    }
   
 
  float max_val_ = (max_val / 1023.0) * 5;
  float min_val_ = (min_val / 1023.0) * 5;

    return (float)(max_val_ - min_val_);// / 2; // Amplitud en Voltios
}

float calcularFrecuencia(short* senal, short tamano) {
  int cruces_cero = 0;
  float media = 0;

  // Calcular la media de la señal
  for (int i = 0; i < tamano; i++) {
    media += senal[i];
  }
  media /= tamano;

  // Contar cruces por cero
  for (int i = 1; i < tamano; i++) {
    if ((senal[i-1] < media && senal[i] >= media) || 
        (senal[i-1] > media && senal[i] <= media)) {
      cruces_cero++;
    }
  }

  // Calcular frecuencia
  float periodo = (tamano * 0.01) / (cruces_cero ); //(cruces_cero / 2.0);
  return 1.0 / periodo;
}

void clasificarSenal(short* datos, short tamano) {
    int ascensos = 0, descensos = 0, saltos = 0;
  float sumaDiferencias=0.0;

    for (int i = 1; i < tamano; ++i) {
        float dif = datos[i] - datos[i - 1];
		sumaDiferencias += abs(dif);
        // Determinamos si hay un ascenso, descenso o salto
        if (dif > 0) {
            ascensos++;
        } else if (dif < 0) {
            descensos++;
        }

        // Detectamos saltos grandes (señal cuadrada)
        if (abs(dif) > 1.0) {  // Un umbral arbitrario para distinguir saltos
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
  Serial.println("PROMEDIO: ");
  Serial.println(sumaDiferencias/(tamano-1));
  Serial.println("MAX: ");
  Serial.println(max_val);
  Serial.println("MIN: ");
  Serial.println(min_val);
 
  
    // Clasificar la señal en función de las características
    if (ascensos == descensos||abs(ascensos-descensos)==1) {
      lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal cuadrada");
        //Serial.print( "Senal cuadrada");
    } else if (ascensos == descensos) {
       lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal senoidal");
        //Serial.print( "Senal senoidal");
    } else if (ascensos != descensos) {
       lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal triangular");
        //Serial.print( "Senal triangular");
    }else{
    //Serial.print("Senal no identificada");
      lcd_1.setCursor(0, 0);
  		lcd_1.print("Senal no identificada");
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
  //Lectura de pulsadores
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
 
    
  
  
  //Serial.println(valorGenerador);
  // Lectura de pulsadores
  short* datos=new short[500];
  short i = 0;
  short estadoPulsador1 = digitalRead(pinPulsador1);
  //Serial.println(estadoPulsador1);
  
  if (estadoPulsador1 == HIGH) {
   
    for (; i < 500; i++) {
      short valorGenerador = analogRead(pinAnalogEntradaGen);
      datos[i] = valorGenerador;
      Serial.println(datos[i]);
      // Leer el segundo pulsador durante el ciclo
      short estadoPulsador2 = digitalRead(pinPulsador2);
      if (estadoPulsador2 == HIGH) {
        
        
        // Salir del ciclo si se presiona el segundo pulsador
        
        lcd_1.setCursor(0, 1);
  		lcd_1.print(medirAmplitud(datos,i));
        lcd_1.print("V, ");
        lcd_1.print(calcularFrecuencia(datos,i));
        lcd_1.print("HZ");
        clasificarSenal(datos,i);
        //Serial.println(medirAmplitud(datos,i));
         
        
        break;
      }
      
     
    }
    
    
  }
  
  // Agregar un pequeño retraso para evitar saturar la comunicación serial
  delay(100);
  delete[] datos;
}



	