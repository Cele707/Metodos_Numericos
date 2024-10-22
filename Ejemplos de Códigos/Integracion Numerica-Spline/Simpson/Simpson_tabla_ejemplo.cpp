#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
#include <stdio.h>


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
