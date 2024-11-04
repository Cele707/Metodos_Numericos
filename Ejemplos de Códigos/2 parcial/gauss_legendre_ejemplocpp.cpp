#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
/*
El método de Gauss-Legendre es una técnica numérica utilizada para aproximar el valor de integrales definidas. 
Se basa en la idea de evaluar la función en puntos específicos llamados "puntos de Gauss" y multiplicar esos valores por ciertos "pesos".
*/
double f (double x);
void gauss_legendre ();
	
int main(int argc, char *argv[]) {
	gauss_legendre();
	return 0;
}
//
double f (double x){
	return (pow(x,3) * 2);
}
	
void gauss_legendre(){
//definir limites de integracion
	double a,b;
	printf("Ingrese los limites de integracion\n");
	printf("a:");
	scanf("%lf",&a);
	printf("b:");
	scanf("%lf",&b);
//calculo de la integral
double c0 = 0,c1 = 0,c2 = 0,c3 = 0,c4 = 0,c5 = 0;
double x0 = 0, x1 = 0,x2 = 0, x3 = 0, x4 = 0,x5 = 0;
double I = 0;
 //ingresar cantidad de puntos
int puntos;
printf("\nIngrese la cantidad de puntos (2 - 6):");
scanf("%d",&puntos);
	switch (puntos)
	{
	case 2:
		c0 = 1.0;
		c1 = 1.0;
		x0 = -0.577350269;
		x1 = -x0;
		
		I = ((b-a)/2) * (c0 * f(((b-a)*x0/2) + ((b+a)/2)) + c1 * f(((b-a)*x1/2) + ((b+a)/2)));
		break;          
	case 3:
		c0 = 0.5555556;
		c1 = 0.8888889;
		c2 = c0;
		x0 = -0.774596669;
		x1 = 0.0;
		x2 = -x1;
		
		I = ((b-a)/2)  * ((c0 * f(((b-a)* x0 / 2) + ((b+a)/2))) + (c1 * f(((b-a)*x1) / 2 + ((b+a)/2))) + (c2* f(((b-a)*x2 / 2) + ((b+a)/2))));
		break;
	case 4:
		c0 = 0.3478548;
		c1 = 0.6521452;
		c2 = 0.6521452;
		c3 = 0.3478548;
		x0 = -0.861136312;
		x1 = -0.339981044;
		x2 = 0.339981044;
		x3 = 0.861136312;
		
		I = ((b-a)/2)  * ((c0 * f(((b-a)* x0 / 2) + ((b+a)/2))) + (c1 * f(((b-a)*x1) / 2 + ((b+a)/2))) + (c2* f(((b-a)*x2 / 2) + ((b+a)/2)))+ (c3 * f(((b-a)*x3 / 2) + ((b+a)/2))));
		
		break;
	case 5:
		c0 = 0.2369269;
		c1 = 0.4786287;
		c2 = 0.5688889;
		c3 = 0.4786287;
		c4 = 0.2369269;
		x0 = -0.906179846;
		x1 = -0.538469310;
		x2 = 0.0;
		x3 = 0.538469310;
		x4 = 0.906179846;
		
		I = ((b-a)/2)  * ((c0 * f(((b-a)* x0 / 2) + ((b+a)/2))) + (c1 * f(((b-a)*x1) / 2 + ((b+a)/2))) + (c2* f(((b-a)*x2 / 2) + ((b+a)/2)))+ (c3 * f(((b-a)*x3 / 2) + ((b+a)/2)))+ (c4 * f(((b-a)*x4 / 2) + ((b+a)/2))));
		
		break;
	case 6:
		c0 = 0.1713245;
		c1 = 0.3607616;
		c2 = 0.4679139;
		c3 = 0.4679139;
		c4 = 0.3607616;
		c5 = 0.1713245;
		x0 = -0.932469514;
		x1 = -0.661209386;
		x2 = -0.238619186;
		x3 = -x2;
		x4 = -x1;
		x5 = -x0;
		
		I = ((b-a)/2)  * ((c0 * f(((b-a)* x0 / 2) + ((b+a)/2))) + (c1 * f(((b-a)*x1) / 2 + ((b+a)/2))) + (c2* f(((b-a)*x2 / 2) + ((b+a)/2)))+ (c3 * f(((b-a)*x3 / 2) + ((b+a)/2)))+ (c4 * f(((b-a)*x4 / 2) + ((b+a)/2))) + (c5
 * f(((b-a)*x5 / 2) + ((b+a)/2))));
		break;
	default:
	printf("Asegurese que la cantidad de puntos ingresadas esta comprendida entre 2 y 6");
	break;
	}
	printf("\nEl valor de la integral es %f",I);
}
