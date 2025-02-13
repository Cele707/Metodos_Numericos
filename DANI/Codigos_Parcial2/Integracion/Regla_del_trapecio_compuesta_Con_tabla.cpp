// ------------------------- Regla del trapecio compuesta -------------------------
// (con funcion)
/*
Este codigo trabaja con una tablade datos equiespaciada. 
Si no se cuenta con una, se debe hacer spline cubica primero.
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n = 5; // cantidad de puntos empleada

int main(int argc, char *argv[])
{
    // tabla de datos EQUIESPACIADA
    double x[n] = {1.0, 1.4, 1.8, 2.2, 2.6}; // vector de x de datos
    double y[n] = {2.1, 3.45, 4.80, 6.15, 7.5}; // vector de f(x) de datos
    
    double h = x[1] - x[0]; // se supone que la tabla esta equiespaciada
    double I = 0; // resultado de la integral
    double suma = 0;// auxiliar

    // calculo de I
    for(int i = 1; i < (n-1); i++){ // acumula f(x_i)
        suma += y[i];
    }
    I = (double) h/2 * (y[0] + y[n-1] + 2 * suma);

    // impresion de resultados
    cout << "Valor aproximado de la integral de f(x): I = " << I << endl;

    return 0;
}