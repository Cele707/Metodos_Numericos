#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n 5// cantidad de datos, numero de puntos
/*
La diferenciación numérica es un método para calcular la derivada de una función a partir de valores discretos (datos). 
Se utiliza cuando no se tiene la expresión exacta de la función, pero sí puntos conocidos de la función en ciertos valores de xx.
*/

double f(double x){ // funcion a definir
	return(log(pow(x, 2) + 1)-sin(x));
}
	
//PARA PRIMERA DERIVADAS
int main(int argc, char *argv[]) {
//declaracion
	// Vectores "x" e "y"
	double x[n] = {1.0, 1.25, 1.5, 1.75, 2}; // vector de x de datos
	double y[n]={0};
	int op_menu=0;
	
	double resultado = 0;
	double h = x[1] - x[0];
	int i=0;
	
	// -----------carga de y-----------
	for(int j = 0; j < n; j++){
		y[j] = f(x[j]);
	}
	printf("DIFERENCIACIÓN NUMERICA\n\n");
	// Imprimir los valores de x e y con índice
	printf("Tabla de datos\n");
	printf("i |   x   |   y   \n");
	printf("--|-------|------\n");
	for (int j = 0; j < n; j++) {
		printf(" %d| %.2f  | %.5f \n", j, x[j], y[j]);
	}
	printf("\n");
//inicio
	do{
		printf("\n1-Obtener derivada\n2-Salir\nRespuesta:");
		scanf("%d", &op_menu);
		switch(op_menu){
		case 1:
			printf("\nIngrese el subindice del punto del que desea calcular la derivada (i):");
			scanf("%d",&i);
			if (i == 0){// Si el índice es el primero, no se puede calcular hacia atrás ni centrada, solo hacia adelante
				resultado = (y[i+1] - y[i]) / h;
				printf("\nAl ser el primer indice, solo es posible calcular la aproximacion hacia adelante\n");
				printf("La aproximacion hacia adelante es %lf\n",resultado);
			} else if (i == n-1){// Si el índice es el último, no se puede calcular hacia adelante ni centrada, solo hacia atras
				resultado = (y[i] - y[i-1]) / h;
				printf("\nAl ser el ultimo indice, solo es posible calcular la aproximacion hacia adelante\n");
				printf("La aproximacion hacia atras es %lf\n",resultado);
			} else {
				//Hacia adelante
				resultado = (y[i+1] - y[i]) / h;
				printf("\nLa aproximacion hacia adelante es %lf\n",resultado);
				//Centrada
				resultado = (y[i+1] - y[i-1]) / (2 * h);
				printf("La aproximacion centrada es %lf\n",resultado);
				//acia atras
				resultado = (y[i] - y[i-1]) / h;
				printf("La aproximacion hacia atras es %lf\n",resultado);
			}
		
			break;
		case 2:
			printf("\nSaliendo del programa.\n");
			break;
		}
	}while(op_menu != 2);
	return 0;
}


