// ------------------------- Regla del trapecio compuesta -------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n = 5; // cantidad de puntos empleada

double f(double x){ // funcion a definir
    return (pow(x,2)+1); // I_exacto = 12
}

int main(int argc, char *argv[])
{
    double a = 0, b = 3; // limites de integracion 
    double I = 0; // resultado de la integral

    // auxiliares
    double h = (double) (b-a) / n; // distancia entre puntos
    double x_i = 0; // guarda puntos intermedios
    double suma = 0;
    
    // calculo de I
    for(int i = 1; i < n; i++){ // acumula f(x_i)
        x_i = a + i * h;
        suma += f(x_i);
    }
    I = (double) h/2 * (f(a) + f(b) + 2 * suma);

    // impresion de resultados
    cout << "Valor aproximado de la integral de f(x): I = " << I << endl;

    return 0;
}