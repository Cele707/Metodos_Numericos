#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

double f(double x ,double y) {
	return -0.05*(x-50)+2*cos(x);
}

int main(int argc, char *argv[]) {
	double x0 = 0.0;
	double xf = 1.0;  // Inicializado a un valor arbitrario
	double y0 = 80;
	double h = 0;
	int n = 0;//Definir número de pasos correctamente
	int op_menu=0;
	
	// Abrir el archivo para escritura
		FILE *file = fopen("Euler_tabla.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	// Escribir los valores iniciales en el archivo
	fprintf(file, "%.10lf\t%.10lf\n", x0, y0);
	
	printf("--Metodo de Euler (Error de orden h²)--\n");
	do{
		printf("\nDatos conocidos:\n1-n (cantidad de subintervalos)\n2-h (ancho del intervalo)\n3-Salir\nRespuesta: ");
		scanf("%d", &op_menu);
		switch(op_menu){
		case 1:
			printf("\nIngrese el valor del n:");
			scanf("%d", &n);
			h=(xf-x0)/n;
			printf("El 'h' obtenido es de %lf\n", h);
			break;
		case 2:
			printf("\nIngrese el valor del h:");
			scanf("%lf", &h);
			n=(xf-x0)/h;
			printf("El 'n' obtenido es de %d\n", n);
			break;
			
		case 3:
			fclose(file);// Cerrar el archivo antes de salir
			return 0;
			break;
		}
		
		//Redimensionar los vectores después de definir `n`
		vector<double> x(n+1);
		vector<double> y(n+1);
		
		// Inicialización de condiciones iniciales
		x[0] = x0;
		y[0] = y0;
		
		printf("\nX0 = %.10lf \tY0 = %.10lf", x0, y0); // Se imprime el primer el x0 e y0
		for(int i = 0; i < n; i++) { 
			x[i+1] = x[i] + h;
			y[i+1] = y[i] + h * f(x[i], y[i]);
			printf("\nX%d = %.10lf \tY%d = %.10lf", i+1, x[i+1], i+1, y[i+1]);
			fprintf(file, "%.10lf\t%.10lf\n",x[i+1], y[i+1]);
		}
		return 0;
	} while (op_menu != 3);
	fclose(file);
}
