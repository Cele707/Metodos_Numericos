#include <iostream>
using namespace std;
/*
La diferenciación numérica es un método para calcular la derivada de una función a partir de valores discretos (datos). 
Se utiliza cuando no se tiene la expresión exacta de la función, pero sí puntos conocidos de la función en ciertos valores de xx.
*/
//PARA PRIMERA DERIVADAS
int main(int argc, char *argv[]) {
//declaracion
	// Vectores "x" e "y"
	int n = 3;//numero de puntos
	double x[] = {1.5, 2, 2.5};
	double y[] = {1.0721, 1.193, 1.3163};
	double resultado = 0;
	double h = x[1] - x[0];
	int i=0;
//inicio
	printf("Ingrese el valor del cual desea averiguar su derivada primera:");
	scanf("%d",&i);
	if (i == 0){
		//Hacia adelante->no se puede usar en el ultimo punto, solo en los primeros
		resultado = (y[i+1] - y[i]) / h;
		printf("La aproximacion hacia adelante es %lf\n",resultado);
	} else if (i == n-1){
		//acia atras->no puede ser usado en el primer punto, solo en los ultimos
		resultado = (y[i] - y[i-1]) / h;
		printf("La aproximacion hacia atras es %lf\n",resultado);
	} else {
		//Centrada
		resultado = (y[i+1] - y[i-1]) / (2 * h);
		printf("La aproximacion centrada es %lf\n",resultado);
	}
	
	return 0;
}

