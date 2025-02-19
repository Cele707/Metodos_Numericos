#include <iostream>
#include <stdio.h>
#include <math.h>

double funcion (double);
void biseccion (double, double, int);

//funcion
double funcion(double x){
	return pow(x, 3) - 4*x +cos(x);
}
int main(int argc, char *argv[]) {
	//declaracion de variables
	double a, b;
	int iter=0;
	//obtencion de datos
	printf("\nCalculo de las raices de una funcion aplicando el metodo de biseccion\n");
	printf("\nIngrese el extremo del intervalo por la izquierda:");
	scanf("%lf", &a);	
	printf("\nIngrese el extremo del intervalo por la derecha:");
	scanf("%lf", &b);
	//llamamos biseccion
	biseccion(a, b, iter);
	
	return 0;
}
//metodo de la biseccion
void biseccion (double a, double b, int iter){
	//declaracion
	double tol=10*exp(-8);
	double error, error_p, c;
	//inicio
	if((funcion(a)*funcion(b))>0){//comprabamos que haya raiz en el intervalo
		printf("No hay raiz en ese intervalo");
	}
	else{
		do{
			iter++;
			c=(a+b)/2;
			//REGULA FALSI-> c=(a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a)); 
			if((funcion(a)*funcion(c))>0){//significa que no hay cambio de signo entre a y c, por lo que la raíz debe estar en el intervalo [c,b]
				a=c;
			}
			else{
				if((funcion(a)*funcion(c))<0){//significa que hay un cambio de signo entre a y c, lo que implica que la raíz está en el intervalo [a,c]
					b=c;
				}
				else{
					printf("La raiz es %lf", c);//es la raiz exacta
					exit(0);
				}
			}
			error=(b-a)/2;
			error_p=abs((b-a)/2) * (1/c) * 100;
		} while(error > tol && iter<=10000);
		printf("\nLa raiz es %.12lf\nEl error absoluto es %lf y el error porcentual es %lf\nLa cantidad de iteraciones realizadas es de %d", c, error, error_p, iter);
	}
}
