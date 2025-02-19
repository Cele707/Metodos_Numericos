#include <iostream>
#include <stdio.h>
#include <math.h>

//funciones
double funcion (double);
double derivada_f (double);
void newton_raphson (double);

int main(int argc, char *argv[]) {
	//declaracion de variables
	double x_viejo;
	printf("Metodo Newton-Rhapson modificado:\n");
	printf("Ingrese el valor inicial: ");
	scanf("%lf", &x_viejo);
	//llamamos a la funcion
	newton_raphson (x_viejo);
	return 0;
}
//FUNCIONES
double funcion(double x) { 
	return pow(x, 3) - 4 * x + cos(x);
}

// Derivada usando diferencias finitas
double derivada_f(double x) {
	double h = 0.01;
	return (3 * funcion(x) - 4 * funcion(x - h) + funcion(x - 2 * h)) / (2 * h);
}	
void newton_raphson (double x_viejo){
	double tol=10*exp(-8);
	double error, error_porcentual, x_nuevo;
	int iteracion=0;
			do{
				iteracion++;
				x_nuevo = (x_viejo - (funcion(x_viejo)/derivada_f(x_viejo)));
				
				if (abs(derivada_f(x_nuevo)) < pow(10, -10)){
					printf("Derivada demasiado grande");
					exit(0);
				}
				else{
					error=abs(x_nuevo-x_viejo);
					error_porcentual=abs((x_nuevo - x_viejo)/x_viejo)*100;
					x_viejo=x_nuevo;
				}
				
				
			} while(error > tol && iteracion<=10000);
			printf("\nLa raiz es %.12lf\nEl error absoluto es %lf y el porcentual es %lf\nLa cantidad de iteraciones realizadas es de %d",x_viejo, error, error_porcentual, iteracion);
		}
			

