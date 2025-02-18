#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define n 3 // Tamaño de la matriz
using namespace std;

void cargar(double A[n][n], double B[n]);
void imprimir(double A[n][n], double B[n]);
void Gauss_Seidel(double A[n][n], double B[n], double omega);

int main() {
	double A[n][n], B[n], omega;
	int op_menu = 0;
	do {
		printf("METODO ITERATIVO DE GAUSS-SEIDEL CON RELAJACION\n");
		printf("1-Cargar datos\n");
		printf("2-Salir\n");
		printf("Ingresar eleccion: ");
		scanf("%d", &op_menu);
		
		switch (op_menu) {
		case 1:
			cargar(A, B);
			imprimir(A, B);
			printf("Ingrese el factor de relajacion (omega): ");
			scanf("%lf", &omega);
			Gauss_Seidel(A, B, omega);
			printf("\n");
			break;
		case 2:
			exit(0);
		}
	} while (op_menu != 2);
	return 0;
}

void cargar(double A[n][n], double B[n]) {
	printf("\nMatriz A (matriz reducida):\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("Dato en [%d][%d]: ", i + 1, j + 1);
			scanf("%lf", &A[i][j]);
		}
		printf("\n");
	}
	printf("\nMatriz B (vector de terminos independientes):\n");
	for (int i = 0; i < n; i++) {
		printf("Dato en [%d]: ", i + 1);
		scanf("%lf", &B[i]);
	}
}

void imprimir(double A[n][n], double B[n]) {
	printf("\nLa matriz se ve de esta manera:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2lf\t", A[i][j]);
		}
		printf("| %.2lf\n", B[i]);
	}
}

void Gauss_Seidel(double A[n][n], double B[n], double omega) {
	double Xv[n] = {0}; // Valores anteriores
	double Xn[n] = {0}; // Valores nuevos
	double tol = 1e-10;
	double error = 0, error_anterior = 0, suma = 0;
	int iter = 0;
	
	printf("\nIngrese los valores iniciales para el vector X:\n");
	for (int i = 0; i < n; i++) {
		printf("X[%d]:", i);
		scanf("%lf", &Xv[i]);
	}
	
	do {
		iter++;
		for (int i = 0; i < n; i++) {
			suma = 0;
			for (int j = 0; j < n; j++) {
				if (j != i) {
					suma += A[i][j] * Xn[j]; // Usa los valores ya actualizados
				}
			}
			// Aplicando la relajación
			Xn[i] = (1 - omega) * Xv[i] + omega * (B[i] - suma) / A[i][i];
		}
		
		// Cálculo del error
		suma = 0;
		for (int i = 0; i < n; i++) {
			suma += pow((Xn[i] - Xv[i]), 2);
		}
		error = sqrt(suma);
		
		if (iter >= 2 && error > error_anterior) {
			printf("\nEl método no converge\n");
			exit(0);
		}
		
		error_anterior = error;
		for (int i = 0; i < n; i++) {
			Xv[i] = Xn[i];
		}
	} while (error > tol && iter <= 2);
	
	printf("\nLas soluciones del sistema luego de %d iteraciones:\n\n", iter);
	for (int i = 0; i < n; i++) {
		printf("X[%d]: %.6lf\n", i, Xn[i]);
	}
	printf("\nEl error aproximado es %.10lf\n", error);
}
