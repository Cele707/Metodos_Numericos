#include <iostream>
#include <stdio.h>
#include <math.h>
#define pi 3.14159
/*
El m�todo de Simpson compuesto es una t�cnica num�rica para aproximar el valor de una integral definida, 
utilizando par�bolas para conectar los puntos de la funcion. Se divide el intervalo de integraci�n en un n�mero par de subintervalos,
 y en cada grupo de tres puntos consecutivos se ajusta una par�bola que aproxima la forma de la funci�n. 
Al sumar las �reas bajo todas las par�bolas generadas, se obtiene una aproximaci�n m�s precisa del valor de la integral, .
*/
double funcion (double x);
void Simpson(double a, double b, int n);

int main(int argc, char *argv[]) {
//declaracion de var
	double a=0; 
	double b=pi/2;
	int n=2;
//inicio
	Simpson(a, b, n);
	
	
	return 0;
}
//funciones
double funcion (double x){
	return ((2*sin(x))+(cos(x)));
}
void Simpson(double a, double b, int n){
//declaracion de var
	double suma, x, h;
//Verificar que n sea par
	if (n % 2 != 0){
		printf ("�La cantidad de intervalos debe ser par!\n");
	}
	
	h = (b-a)/n;
	suma = funcion(a)+funcion(b);

//Calcular I
	for (int i = 1; i < n; i += 2) {
		x = a + i * h;
		suma += 4 * funcion(x);
	}
	
	// Calcular los t�rminos con coeficiente 2
	for (int i = 2; i < n; i += 2) {
		x = a + i * h;
		suma += 2 * funcion(x);
	}
	
	// Calcular el resultado final
	suma = (h / 3) * suma;
	
	printf("La aproximaci�n de la integral con Simpson usando funcion es: %lf\n", suma);
}
