#include <stdio.h>
#include <math.h>

#define N 10

// Funciones que definen el sistema de EDOs
double f1(double x, double y1, double y2, double y3) {
	return y2;
}

double f2(double x, double y1, double y2, double y3) {
	return y3;
}

double f3(double x, double y1, double y2, double y3) {
	return 4 * y3 - 24 * y1 + 24 * pow(x, 2) - 16;
}

int main() {
	double x0 = 0.0, xf = 2.0, h;
	int n, op_menu;
	
	// Entrada de datos
	printf("Euler para 3 funciones\n");
	printf("Seleccione un metodo para definir el paso:\n");
	printf("1- Ingresar cantidad de subintervalos (n)\n");
	printf("2- Ingresar ancho del intervalo (h)\n");
	printf("Respuesta: ");
	scanf("%d", &op_menu);
	
	if (op_menu == 1) {
		printf("Ingrese el valor de n: ");
		scanf("%d", &n);
		h = (xf - x0) / n;
	} else if (op_menu == 2) {
		printf("Ingrese el valor de h: ");
		scanf("%lf", &h);
		n = (xf - x0) / h;
		n = ceil((xf - x0) / h);
	} else {
		printf("Opcion no valida.\n");
		return 1;
	}
	
	double *x = (double *)malloc((n + 1) * sizeof(double));
	double *y1 = (double *)malloc((n + 1) * sizeof(double));
	double *y2 = (double *)malloc((n + 1) * sizeof(double));
	double *y3 = (double *)malloc((n + 1) * sizeof(double));
	
	if (x == NULL || y1 == NULL || y2 == NULL) {
		printf("Error de asignacion de memoria.\n");
		return 1;
	}
	
	x[0] = x0;
	y1[0] = 0.0;
	y2[0] = -1.0;
	y3[0] = 4.0;
	
	FILE *file = fopen("EUler_Sistema_EDO3.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[0], y1[0], y2[0], y3[0]);
	printf("\nX0 = %lf\tY100 = %lf\tY200 = %lf\tY300 = %lf\n", x[0], y1[0], y2[0], y3[0]);
	// Integración con el método de Euler
	for (int i = 0; i < n; i++) {
		x[i + 1] = x[i] + h;
		y1[i + 1] = y1[i] + h * f1(x[i], y1[i], y2[i], y3[i]);
		y2[i + 1] = y2[i] + h * f2(x[i], y1[i], y2[i], y3[i]);
		y3[i + 1] = y3[i] + h * f3(x[i], y1[i], y2[i], y3[i]);
		
		printf("X%d = %lf\t Y1%d = %lf\t Y2%d = %lf\t Y3%d = %lf\n", 
			   i + 1, x[i + 1], i + 1, y1[i + 1], i + 1, y2[i + 1], i + 1, y3[i + 1]);
		
		// Escribir en archivo
		fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[i + 1], y1[i + 1], y2[i + 1], y3[i + 1]);
	}
	
	fclose(file);  // Cerrar el archivo
	return 0;
}

