#include <iostream>
#include <stdio.h>
#include <math.h>

double funcion (double);
void biseccion (double, double, int);

int main(int argc, char *argv[]) {
	//declaracion de variables
	double a, b;
	int iter=0;
	//obtencion de datos
	printf("\nCalculo de las raices de una funcion aplicando el metodo e biseccion\n");
	printf("\nIngrese el extremo del intervalo por la izquierda:");
	scanf("%lf", &a);	
	printf("\nIngrese el extremo del intervalo por la derecha:");
	scanf("%lf", &b);
	//llamamos biseccion
	biseccion(a, b, iter);
	
	return 0;
}
//funcion
double funcion(double x){
	return (2*x)-4;
}
//metodo de la biseccion
void biseccion (double a, double b, int iter){
	//declaracion
	double tol=10*exp(-10);
	double error, c;
	//inicio
	if((funcion(a)*funcion(b))>0){//comprabamos que haya raiz en el intervalo
		printf("No hay raiz en ese intervalo");
	}
	else{
		do{
			iter++;
			c=(a+b)/2;
			/*Si hicieramos el m�todo de regula falsi c=(a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a))*/
			if((funcion(a)*funcion(c))>0){//significa que no hay cambio de signo entre a y c, por lo que la ra�z debe estar en el intervalo [c,b]
				a=c;
			}
			else{
				if((funcion(a)*funcion(c))<0){//significa que hay un cambio de signo entre a y c, lo que implica que la ra�z est� en el intervalo [a,c]
					b=c;
				}
				else{
					printf("La raiz es %lf", c);//es la raiz exacta
					exit(0);
				}
			}
			error=(b-a)/2;
		} while(error > tol);
		printf("\nLa raiz es %lf\nEl error aproximado es %lf\nLa cantidad de iteraciones realizadas es de %d", c, error, iter);
	}
}
