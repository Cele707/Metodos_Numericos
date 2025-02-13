// -------------------------- Metodo de RK4 --------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

// const double h = 0.01; // espaciado estandar
const double h = 0.2; // para ejemplo, con dato = (0,1)

double f(double x, double y){
    return(-2*x*y);
}

int main(int argc, char *argv[])
{
    double a = 0; // limite inf. del intervalo
    double b = 1; // limite sup. del intervalo
    int n = (b-a) / h; // cantidad de subintervalos

    double x[n+1] = {0};
    double y[n+1] = {0};

    double k1,k2,k3,k4; // particulares del metodo

    FILE *ptrTabla = NULL;

    // ------------------- carga del punto dato -------------------
    cout << "Ingrese x de dato: ";
    cin >> x[0];
    cout << "Ingrese y de dato: ";
    cin >> y[0];
    // ------------------- bucle de calculo -------------------
    for(int i = 0; i <= n-1; i++){ // solo calcula n de las n+1 veces porque el x[0],y[0] es dato
        x[i+1] = x[i]+h;
        k1 = f(x[i],y[i]);
        k2 = f(x[i] + h/2.0,y[i] + h/2.0 * k1);
        k3 = f(x[i] + h/2.0,y[i] + h/2.0 * k2);
        k4 = f(x[i] + h,y[i] + h * k3);
        y[i+1] = y[i] + h / 6.0 * (k1 + 2*k2 + 2*k3 + k4);
    }
    // ------------------- impresion a un archivo -------------------
    ptrTabla = fopen("tabla_RK4.txt","w");
    if(ptrTabla == NULL){
        cout << "ERROR: No se pudo abrir el archivo. " << endl;
    }
    else{
        cout << "Creacion de archivo exitosa. Comenzando escritura." << endl;
        for(int i = 0; i < n+1; i++){ // tenemos que imprimir los n elementos
            fprintf(ptrTabla,"%lf\t%lf\n",x[i],y[i]);
        }
        cout << "Escritura de archivo finalizada." << endl;
    }
    fclose(ptrTabla);

    return 0;
}