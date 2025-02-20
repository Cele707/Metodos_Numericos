#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
/*
El m�todo del trapecio es una t�cnica num�rica para aproximar el valor de una integral definida, 
donde se estima el �rea bajo una curva conectando los puntos inicial y final con una l�nea recta, formando un trapecio. 
El �rea de este trapecio se utiliza como una aproximaci�n de la integral.
 Para mejorar la precisi�n, se puede dividir el intervalo en varias partes, creando m�s trapecios, 
y sumando sus �reas para obtener una estimaci�n m�s precisa del �rea total bajo la curva. 
*/
//funciones
void trapecio_compuesto(double a, double b, double n);
double funcion (double x);
double derivada (double x);
int main(int argc, char *argv[]) {
//variables
	//limites de integracion (en este caso [0,3]
	double a=1;
	double b=5;
	//Para obtener n hay dos opciones:
	//calcularla a traves de la formula:
	//double n = sqrt((fabs(1/(b-a) * (fp(b)-fp(a)))/12) * (pow((b-a),3)/10e-6));
	double n = 5;
	trapecio_compuesto(a, b, n);
	return 0;
}
//funciones
double funcion(double x){
	return (5+3*pow(x, 3));
}
//derivada de la funcion
double derivada(double x){
	return (9*pow(x, 2));
}
void trapecio_compuesto(double a, double b, double n){
//variables
	double x=0;
	double error;
	//calculamos la Integral aproximada
	double h=(b-a)/n;
	double suma=funcion(a) + funcion(b);
	for(int i=1; i<n; i++){
		x = a + i*h;
		suma+=2*funcion(x);
	}
	suma=h/2 * suma;
	printf("El resultado aproximado de la integral es %lf\n",suma);
	//Error
	
	error = ((1.0/12.0) * (1/(b-a) * (derivada(b)-derivada(a))) * (pow((b-a),3)/pow(n,2)));
	printf("SU error es %lf\n",error);
}
