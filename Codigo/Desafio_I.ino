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

// Función para clasificar la señal
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
Señal* generarSeñal(int tamano, string tipo) {
    Señal* señal = new Señal;
    señal->tamano = tamano;
    señal->datos = new float[tamano];

    srand(time(0));

    if (tipo == "senoidal") {
        for (int i = 0; i < tamano; ++i) {
            señal->datos[i] = sin(2 * M_PI * i / tamano);
        }
    } else if (tipo == "triangular") {
        for (int i = 0; i < tamano; ++i) {
            señal->datos[i] = 2.0 * fabs((i / float(tamano / 2)) - 1) - 1;
        }
    } else if (tipo == "cuadrada") {
        for (int i = 0; i < tamano; ++i) {
            señal->datos[i] = (i % 2 == 0) ? 1.0 : -1.0;
        }
    }

    return señal;
}

int main() {
    // Generar una señal de prueba
    Señal* miSeñal = generarSeñal(100, "senoidal");
    
    for (int i=0;i<100;i++){
        printf("%f",*miSeñal[i].datos);
    }

    // Clasificar la señal
    string tipoSeñal = clasificarSeñal(miSeñal);
    cout << "Tipo de señal: " << tipoSeñal << endl;

    // Liberar la memoria dinámica
    delete[] miSeñal->datos;
    delete miSeñal;

    return 0;
}
