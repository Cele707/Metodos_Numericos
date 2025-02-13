#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
    double x[6] = {0};
    double y[6] = {0};

    FILE *ptrArchivo = fopen("tabla_Euler.txt", "r");
    if(ptrArchivo != NULL){
        for(int i = 0; i < 6 && fscanf(ptrArchivo, "%lf\t%lf\n", &x[i], &y[i]) == 2; i++) {
            // Lee y asigna los valores a x[i] y y[i] solo si fscanf devuelve 2 (indicando que ambas lecturas fueron exitosas)
        }
        fclose(ptrArchivo); // Mueve el cierre del archivo aquí para asegurarse de que siempre se cierra después de abrirse
    }
    else{
        cout << "No se pudo abrir el archivo." << endl;
        return 1; // Retorna un código de error
    }

    for(int i = 0; i < 6; i++){
        cout << x[i] << "\t" << y[i] << endl;
    }

    return 0;
}
