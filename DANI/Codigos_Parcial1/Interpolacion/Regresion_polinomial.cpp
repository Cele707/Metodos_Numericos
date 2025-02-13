#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n = 5; // cantidad de datos // requerido: n >= p+1
const int p = 3; // grado del polinomio de ajuste // como mucho: p = n-1
const int TAM = p+1; // tamanio de las matrices

void reduccionGauss(double A[TAM][TAM], double b[TAM]); // incluye pivot. NO hace retrosustitucion
void retrosustitucion(double A[TAM][TAM], double b[TAM], double x[TAM]);

int main(int argc, char *argv[])
{
    // tabla de datos 
    double xDatos[n] = {0, 1, 1.5, 3, 5};
    double yDatos[n] = {1.2, 2.7, 3.9, 7.1, 10};
    // var para determinar el polinomio interpolador
    double A[TAM][TAM] = {0}; // matriz de coeficientes
    double b[TAM] = {0}; // vector de terminos indep.
    double x[TAM] = {0}; // vector de resultados // en este metodo guarda los coeficientes del pol. interpolador

    // armado de matrices para calcular los coeficientes
    for(int k = 0; k < TAM; k++){ // filas (ecuaciones)
        for(int j = 0; j < TAM; j++){ // columnas (incognitas / coeficientes)
            for(int i = 0; i < n; i++){ // sumatoria de (x_i)^(j+k)
                A[k][j] += pow(xDatos[i],(j+k));
            }
        }
        for(int i = 0; i < n; i++){ // terminos indep.
            b[k] += yDatos[i] * pow(xDatos[i],k);
        }
    }
    cout << "Matriz armada: " << endl;
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            cout << A[i][j] << "\t";
        }
        cout << "|\t" << b[i] << endl;
    }

    // red. de matriz
    reduccionGauss(A,b);
    cout << "Matriz reducida: " << endl;
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            cout << A[i][j] << "\t";
        }
        cout << "|\t" << b[i] << endl;
    }
    // calculo de coeficientes
    retrosustitucion(A,b,x);
    // impresion de resultados
    /* NOTA: debido a la forma en que se carga la matriz ampliada, 
    el vector de resultados queda organizado de MENOS significativo 
    a MAS significativo */
    cout << "Polinomio de grado " << p << ": " << endl;
    cout << "P_n(x) = ";
    for(int i = 0; i < TAM; i++){
        cout << "(" << x[i] << ") * x^" << i;
        if(i != TAM-1){
            cout << " + ";
        }
    }
    cout << endl;

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
void retrosustitucion(double A[TAM][TAM], double b[TAM], double x[TAM]){
    for(int i = TAM-1; i >= 0; i--){ // por cada fila despeja una incognita
        x[i] = b[i];
        for(int j = (i+1); j < TAM; j++){
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}