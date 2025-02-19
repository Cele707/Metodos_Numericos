#include <stdio.h>
#include <math.h>

// Definición de la función a integrar
double funcion(double x) {
	return (5 + 3 * pow(x, 3));
}

// Implementación de la regla de Boole
void Boole(double a, double b, int n) {
	if (n % 4 != 0) {
		printf("¡La cantidad de intervalos debe ser múltiplo de 4!\n");
		return;
	}
	
	double h = (b - a) / n;
	double suma = 0.0;
	
	for (int i = 0; i < n; i += 4) {
		double x0 = a + i * h;
		double x1 = x0 + h;
		double x2 = x0 + 2 * h;
		double x3 = x0 + 3 * h;
		double x4 = x0 + 4 * h;
		
		suma += (7 * funcion(x0) + 32 * funcion(x1) + 12 * funcion(x2) + 32 * funcion(x3) + 7 * funcion(x4));
	}
	
	suma *= (2 * h / 45);
	
	printf("La aproximación de la integral con la regla de Boole es: %lf\n", suma);
}

int main() {
	// Declaración de variables
	double a = 1.0;
	double b = 5.0;
	int n = 4; // Debe ser múltiplo de 4, cantidad de subintervalos
	
	// Calcular integral con Boole
	Boole(a, b, n);
	
	return 0;
}

