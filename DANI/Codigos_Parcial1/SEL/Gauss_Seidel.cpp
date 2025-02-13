// ------------------------------- Metodo de Gauss_Seidel -------------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int TAM = 2; // tamanio de las matrices

int main(int argc, char *argv[])
{
    double A[TAM][TAM] = {{5,1},{2,-3}}; // matriz de coeficientes
	double B[TAM] = {7,-4}; // vector de terminos independientes
	double xN[TAM] = {0}; // vector de resultados
    double xV[TAM] = {0}; // inicializado estandar: todo 0
    // double w = 0; // relajacion: w E [0,2]

    int tol = 0; // exponente de la tolerancia
    int iter = 0; // contador de iteraciones
    int iterMax = 2; // maximo de iter permitido
    double error = 0, errorViejo = 0;

    // auxiliares
    double suma = 0;
	bool exitALL = false, exitDD = false;

    // verificacion de si la matriz es diagonalmente dominante 
	// "|a_ii| > |sumatoria de los demas elementos de la fila|"
	for(int i = 0; i < TAM && exitDD == false; i++){ // recorre las filas
		suma = 0;
		for(int j = 0; j < TAM; j++){ // recorre las columnas 
			suma += abs(A[i][j]);
		}
		suma -= abs(A[i][i]); // el acumulador tmb sumo A[i][i], con esto se lo elimina
		if(abs(A[i][i]) <= abs(suma)){
			cout << "ADVERTENCIA: La matriz no es diagonalmente dominante, el metodo podria no converger" << endl;
			exitDD = true; // con que encuentre 1 ya es suficiente
		}
	}
    do{
        iter++;
        // calculo de xN
        for(int i = 0; i < TAM; i++){
            suma = 0; // inicializa (o limpia) el acumulador de A_ij * x_j
            for(int j = 0; j < i; j++){ // sumatoria de los anteriores a A_ij
                suma += A[i][j] * xN[j]; // diferencia con Jacobi: con los anteriores usa los que ya calculo
            }
            for(int j = i+1; j < TAM; j++){ // sumatoria de los posteriores a A_ij
                suma += A[i][j] * xV[j];
            }
            xN[i] = (B[i] - suma) / A[i][i];
            // xN[i] = w * xN[i] + (1-w) * xV[i]; // w E [0,2] // relajacion -> hay que agregar la var 'w'
        }
        // calculo del error de la iteracion
        suma = 0; // limpia el acumulador
        for(int i = 0; i < TAM; i++){
            suma += pow(xN[i] - xV[i],2); // acumula los cuadrados de las diferencias
        }
        error = sqrt(suma); // termina de calcular el modulo de la diferencia
        // control de convergencia 
        if(iter > 1 && error > errorViejo){ // en iter = 1 : error = 0 && errorViejo = 0
            cout << "ERROR: el metodo NO converge" << endl;
            exitALL = true;
        }
        else{ // reasignacion de variables para sig. iter
            errorViejo = error;
            for(int i = 0; i < TAM; i++){
                xV[i] = xN[i];
            }
        }
    }while(error > pow(10,-tol) && iter < iterMax && exitALL != true);
    // impresion de resultados
    cout << "Iteraciones efectuadas: " << iter << endl;
    for(int i = 0; i < TAM; i++){
        cout << "Xr[" << i << "] = " << xN[i] << endl;
    }
    cout << "Error = " << error << endl;

    return 0;
}