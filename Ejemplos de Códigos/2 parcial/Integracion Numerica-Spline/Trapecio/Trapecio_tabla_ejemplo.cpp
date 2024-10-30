#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
/*EN EL CASO DE Q SE NOS DE UNA TABLA CON DATOS NO EQUIESPACIADOS SE DEBE ARMAR UNA NUEVA TABLA AHORA SI CON 
LOS VALORES EQUIESPACIADOS UTILIZANDO INTERPOLACION A TRAVES DE SPLINE CUBICO
(COLOCAMOS COMO "X" y "Y" LOS VALORES Q SE NOS PROPORCIONARON  LUEGO COMPLETAMOS
Por ejemplo;
x       y
1      2.1
1.4    ---
1.8    ---
2.2    ---
2.6    7.5
En este caso ponemos 
double x[FILAS_MAX]={1, 2.6};
double y[FILAS_MAX]={2.1,7.5};
En el spline, corremos el programa y luego los interpolamos

*/
int main() {
	// Numero de puntos
	int n = 5;
	
	// Vectores "x" e "y"
	double x[] = {1.0, 1.4, 1.8, 2.2, 2.6};
	double y[] = {2.1, 3.45, 4.80, 6.15, 7.5};
	
	double h = x[1] - x[0]; // como están equiespaciados, h es lo mismo para cualquier par de datos
	
	int i;
	double suma = y[0] + y[n - 1]; // los Y de las puntas
	
	for (i = 1; i < n-1; i++) {
		suma += 2 * y[i]; // suma de los valores intermedios multiplicados por 2
	}
	
	suma = (h / 2) * suma; // cálculo final de la integral
	
	printf("El resultado de la integral es: %lf\n", suma);
	return 0;
}
	

