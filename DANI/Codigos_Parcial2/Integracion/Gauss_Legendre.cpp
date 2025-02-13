// ------------------------- Integracion por Gauss-Legendre -------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n = 6; // cantidad maxima de datos

double f(double x){ // funcion a definir 
    return (log(pow(x,2) +1) - sin(x));
}

int main(int argc, char *argv[])
{
    double c[n] = {0}; // vector factores c_i
    double x[n] = {0}; // vector de puntos x_i
    double a = 1, b = 2; // limites de integracion

    int datos = 0; // cantidad de puntos a emplear;
    double I = 0; // resultado de la integral

    bool exit = false;

    cout << "Ingrese la cantidad de puntos que desea emplear: ";
    cin >> datos;

    // Asignacion de c_i y x_i en funcion de la cantidad de puntos
    switch(datos){
        case 2: // error en la 4ta derivada
            // carga de c 
            c[0] = 1.0000000;
            c[1] = 1.0000000;
            // carga de x
            x[0] = (-0.577350269);
            x[1] = 0.577350269;
            break;
        case 3: // error en la 6ta derivada
            // carga de c 
            c[0] = 0.5555556;
            c[1] = 0.8888889;
            c[2] = 0.5555556;
            // carga de x
            x[0] = (-0.774596669);
            x[1] = 0.0;
            x[2] = 0.774596669;
        case 4: // error en la 8va derivada
            // carga de c 
            c[0] = 0.3478548;
            c[1] = 0.6521452;
            c[2] = 0.6521452;
            c[3] = 0.3478548;
            // carga de x
            x[0] = (-0.861136312);
            x[1] = (-0.339981044);
            x[2] = 0.339981044;
            x[3] = 0.861136312;
            break;
        case 5: // error en la 10ma derivada
            // carga de c 
            c[0] = 0.2369269;
            c[1] = 0.4786287;
            c[2] = 0.5688889;
            c[3] = 0.4786287;
            c[4] = 0.2369269;
            // carga de x
            x[0] = (-0.906179846);
            x[1] = (-0.538469310);
            x[2] = 0.0;
            x[3] = 0.538469310;
            x[4] = 0.906179846;
            break;
        case 6: // error en la 12va derivada
            // carga de c 
            c[0] = 0.1713245;
            c[1] = 0.3607616;
            c[2] = 0.4679139;
            c[3] = 0.4679139;
            c[4] = 0.3607616;
            c[5] = 0.1713245;
            // carga de x
            x[0] = (-0.932469514);
            x[1] = (-0.661209386);
            x[2] = (-0.238619186);
            x[3] = 0.238619186;
            x[4] = 0.661209386;
            x[5] = 0.932469514;
            break; 
        default:
            cout << "\nERROR: Cantidad de datos no contemplada. Modifique la cantidad de datos y reinicie el programa." << endl;
            exit = true;
            break;
    }
    if(exit != true){
        // Calculo de I 
        I = ((b-a)/2) * ( c[0] * f( ((b-a) * x[0])/2 + (b+a)/2 ) + c[1] * f( ((b-a) * x[1])/2 + (b+a)/2 ) + c[2] * f( ((b-a) * x[2])/2 + (b+a)/2 ) + c[3] * f( ((b-a) * x[3])/2 + (b+a)/2 ) + c[4] * f( ((b-a) * x[4])/2 + (b+a)/2 ) + c[5] * f( ((b-a) * x[5])/2 + (b+a)/2 ));

        // Impresion del resultado
        cout << "I = " << I << endl;
        cout << "Se consideraron " << n << " datos." << endl;
    }

    return 0;
}