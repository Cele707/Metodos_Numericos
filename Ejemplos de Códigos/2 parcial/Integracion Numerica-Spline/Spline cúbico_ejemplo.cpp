/*El método de spline cúbico conecta un conjunto de puntos (x, y) con una curva suave usando 
polinomios de tercer grado, asegurando que la curva sea continua 
y no tenga saltos en las pendientes o curvaturas en los puntos donde se unen los tramos.*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

//#define TAM 20
//#define CANT_PUNTOS 5

const int CANT_PUNTOS = 5; // cantidad de datos
const int n = CANT_PUNTOS-1; // cantidad de subintervalos
const int TAM = 4*n; // tamanio de las matrices A, b y z // sale de considerar que tenemos 4n incognitas y, por lo tanto, 4n ecuaciones
//
void spline_cubico(double A[TAM][TAM], double B[TAM], double x[TAM], double y[TAM]);
void gauss(double A[TAM][TAM], double B[TAM], double *X);
void imprimir(double A[TAM][TAM], double B[TAM]);
void imprimir_ecuaciones(double* X, int n);
void interpolar(double x[TAM], double y[TAM], double* X);
//
int main(int argc, char *argv[]) {
	
	bool op=true;
	int op_menu=0;
	int n = CANT_PUNTOS - 1; 
	double A[TAM][TAM] = {{0}}; // Inicializamos la matriz con ceros
	double b[TAM] = {0};// Inicializamos el vector b con ceros
	double* X = (double*)malloc((4*(CANT_PUNTOS-1)) * sizeof(double));
	//puntos
	double x[TAM]={0.00, 2.00, 5.00, 7.00, 10.00};
	double y[TAM]={10.00, 25.00, 40.00, 55.00, 65.00};
	
	//spline cubico
	spline_cubico(A, b, x, y);
	//impresion
	imprimir(A, b);
	//Hacemos gauss
	gauss(A, b, X);
	//armamos ecuacoines
	imprimir_ecuaciones(X, n);
	//encontrar intervalo y la aproximacion
	do{
		printf("\nInterpolar valores(para salir presione cualquier numero distinto de 1):");
		scanf("%d", &op_menu);
		switch(op_menu){
		case 1:
			interpolar(x, y, X);
			printf("\n");
			break;
		default:
			op=false;
			break;
		}
	} while(op!=false);
	
	
	return 0;
}

//FUNCOINES
void imprimir(double A[TAM][TAM], double B[TAM]){
	printf("\nLa matriz se ve de esta manera:\n");
	int n=CANT_PUNTOS-1;
	for(int i=0; i<=(4*n)-1; i++){
		for(int j=0; j<=(4*n)-1; j++){
			printf("%.2lf\t", A[i][j]);
		}
		printf("|%.2lf\n", B[i]);
	}
}

void spline_cubico(double A[TAM][TAM], double b[TAM], double x[TAM], double y[TAM]){
	int n=CANT_PUNTOS-1;//intervalos
	//Primeras 2n filas de A
	for(int k=0; k<n; k++){
		for(int j=0; j<4; j++){
			A[2*k][4*k+j]= pow(x[k], 3-j);
			A[2*k+1][4*k+j]= pow(x[k+1], 3-j);
		}
		b[2*k]= y[k];
		b[2*k+1]= y[k+1];
	}
	//derivadas primeras
	for(int k = 0; k <= n-2; k++){
		for(int j = 0; j <= 2; j++){
			A[2*n+k][4*k+j] = (3-j) * pow(x[k+1],2-j);
			A[2*n+k][4*(k+1)+j] = -(3-j) * pow(x[k+1],2-j);
		}
	}
	//derivadas segundas
	for(int k = 0; k <= n-2; k++){
		A[3*n-1+k][4*k] = 3 * x[k+1];
		A[3*n-1+k][4*k+1] = 1;
		A[3*n-1+k][4*k+4] = -3 * x[k+1];
		A[3*n-1+k][4*k+5] = -1;
	}
	
	//Ultimas filas de A
	A[4*n-2][0]= 3*x[0];
	A[4*n-2][1]= 1;
	A[4*n-1][4*n-4]= 3*x[n];
	A[4*n-1][4*n-3]= 1;
	b[4*n-2]= 0;
	b[4*n-1]= 0;
}
void gauss(double A[TAM][TAM], double B[TAM], double X[TAM]){
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
		printf("S_%d(x) = %.6lfx³ ", i, X[4 * i]);
		printf("%s %.6lfx² ", X[4 * i + 1] >= 0 ? "+ " : "- ", fabs(X[4 * i + 1]));
		printf("%s %.6lfx ", X[4 * i + 2] >= 0 ? "+ " : "- ", fabs(X[4 * i + 2]));
		printf("%s %.6lf\n", X[4 * i + 3] >= 0 ? "+ " : "- ", fabs(X[4 * i + 3]));
	}
}
void interpolar(double x[TAM], double y[TAM], double* X){	
	
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
		
		
