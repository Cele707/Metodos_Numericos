#include <iostream>
#include <ctime>
#define n 5 //cantidad de datos (contado desde o)
using namespace std;

void cargar(double X[n], double Y[n]);
void imprimir(double X[n], double Y[n]);
void interpolacion(double X[n], double Y[n]);
int main(int argc, char *argv[]) {
	//declaracion de var
	double X[n]={1.0,1.2,1.5,1.75,2.0}, Y[n]={-0.148,-0.040,0.181,0.419,0.700}; //datos
	srand(time(NULL));
	//inicio
	imprimir(X, Y);
	interpolacion(X, Y);
	return 0;
}
void imprimir(double X[n], double Y[n]){
	printf("Tabla de datos:\n");
	printf("_X__|_Y__\n");
	for(int i=0; i<n; i++){
		printf("%.2lf", X[i]);
		printf("|%.2lf\n", Y[i]);
	};
}
void cargar(double X[n], double Y[n]){//ingresa numeros random
	//carga en X
	printf("Datos en X:\n");
	for(int i=0; i<n; i++){
		X[i] = rand() % 100;
		printf("%.2lf\n", X[i]);
	};
	//carga en Y
	printf("\nDatos en Y:\n");
	for(int i=0; i<n; i++){
		Y[i] = rand() % 100;
		printf("%.2lf\n", Y[i]);
	};
}
void interpolacion(double X[n], double Y[n]){
//declaracion de variables
	double v_interpolar=0;
	double suma=0;
	double producto=0;
//inicio 
	//// Solicitar al usuario el valor de X para el que quiere estimar Y
	printf("\nIngrese el valor a interpolar (^x):");
	scanf("%lf", &v_interpolar);
	//calculo del valor interpolado
	for(int i=0; i<n; i++){
		producto=1;
		for(int j=0; j<n; j++){
			if(i != j){
				producto = producto * (v_interpolar - X[j])/(X[i] - X[j]);
			}
		}
		suma = suma + (Y[i] * producto);
	}
	printf("\nEl valor interpolado es %lf", suma);
}
