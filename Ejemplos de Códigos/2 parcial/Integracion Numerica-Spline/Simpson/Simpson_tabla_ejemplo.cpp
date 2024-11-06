#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

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

double simpson(double x[], double y[], int n);

int main() {
	// Ejemplo de uso con una matriz de datos x e y
	int n = 5; // Número de puntos (debe ser impar)
	double x[] = {1, 1.4, 1.8, 2.2, 2.6}; // Valores de x
	double y[] = {2.1, 3.45, 4.80, 6.15, 7.5}; // Valores de y = f(x)
	
	double resultado = simpson(x, y, n);
	if (resultado != -1) {
		printf("La aproximación de la integral mediante Simpson usando table es: %lf\n", resultado);
	}
	
	return 0;
}
// Función para aplicar el método de Simpson
double simpson(double x[], double y[], int n) {
	if (n % 2 == 0) {
		printf("El número de puntos debe ser impar para aplicar el método de Simpson.\n");
		return -1;
	}
	
	double h = x[1] - x[0]; // Asumimos que los puntos están igualmente espaciados
	double integral = y[0] + y[n-1]; // f(x0) + f(xn)
	
	// Suma de los términos de Simpson
	for (int i = 1; i < n-1; i++) {
		if (i % 2 == 0) {
			integral += 2 * y[i]; // Términos pares
		} else {
			integral += 4 * y[i]; // Términos impares
		}
	}
	
	// Multiplicar por h/3
	integral *= (h / 3.0);
	
	return integral;
}
