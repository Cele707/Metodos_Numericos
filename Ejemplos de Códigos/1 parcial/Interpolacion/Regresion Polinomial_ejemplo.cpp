#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define n 5 //cantidad de datos (contado desde o)

/*usamos una curva que sigue el patrón de
 los datos de manera más precisa. 
La idea es que esta curva pase cerca de todos los puntos en tu gráfico
*/

void gauss(double **A, double *B, double *X, int p);
void imprimir(double **A, double *B, int p);
void regresion_polinomial(double **A, double *B, double *Xi, double X[n], double Y[n], int p);
void armar_polinomio(double *Xi, int p);

int main(int argc, char *argv[]) {
//declaracion de variables
	double X[n]={0,1, 1.5, 3, 5}, Y[n]={1.2,2.7, 3.9, 7.1, 10}; //datos
	int p=0;
//inicio
	//ingresar orden polinomio
	printf("Ingrese el orden del polinomio(p):");
	scanf("%d", &p);
	//verificamos q hayan suficientes datos
	if(n<(p+1)){
		printf("No hay suficientes datos.");
		exit(0);
	}
//reserva de memoria
	double **A = (double **)malloc((p + 1) * sizeof(double *));
	for (int i = 0; i <= p; i++) {
		A[i] = (double *)malloc((p + 1) * sizeof(double));
	}
	double *B = (double *)malloc((p + 1) * sizeof(double));
	double *Xi = (double *)malloc((p + 1) * sizeof(double));
//verificamos q haya memoria
	if(A==NULL|| B == NULL || Xi == NULL){
		printf("No hay memoria suficiente");
		exit(1);
	}
//armamos matriz A y el vector B
	else{
		//aplicamos metodo
		regresion_polinomial(A, B, Xi, X, Y ,p);
		//imprimir matriz
		imprimir(A, B,p);
		// Resolver el sistema usando el método de Gauss
		gauss(A, B, Xi, p);
		//Mostramos el polinimio
		armar_polinomio(Xi, p);
	}
	//liberar memoria
	for (int i = 0; i <= p; i++) {
		free(A[i]);
	}
	free(A);
	free(B);
	free(Xi);
	
	return 0;
}
//funciones
void gauss(double **A, double *B, double *X, int p){
	//declaracion de variables
	double factor=0;
	double swap=0;
	double prod=1;
	int b=p+1;
	
	//Triangulacion->Obtener matriz triangular superior (Elementos por debajo de la diagonal principal = 0)
	for(int i=0; i<(b-1); i++){
		int p=i;//p va a ser el indice de la fila en la q estemos
		
		//Pivoteo parcial-> encuentra la fila con el mayor valor absoluto en la columna i e intercambia
		if (fabs(A[i][i]) < pow(10, -5)){
			// Busca la fila con el mayor valor absoluto en la columna i
			for(int l=i+1; l<b; l++){
				if(fabs(A[l][i]) > fabs(A[p][i])){
					p=l;
				}
			}
			//intercambio de filas
			if(p != i){
				for(int m=0; m<b; m++){
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
		for (int j=i+1; j<b; j++){//
			factor=-(A[j][i])/(A[i][i]);
			//este bucle actualiza los elementos de la fila j a partir de la columna i
			for(int k=i;k<b; k++){
				A[j][k]+=factor*A[i][k];
			}
			//TambiÃ©n se debe actualizar el tÃ©rmino independiente correspondiente en el vector B
			B[j]+=factor*B[i];
		}	
	}
	
	//Chequeo del determinante->Nuestra matriz debe tener
	for(int i=1; i<b; i++){
		prod=prod*A[i][i];
	}
	if(prod==0){
		printf("\nEl sistema no tiene solucion (su determinante es 0)");
		exit(0);
	}
	
	//Restrosusticion-> sustituir los valores encontrados en las ecuaciones mÃ¡s simples en las mÃ¡s complejas, de atrÃ¡s hacia adelante.
	for(int i=b-1; i>=0; i--){
		X [i] = B [i];
		for(int j=i+1; j<b; j++){
			X[i] = X[i]-A[i][j]*X[j];
		}
		X[i]=X[i]/A[i][i];
	}
	
	//Impresion de los valores de X
	printf("\nLos valores de las incognitas son:\n");
	for(int i=0; i<b; i++){
		printf("X[%d]= %lf \n", i+1, X[i]);
	}
}
void imprimir (double **A, double *B, int p){
	int b=p+1;
	printf("\nLa matriz se ve de esta manera:\n");
	for(int i=0; i<b; i++){
		for(int j=0; j<b; j++){
			printf("%.2lf \t", A[i][j]);
		}
		printf("| %.2lf\n", B[i]);
	}
}
void regresion_polinomial(double **A, double *B, double *Xi, double X[n], double Y[n], int p){
//declaracion var
	double suma_xy=0, suma_x=0;
//inicio
	for(int i=0; i<=p; i++){ //recorre filas
		suma_xy=0;
//Calcula B
		for(int j=0; j<n; j++){  // Calcula la suma para el vector B
			suma_xy+=Y[j]*pow(X[j], i);
		}
		B[i]=suma_xy;//Asigna la suma a B
//Calcula A
		for(int m=0; m<=p; m++){// recorre columnas
			suma_x=0;
			for(int k=0; k<n; k++){// Suma los términos necesarios para A[i][m]
				suma_x+=pow(X[k], (i+m));
			}
			A[i][m]=suma_x;//Asigna a A
		}
	}
}
void armar_polinomio(double *Xi, int p){
//declaracion variables
	int b=p+1;
//inicio
printf("\nEl polinomio obtenido es:\nP(x)=");
	for(int i=0; i<b; i++){
		if(i>0){
			printf(" %s ", Xi[i] >= 0 ? "+ " : "- ");
		}
		if(i == 0){
			printf("%lf", Xi[i]);
		} else 
		   if (i == 1) {
			   printf("%lfx", fabs(Xi[i]));
		} else {
			   printf("%lfx^%d", fabs(Xi[i]), i);
		   }
	}
}
