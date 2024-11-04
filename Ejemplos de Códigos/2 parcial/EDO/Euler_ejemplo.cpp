#include <iostream>
#include <vector>
using namespace std;

double f(double x ,double y) {
	return (-2 * x * y);
}

int main(int argc, char *argv[]) {
	double x0 = 0.0;
	double xf = 1.0;  // Inicializado a un valor arbitrario
	double y0 = 1.0;
	double h = 0.2;
	double n = (xf-x0)/h; //Definir n�mero de pasos correctamente
	
	vector<double> x(n+1);
	vector<double> y(n+1);
	
	// Inicializaci�n de condiciones iniciales
	x[0] = x0;
	y[0] = y0;
	
	// Abrir el archivo para escritura
		FILE *file = fopen("Euler_tabla.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	// Escribir los valores iniciales en el archivo
	fprintf(file, "%lf\t%lf\n", x0, y0);
	
	printf("Metodo de Euler (Error de orden h�)\n");
	
	// M�todo de Euler
	printf("\nX0 = %lf \tY0 = %lf", x0, y0); // Se imprime el primer el x0 e y0
	for(int i = 0; i < n; i++) {  // Cambi� de n-1 a n para calcular todos los puntos
		x[i+1] = x[i] + h;
		y[i+1] = y[i] + h * f(x[i], y[i]);
		printf("\nX%d = %lf \tY%d = %lf", i+1, x[i+1], i+1, y[i+1]);
		fprintf(file, "%lf\t%lf\n",x[i+1], y[i+1]);
	}
	return 0;
	
}
