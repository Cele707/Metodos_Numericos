// -----------------------------------Regla de Simpson - Compuesta-----------------------------------
// (con funcion)

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.14159 // para ejemplo

using namespace std;

const int p = 3; // cantidad de puntos a emplear // debe ser impar
const int n = p-1; // cantidad de subintervalos a emplear // debe ser un nro par

double f(double x){ // funcion a definir 
    return(2 * sin(x) + cos(x));
}

int main(int argc, char *argv[])
{
    double a = 0, b = pi/2; // limites de integracion
    double I = 0; // integral aproximada

    // auxiliares
    double h = (double) (b-a)/n;
    double x_i = 0;
    double suma_impares = 0, suma_pares = 0; 

    // calculo de I
    for(int i = 1; i <= (n-1); i++){ // i impares
        if(i % 2 == 1){
            x_i = a + i * h;
            suma_impares += f(x_i);
        }
    }
    for(int i = 2; i <= (n-2); i++){ // i pares
        if(i % 2 == 0){
            x_i = a + i * h;
            suma_pares += f(x_i);
        }
    }
    I = (double) h/3 * (f(a) + f(b) + 4 * suma_impares + 2 * suma_pares);

    // impresion de resultados
    cout << "Valor aproximado de la integral de f(x): I = " << I << endl;

    return 0;
}