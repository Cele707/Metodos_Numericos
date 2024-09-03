#include <iostream>
#include <stdio.h>
#include <math.h>
/*
LA FUNCION QUE SE VA A UTILIZAR ES:

*/

//funciones
double despeje_f (double);
void punto_fijo (double);
//main
int main(int argc, char *argv[]) {
	//declaracion de variables
	double x_viejo;
	printf("Ingrese el valor inicial: ");
	scanf("%lf", &x_viejo);
	//llamamos al metodo punto fijo
	punto_fijo(x_viejo);
	return 0;
}
//funciones
double despeje_f (double x){ 
	return exp(-x);
}
void punto_fijo(double x_viejo){
	//declaracion variables
	double tol=10*exp(-10);
	double error, error_porcentual, x_nuevo;
	int iter=0;
	//inicio
	do{
		iter++;
		x_nuevo=despeje_f(x_viejo);
		if(fabs((despeje_f(x_viejo+0.01)-despeje_f(x_viejo))/(0.01))>1){
			printf("No se cumple el criterio de convergencia");
			exit(0);
		}
		else{
			error=fabs(x_nuevo - x_viejo);
			error_porcentual=((x_nuevo - x_viejo)/x_viejo)*100;
			x_viejo=x_nuevo;
		}
		
	} while(error > tol);
	printf("\nLa raiz es %lf\nEl error aproximado es %lf y le porcentual es %lf\nLa cantidad de iteraciones realizadas es de %d",x_viejo, error, error_porcentual, iter);
}
