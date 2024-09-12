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
