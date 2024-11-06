#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
/*EN EL CASO DE Q SE NOS DE UNA TABLA CON DATOS NO EQUIESPACIADOS SE DEBE ARMAR UNA NUEVA TABLA AHORA SI CON 
LOS VALORES EQUIESPACIADOS UTILIZANDO INTERPOLACION A TRAVES DE SPLINE CUBICO
Primero obtnemos los x a partir de el x0=a y el xn=b q se nos da, tmb se nos debe decir la cantidad de subintervalos (n)
Entonces haces a-b/n -> cuanto va a haber entre cada numero de x. Obtenemos entonces algo as:
x      y
1      2.1
1.4    ---
1.8    ---
2.2    ---
2.6    7.5

Ponemos en el Spline la tabla original q nos dieron e interpolamos las x q obtuvimos
Entonces tenemos asi los y

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
	

