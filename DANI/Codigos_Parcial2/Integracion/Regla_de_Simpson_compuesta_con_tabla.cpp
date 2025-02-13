// -----------------------------------Regla de Simpson - Compuesta-----------------------------------
// (con tabla)
/*
Este codigo trabaja con una tabla de datos equiespaciada. 
Si no se cuenta con una, se debe hacer spline cubica primero.
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int p = 5; // cantidad de puntos a emplear
const int n = p-1; // cantidad de subintervalos a emplear // debe ser un nro par

int main(int argc, char *argv[])
{
    // tabla de datos EQUIESPACIADA
    double x[p] = {1, 1.4, 1.8, 2.2, 2.6};
    double y[p] = {2.1, 3.45, 4.80, 6.15, 7.5};
    
    double I = 0; // integral aproximada

    // auxiliares
    double h = (double) (x[1] - x[0]); // asume que la tabla esta equiespaciada
    double suma_impares = 0, suma_pares = 0; 

    // calculo de I
    for(int i = 1; i <= (n-1); i++){ // i impares
        if(i % 2 == 1){
            suma_impares += y[i];
        }
    }
    for(int i = 2; i <= (n-2); i++){ // i pares
        if(i % 2 == 0){
            suma_pares += y[i];
        }
    }
    I = (double) h/3 * (y[0] + y[n] + 4 * suma_impares + 2 * suma_pares);

    // impresion de resultados
    cout << "Valor aproximado de la integral de f(x): I = " << I << endl;

    return 0;
}