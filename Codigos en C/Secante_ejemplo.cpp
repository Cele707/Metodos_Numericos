#include <iostream>
#include <stdio.h>
#include <math.h>
//es utilizado si no puedo obtener la derivada a mano
//funciones
double funcion (double);
void secante (double, double);

int main(int argc, char *argv[]) {
	//declaracion de variables
	double x_viejo, x_vv;
	printf("Ingrese el primer valor: ");
	scanf("%lf", &x_vv);
	printf("Ingrese el segundo valor. ");
	scanf("%lf", &x_viejo);
	//llamamos a la funcion
	secante(x_viejo, x_vv);
	return 0;
}
//FUNCIONES
double funcion (double x){
	return exp(x)-pow(x, 2);
}
	
void secante (double x_viejo, double x_vv){
	double tol=10*exp(-10);
	double error, error_porcentual, x_nuevo;
	int iteracion=0;
	do{
		iteracion++;
		x_nuevo = x_viejo - (funcion(x_viejo)*(x_vv - x_viejo))/ (funcion(x_vv)-funcion(x_viejo));
		
		error=fabs(x_nuevo-x_viejo);
		error_porcentual=((x_nuevo - x_viejo)/ x_viejo)*100;
		x_vv = x_viejo;
		x_viejo=x_nuevo;
		
	} while(error > tol && iteracion<=100000);
		printf("\nLa raiz es %.10lf\nEl error aproximado es %.10lf y el porcentual es %.2lf\nLa cantidad de iteraciones realizadas es de %d",x_viejo, error, error_porcentual, iteracion);
}
			
