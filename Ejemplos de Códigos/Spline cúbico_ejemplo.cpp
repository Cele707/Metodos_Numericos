/*El método de spline cúbico conecta un conjunto de puntos (x, y) con una curva suave usando 
polinomios de tercer grado, asegurando que la curva sea continua 
y no tenga saltos en las pendientes o curvaturas en los puntos donde se unen los tramos.*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

#define FILAS_MAX 20
#define COLUMNAS_MAX 20
#define CANT_PUNTOS 4
//
void spline_cubico(double A[FILAS_MAX][COLUMNAS_MAX], double B[FILAS_MAX], double x[FILAS_MAX], double y[FILAS_MAX]);
void gauss(double A[FILAS_MAX][COLUMNAS_MAX], double B[FILAS_MAX], double *X);
void imprimir(double A[FILAS_MAX][COLUMNAS_MAX], double B[FILAS_MAX]);
void imprimir_ecuaciones(double* X, int n);
void interpolar(double x[FILAS_MAX], double y[FILAS_MAX], double* X);
//
int main(int argc, char *argv[]) {
	
	int n = CANT_PUNTOS - 1; 
	double A[FILAS_MAX][COLUMNAS_MAX] = {{0}}; // Inicializamos la matriz con ceros
	double b[FILAS_MAX] = {0};// Inicializamos el vector b con ceros
	double* X = (double*)malloc((4*(CANT_PUNTOS-1)) * sizeof(double));
	//puntos
	double x[FILAS_MAX]={3,4.5,7, 9};
	double y[FILAS_MAX]={2.5,1,2.5, 0.5};
	//spline cubico
	spline_cubico(A, b, x, y);
	//impresion
	imprimir(A, b);
	//Hacemos gauss
	gauss(A, b, X);
	//armamos ecuacoines
	imprimir_ecuaciones(X, n);
	//encontrar intervalo y la aproximacion
	interpolar(x, y, X);
	return 0;
}

//FUNCOINES
void imprimir(double A[FILAS_MAX][COLUMNAS_MAX], double B[FILAS_MAX]){
	printf("\nLa matriz se ve de esta manera:\n");
	int n=CANT_PUNTOS-1;
	for(int i=0; i<(3*n)-1; i++){
		for(int j=0; j<(3*n)-1; j++){
			printf("%.2lf \t", A[i][j]);
		}
		printf("| %.2lf\n", B[i]);
	}
}

void spline_cubico(double A[FILAS_MAX][COLUMNAS_MAX], double b[FILAS_MAX], double x[FILAS_MAX], double y[FILAS_MAX]){
	int i=0, j=0, k=0;
	int n=CANT_PUNTOS-1;//intervalos
	//Primeras 2n filas de A
	for(k=0; k<n; k++){
		for(j=0; j<4; j++){
			A[2*k][4*k+j]= pow(x[k], 3-j);
			A[2*k+1][4*k+j]= pow(x[k+1], 3-j);
		}
		b[2*k]= y[k];
		b[2*k+1]= y[k+1];
	}
	//derivadas primeras
	k=0;
	for(i=(2*n); i<=((3*n)-2); i++){
		for(j=0; j<=2; ++j){
			A[i][4*k+j]= (3-j)*pow(x[k+1], 2-j);
			A[i][4*(k+1)+j] = -(3-j)*pow(x[k+1], (2-j));
		}
		k++;
		if(k > (n-2)){
			break;
		}
		b[i] = 0;
	}
	
	//derivadas segundas
	k=0;
	for(i=3*n-1; i<=4*n-3; i++){
		A[i][4*k]= 6*x[k+1];
		A[i][4*k+1]= 2;
		A[i][4*k+4]= -6*x[k+1];
		A[i][4*(k+1)+1]= -2;
	k++;
	if(k > (n-2)){
		break;
	}
	b[i] = 0;
	}
	
	//Ultimas filas de A
	A[4*n-2][0]= 3*x[0];
	A[4*n-2][1]= 1;
	A[4*n-1][4*n-4]= 3*x[n];
	A[4*n-1][4*n-3]= 1;
	b[4*n-2]= 0;
	b[4*n-1]= 0;
}
void gauss(double A[FILAS_MAX][COLUMNAS_MAX], double B[FILAS_MAX], double X[FILAS_MAX]){
	//declaracion de variables
	int n= 4*(CANT_PUNTOS-1);//intervalos
	double factor=0;
	double swap=0;
	double prod=1;
	
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
			//TambiÃ©n se debe actualizar el tÃ©rmino independiente correspondiente en el vector B
			B[j]+=factor*B[i];
		}	
	}
	
	//Chequeo del determinante->Nuestra matriz debe tener
	for(int i=1; i<n; i++){
		prod=prod*A[i][i];
	}
	if(prod==0){
		printf("\nEl sistema no tiene solucion (su determinante es 0)");
		exit(0);
	}
	
	//Restrosusticion-> sustituir los valores encontrados en las ecuaciones mÃ¡s simples en las mÃ¡s complejas, de atrÃ¡s hacia adelante.
	for(int i=n-1; i>=0; i--){
		X [i] = B [i];
		for(int j=i+1; j<n; j++){
			X[i] = X[i]-A[i][j]*X[j];
		}
		X[i]=X[i]/A[i][i];
	}
	
	//Impresion de los valores de X
	printf("\nConjunto solucion: \n");
	for (int i = 0; i < (n/4); ++i) {
		printf("a%d = %lf\n", i , X[4*i]);
		printf("b%d = %lf\n", i , X[4*i + 1]);
		printf("c%d = %lf\n", i , X[4*i + 2]);
		printf("d%d = %lf\n", i , X[4*i + 3]);
	}
}
void imprimir_ecuaciones(double* X, int n){
	printf("\nEcuaciones de los splines cúbicos:\n");
	for (int i = 0; i < n; i++) {
		printf("S_%d(x) = %.2lf * x^3 ", i, X[4 * i]);
		printf("%s %.2lf * x^2 ", X[4 * i + 1] >= 0 ? "+ " : "- ", fabs(X[4 * i + 1]));
		printf("%s %.2lf * x ", X[4 * i + 2] >= 0 ? "+ " : "- ", fabs(X[4 * i + 2]));
		printf("%s %.2lf\n", X[4 * i + 3] >= 0 ? "+ " : "- ", fabs(X[4 * i + 3]));
	}
}
void interpolar(double x[FILAS_MAX], double y[FILAS_MAX], double* X){	
	
double valor_interpolar=0;
int n=CANT_PUNTOS;
int intervalo;
double resultado = 0;

printf("\nIngrese el valor a interpolar:");
	scanf("%lf", &valor_interpolar);
	//verificamos q este dentro del rango de puntos
	if (valor_interpolar >= x[0] && valor_interpolar <= x[n - 1]) { 
		for (int i = 0; i < n - 1; i++) { 
			// Comprobar si x se encuentra entre m[i][0] y m[i+1][0]
			if (valor_interpolar >= x[i] && valor_interpolar <= x[i + 1]) { 
				// Calcular el valor interpolado utilizando la ecuación cúbica del intervalo
				resultado = X[4 * i] * pow(valor_interpolar, 3) + X[4 * i + 1] * pow(valor_interpolar, 2) + X[4 * i + 2] * valor_interpolar + X[4 * i + 3];
				intervalo = i;
				//Imprimimos
				printf("\nSubintervalo en el que se encuentra-> %d [%.2lf a %.2lf]\n", intervalo, x[i], x[i+1]);
				printf("Valor interpolado para x = %.2lf es y = %lf", valor_interpolar, resultado);
				break;
			}
		}
		
	} else {
		printf("\nEl valor a interpolar no se encuentra en el rango de datos\n");
	}	
}
		
		
