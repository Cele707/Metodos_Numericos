// ------------------------------- Metodo de Lagrange -------------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int TAM = 5; // cantidad de datos -> tamanio matrices
// P_n tiene TAM = n+1 terminos, pero es de grado n

void reduccionGauss(double A[TAM][TAM], double b[TAM]); // incluye pivot. NO hace retrosustitucion
void retrosustitucion(double A[TAM][TAM], double b[TAM], double x[TAM]);

int main(int argc, char *argv[])
{
    // tabla de datos
    double xDatos[TAM] = {1.0,1.2,1.5,1.75,2.0};
    double yDatos[TAM] = {-0.148,-0.040,0.181,0.419,0.700};
    // var de interpolacion
    double xInter = 0; // punto a interpolar (definido por el usuario)
    double yInter = 0; // resultado de la interpolacion
    double productoria = 1; // esto es el 'c_k', segun la def de la profe
    // var para determinar el polinomio interpolador
    double A[TAM][TAM] = {0}; // matriz de coeficientes
    double b[TAM] = {0}; // vector de terminos indep.
    double x[TAM] = {0}; // vector de resultados // en este metodo guarda los coeficientes del pol. interpolador
    // auxiliares
    char exitAll = 0;

    // ----------- Determinacion del pol. interpolador -----------
    // armado de 'A' y 'b' a partir de los datos
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            A[i][j] = pow(xDatos[i],j);
        }
        b[i] = yDatos[i];
    }
    // reduccion
    reduccionGauss(A,b);
    cout << "Matriz reducida: " << endl;
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            cout << A[i][j] << "\t";
        }
        cout << "|\t" << b[i] << endl;
    }
    // retrosustitucion
    retrosustitucion(A,b,x);
    // impresion del polinomio resultante
    cout << "Coeficientes resultantes: " << endl;
    for(int i = 0; i < TAM; i++){
        cout << "a[" << i << "] = " << x[i] << endl;
    }
    cout << "Forma general del polinomio interpolador: " << endl;
    cout << "P_n(x) = ";
    for(int i = 0; i < TAM; i++){
        cout << "(" << x[i] << ") * x^" << i;
        if(i != TAM-1){
            cout << " + ";
        }
    }
    cout << endl;
    
    // ----------- Interpolacion -----------
    do{ // MENU
        cout << "Ingrese el valor a interpolar: ";
        cin >> xInter;
        // calculo usando el metodo de Lagrange
        yInter = 0; // limpiamos lo que quedo de antes 
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){ // calculo de c_k
                if(j != i){
                    productoria *= (xInter - xDatos[j]) / (xDatos[i] - xDatos[j]);
                }
            }
            yInter += yDatos[i] * productoria;
            productoria = 1; // limpiamos lo que haya quedado para la prox.
        }
        // impresion de resultado
        cout << "Valor interpolado: y(" << xInter <<") = " << yInter << endl;
        
        cout << "Ingrese 's' para cerrar el programa: ";
        cin >> exitAll;
    }while(exitAll != 's');

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