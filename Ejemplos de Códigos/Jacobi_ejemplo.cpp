#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define n 3 //definimos tamanio matriz
/*consiste en despejar cada incógnita de un sistema de ecuaciones lineales y resolverlas iterativamente. 
Para cada ecuación, despejamos la incógnita actual usando los valores de las demás incógnitas,
 que son aproximaciones de la iteración anterior.*/

using namespace std;

//funciones
void cargar(double A[n][n], double B[n]);
void imprimir(double A[n][n], double B[n]);
void jacobi(double A[n][n], double B[n]);

int main(int argc, char *argv[]) {
	double A [n][n], B[n];
	int op_menu=0;
	do{
		printf("METODO ITERATIVO DE JACOBI\n");
		printf("1-Cargar datos\n");
		printf("2-salir\n");
		printf("Ingresar elecccion:");
		scanf("%d", &op_menu);
		switch (op_menu)
		{
		case 1:
			cargar(A, B);
			imprimir(A,B);
			jacobi(A, B);
			printf("\n");
			break;
		case 2:
			exit(0);
		}
		
	}while (op_menu != 2);
	return 0;
}
//desarrollo de funciones
void cargar(double A[n][n], double B[n]){
	printf("\nMatriz A (matriz reducida):\n");
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("Dato en [%d][%d]: ",i+1, j+1);
			scanf("%lf", &A[i][j]);
		}
		printf("\n");
	}
	printf("\nMatriz B (vector de terminos independientes):\n");
	for(int i=0; i<n; i++){
		printf("Dato en [%d]: ",i+1);
		scanf("%lf", &B[i]);
	}
}
	void imprimir (double A[n][n], double B[n]){
		printf("\nLa matriz se ve de esta manera:\n");
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				printf("%.2lf \t", A[i][j]);
			}
			printf("| %.2lf\n", B[i]);
		}
	}
void jacobi (double A[n][n], double B[n]){
//declaracion de variables
	double Xv[n] = {0}; //soluciones anteriores
	double Xn[n] = {0}; //solucoines nuevas
	double tol=10*exp(-10); //tolerancia
	double error=0, error_anterior=0, suma=0;
	int iter=0;
//inicio
	//inicializamos Xv por consola
	printf("\nIngrese los valores iniciales para el vector X:\n");
	for(int i=0; i<n; i++){
		printf("X[%d]:", i);
		scanf("%lf", &Xv[i]);
	}
	//verificamos si es diagonalmente dominante (Q el valor abosluto de A[i][i] > valor absoluto de la Sumatoria de los demas numeros de la fila
	for(int i=0; i<n; i++){
		suma=0;
		for(int j=0; j<n; j++){
			if(j != i){
				suma += fabs(A[i][j]);
			}
		}
		if(fabs(A[i][i]) <= suma){
			printf("\nLa matriz no es diagonalmene dominante, el método podría no converger\n");
		}
	}
	do{
		iter++;
	//calculo de la siguiente iteracion, la siguiente incógnita
		for(int i=0; i<n; i++){
			suma=0;
			for(int j=0; j<n; j++){
				if(j != i){
					suma += A[i][j] * Xv[j];
				}
			}
			Xn[i]=(B[i]-suma)/(A[i][i]);
		}
		suma=0;
	//calculo de error
		for(int i=0; i<n; i++){
			suma += pow((Xn[i]-Xv[i]), 2);//error cuadratico
		}
		error= sqrt(suma);//error total
	//Verificamos convergencia-> Si el error está aumentando en lugar de disminuir (es decir, error > errort), el código da por hecho que el método no está convergiendo
		if(iter >= 2 && error > error_anterior){
			printf("\nEl método no converge");
			exit(0);
		}
		error_anterior=error;
		for(int i=1; i<n; i++){
			Xv[i]=Xn[i];
		}
	} while(error<tol && iter <= 100000);
	
	printf("\nLas soluciones del sistema luego de %d iteraciones:\n\n", iter);
	for(int i=0; i<n; i++){
		printf("X[%d]: %.2lf\n", i, Xn[i]);
	}
	printf("\nEl error aproximado es %.10lf\n", error);
	
}





