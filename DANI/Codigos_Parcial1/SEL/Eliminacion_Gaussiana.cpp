// -------------------------- Metodo de Eliminacion Gaussiana --------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int TAM = 2; // tamanio de las matrices

void reduccionGauss(double A[TAM][TAM], double b[TAM]); // incluye pivot. NO hace retrosustitucion
bool solucionUnica(double A[TAM][TAM]); // retorna 1 si la matriz tiene solucion unica
void retrosustitucion(double A[TAM][TAM], double b[TAM], double x[TAM]);

int main(int argc, char *argv[])
{
    double A[TAM][TAM] = {{5,1},{2,-3}}; // matriz de coeficientes
    double b[TAM] = {7,-4}; // vector de terminos indep.
    double x[TAM] = {0};

    // impresion de la matriz cargada
    cout << "Matriz cargada: " << endl;
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            cout << A[i][j] << "\t";
        }
        cout << "|\t" << b[i] << endl;
    }

    // reduccion con pivoteo
    reduccionGauss(A,b);

    // control del determinante
    if(solucionUnica(A)){
        cout << "Matriz reducida: " << endl;
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){
                cout << A[i][j] << "\t";
            }
            cout << "|\t" << b[i] << endl;
        }

        // retrosustitucion
        retrosustitucion(A,b,x);

        // impresion de los resultados
        cout << "Vector resultante: " << endl;
        for(int i = 0; i < TAM; i++){
            cout << "x[" << i << "] = " << x[i] << endl;
        }
    }

    return 0;
}

void reduccionGauss(double A[TAM][TAM], double b[TAM]){
    int i = 0, j = 0, k = 0;
    double factor = 0;

    // var de pivoteo
    int indexMayor = 0;
    double aux = 0;

    for(i = 0; i < TAM-1; i++){ // recorre las filas hasta TAM-2 (inclusive), porque la fila TAM-1 no tiene nada debajo
        // pivoteo
        if(abs(A[i][i]) < pow(10,-5)){ // controla que el elemento de la diag. princ. no sea muy chico
            indexMayor = i;
            for(j = i+1; j < TAM; j++){ // busca el mayor de la columna
                if(abs(A[j][i]) > A[i][i]){
                    indexMayor = j;
                }
            }
            if(indexMayor != i){
                // intercambio de filas
                for(j = i; j < TAM; j++){ // coeficientes
                    aux = A[i][j];
                    A[i][j] = A[indexMayor][j];
                    A[indexMayor][j] = aux;
                }
                // terminos indep
                aux = b[i];
                b[i] = b[indexMayor];
                b[indexMayor] = aux;
            }
        }
        // reduccion 
        for(j = i+1; j < TAM; j++){ // recorre las demas filas, reduciendolas 
            factor = (-A[j][i]) / A[i][i]; // factor que multiplica la fila i que suma a la j
            for(k = i; k < TAM; k++){ // recorre las columnas de cada fila
                A[j][k] += factor * A[i][k];
            }
            b[j] += factor * b[i];
        }
    }
}

bool solucionUnica(double A[TAM][TAM]){
    double determinante = 1;
    bool unique = true;

    // control del det(R_A)
    for(int i = 0; i < TAM; i++){
        determinante *= A[i][i]; // producto de la diagonal principal de la R_A
    }
    if(determinante == 0){
        cout << "ERROR: El sistema NO tiene solucion unica." << endl;
        unique = false;
    }

    return (unique);
}

void retrosustitucion(double A[TAM][TAM], double b[TAM], double x[TAM]){
    for(int i = TAM-1; i >= 0; i--){ // por cada fila despeja una incognita
        x[i] = b[i];
        for(int j = (i+1); j < TAM; j++){
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}