// -------------------------Diferenciacion numerica-------------------------
/*
    Este codigo asume que nos dan una funcion y las x de los puntos, no una tabla. 
    No desarrolle un control de puntos.
*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n = 3; // cantidad de datos 

double f(double x){ // funcion a definir
    return(log(x) + 1/x);
}

int main(int argc, char *argv[])
{
    double x[n] = {1.5,2,2.5}; // vector de x de datos
    double y[n] = {0}; // vector de f(x) de datos
    double derivada = 0; // resultado aproximado

    // auxiliares
    double h = x[1] - x[0]; // distancia entre puntos
    bool exit = false;
    int exit1 = 0;
    int i = 0, modo = 0, orden = 0, precision = 0;

    // -----------carga de y-----------
    for(int j = 0; j < n; j++){
        y[j] = f(x[j]);
    }

    // -----------MENU-----------
    do{
        cout << "-----------MENU-----------" << endl;
        cout << "Para cerrar el programa, ingrese 0 (cero): ";
        cin >> exit1;
        if(exit1 == 0){
            exit = true;
        }
        else{
            // impresion de datos
            cout << "Datos cargados:" << endl;
            for(i = 0; i < n; i++){
                cout << x[i] << " | " << y[i] << endl;
            }
            // -----------carga de directivas-----------
            do{ // seleccion del punto 
                cout << "Ingrese el subindice del punto del que desea calcular la derivada: ";
                cin >> i;
                if(i < 0 || i >= n){
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                }
            }while(i < 0 || i >= n);
            do{ // seleccion del modo de calculo
                cout << "Ingrese la forma en la que desea calcular la derivada:" << endl;
                cout << "1. Hacia adelante \n2. Hacia atras \n3. Centrada" << endl;
                cin >> modo;
                if(modo < 1 || modo > 3){
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                }
            }while(modo < 1 || modo > 3);
            do{
                cout << "Ingrese el orden de la derivada que desea calcular: ";
                cin >> orden;
                if(orden < 1 || orden > 4){
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                }
            }while(orden < 1 || orden > 4);
            do{
                cout << "Ingrese la precision que desea:" << endl;
                cout << "1. Base \n2. Alta" << endl;
                cin >> precision;
                if(precision < 1 || precision > 2){
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                }
            }while(precision < 1 || precision > 2);
            
            // -----------calculo de la derivada-----------
            switch(modo){ // determina si se calcula usando hacia adelante, atrás o centrado
                case 1: // hacia adelante 
                    switch(orden){ // determina el orden de la derivada
                        case 1: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+1] - y[i]) / h;
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+2] + 4*y[i+1] - 3*y[i]) / (2*h);
                                    break;
                            }
                            break;
                        case 2:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+2] - 2*y[i+1] + y[i]) / pow(h,2);
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+3] + 4*y[i+2] - 5*y[i+1] + 2*y[i]) / pow(h,2);
                                    break;
                            }
                            break;
                        case 3: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+3] - 3*y[i+2] + 3*y[i+1] - y[i]) / pow(h,3);
                                    break;
                                case 2: // alta
                                    derivada = (-3*y[i+4] + 14*y[i+3] - 24*y[i+2] + 18*y[i+1] - 5*y[i]) / (2 * pow(h,3));
                                    break;
                            }
                            break;
                        case 4:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+4] - 4*y[i+3] + 6*y[i+2] - 4*y[i+1] + y[i]) / pow(h,4);
                                    break;
                                case 2: // alta
                                    derivada = (-2*y[i+5] + 11*y[i+4] - 24*y[i+3] + 26*y[i+2] - 14*y[i+1] + 3*y[i]) / pow(h,4);
                                    break;
                            }
                            break; 
                    }
                    break;
                case 2: // hacia atras
                    switch(orden){ // determina el orden de la derivada
                        case 1: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i] - y[i-1]) / h;
                                    break;
                                case 2: // alta
                                    derivada = (3*y[i] - 4*y[i-1] + y[i-2]) / (2*h);
                                    break;
                            }
                            break;
                        case 2:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i] - 2*y[i-1] + y[i-2]) / pow(h,2);
                                    break;
                                case 2: // alta
                                    derivada = (2*y[i] - 5*y[i-1] + 4*y[i-2] - y[i-3]) / pow(h,2);
                                    break;
                            }
                            break;
                        case 3: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i] - 3*y[i-1] + 3*y[i-2] - y[i-3]) / pow(h,3);
                                    break;
                                case 2: // alta
                                    derivada = (5*y[i] - 18*y[i-1] + 24*y[i-2] - 14*y[i-3] + 3*y[i-4]) / 2*pow(h,3);
                                    break;
                            }
                            break;
                        case 4:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i] - 4*y[i-1] + 6*y[i-2] - 4*y[i-3] + y[i-4]) / pow(h,4);
                                    break;
                                case 2: // alta
                                    derivada = (3*y[i] - 14*y[i-1] + 26*y[i-2] - 24*y[i-3] + 11*y[i-4] - 2*y[i-5]) / pow(h,4);
                                    break;
                            }
                            break; 
                    }
                    break;
                case 3: // centrado
                    switch(orden){ // determina el orden de la derivada
                        case 1: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+1] - y[i-1]) / (2*h);
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+2] + 8*y[i+1] - 8*y[i-1] + y[i-2]) / (12*h);
                                    break;
                            }
                            break;
                        case 2:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+1] - 2*y[i] + y[i-1]) / pow(h,2);
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+2] + 16*y[i+1] - 30*y[i] + 16*y[i-1] - y[i-2]) / 12*pow(h,2);
                                    break;
                            }
                            break;
                        case 3: 
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+2] - 2*y[i+1] + 2*y[i-1] - y[i-2]) / 2*pow(h,3);
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+3] + 8*y[i+2] - 13*y[i+1] + 13*y[i-1] - 8*y[i-2] + y[i-3]) / 8*pow(h,3);
                                    break;
                            }
                            break;
                        case 4:
                            switch(precision){ // determina la precision del calculo
                                case 1: // base
                                    derivada = (y[i+2] - 4*y[i+1] + 6*y[i] - 4*y[i-1] + y[i-2]) / pow(h,4);
                                    break;
                                case 2: // alta
                                    derivada = (-y[i+3] + 12*y[i+2] + 39*y[i+1] + 56*y[i] - 39*y[i-1] + 12*y[i-2] + y[i-3]) / 6*pow(h,4);
                                    break;
                            }
                            break; 
                    }
                    break;
            }
            // -----------impresion de resultados-----------
            cout << "\n-----------RESULTADOS-----------" << endl;
            cout << "Derivada " << orden << " del punto (" << x[i] << " ; "<< y[i] << ")" << " = " << derivada << endl;
            cout << "Operador utilizado: ";
            switch(modo){
                case 1:
                    cout << "hacia adelante" << endl;
                    break;
                case 2:
                    cout << "hacia atras" << endl;
                    break; 
                case 3: 
                    cout << "centrado" << endl;
                    break;
            }
            cout << "Precision: ";
            switch(precision){
                case 1:
                    cout << "base" << endl;
                    break;
                case 2:
                    cout << "alta" << endl;
                    break; 
            }
            cout << endl;
        }
    }while(exit != true);

    return 0;
}