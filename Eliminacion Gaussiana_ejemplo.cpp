#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define n 3 //definimos tama�o matriz

using namespace std;
//funciones
void cargar(double A[n][n], double B[n]);
void imprimir(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n]);

int main(int argc, char *argv[]) {
	double A [n][n], B[n];
	int op_menu=0;
	do{
		printf("ELIMINACION GAUSSIANA\n");
		printf("1-Cargar datos\n");
		printf("2-salir\n");
		printf("Ingresar elecccion:");
		scanf("%d", &op_menu);
		switch (op_menu)
		{
		case 1:
		cargar(A, B);
		imprimir(A,B);
		gauss(A, B);
		printf("\nMatriz luego de la triangulacion:\n");
		imprimir(A,B);
		printf("\n");
			break;
		case 2:
		exit(0);
		}
		
	}while (op_menu != 2);
	return 0;
}

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
void gauss(double A[n][n], double B[n]){
	//declaracion de variables
	double factor=0;
	double swap=0;
	double prod=1;
	double X [n];
	int p=0;

	//Triangulacion->Obtener matriz triangular superior (Elementos por debajo de la diagonal principal = 0)
	for(int i=0; i<(n-1); i++){
		int p=i;//p va a ser el indice de la fila en la q estemos

		//Pivoteo parcial-> encuentra la fila con el mayor valor absoluto en la columna i e intercambia
		if (fabs(A[i][i]) < pow(10, -5)){
			// Busca la fila con el mayor valor absoluto en la columna i
			for(int l=i+1; l<n; l++){
				if(fabs(A[l][i]) > fabs(A[p][i])){
					p=l;
				}
			}
				//intercambio de filas
				if(p != i){
					for(int m=0; m<n; m++){
					swap=A[p][m];
					A[p][m]=A[i][m];
					A[i][m]=swap;
				}
				swap=B[p];
				B[p]=B[i];
				B[i]=swap;
			}
		}
		//continuamos con triangulacion
		//este bucle hace cero todos los elementos debajo de la diagonal princial
		for (int j=i+1; j<n; j++){//
			factor=-(A[j][i])/(A[i][i]);
			//este bucle actualiza los elementos de la fila j a partir de la columna i
			for(int k=i;k<n; k++){
				A[j][k]+=factor*A[i][k];
			}
		//También se debe actualizar el término independiente correspondiente en el vector B
		B[j]+=factor*B[i];
		}	
	}
	
	//Chequeo del determinante->Nuestra matriz debe tener
	for(int i=1; i<n; i++){
		prod=prod*A[i][i];
	}
	if(prod==0){
		printf("\nEl sistema no tiene solución (su determinante es 0)");
		exit(0);
	}

	//Restrosusticion-> sustituir los valores encontrados en las ecuaciones más simples en las más complejas, de atrás hacia adelante.
	for(int i=n-1; i>=0; i--){
		X [i] = B [i];
		for(int j=i+1; j<n; j++){
			X[i] = X[i]-A[i][j]*X[j];
		}
		X[i]=X[i]/A[i][i];
	}

}
