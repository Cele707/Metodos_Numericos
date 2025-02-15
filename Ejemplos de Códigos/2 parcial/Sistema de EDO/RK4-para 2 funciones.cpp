#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funciones que definen el sistema de EDOs
double F1(double x, double y1, double y2) {
	return 3 * x + y2;
}

double F2(double x, double y1, double y2) {
	return pow(x, 2) - y1 - 1;
}

int main() {
	double x0 = 0.0, xf = 1.0, h;
	int n, op_menu;
	
	// Entrada de datos
	printf("Seleccione un m\u00e9todo para definir el paso:\n");
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
		printf("Opci\u00f3n no v\u00e1lida.\n");
		return 1;
	}
	
	double *x = (double *)malloc((n + 1) * sizeof(double));
	double *y1 = (double *)malloc((n + 1) * sizeof(double));
	double *y2 = (double *)malloc((n + 1) * sizeof(double));
	
	if (x == NULL || y1 == NULL || y2 == NULL) {
		printf("Error de asignacion de memoria.\n");
		return 1;
	}

	x[0] = x0;
	y1[0] = 0.0;
	y2[0] = 1.0;
	
	FILE *file = fopen("RK4_Sistema_EDO.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	fprintf(file, "%lf\t%lf\t%lf\n", x[0], y1[0], y2[0]);
	printf("\nX0 = %lf\tY10 = %lf\tY20 = %lf\n", x[0], y1[0], y2[0]);
	
	for (int i = 0; i < n; i++) {
		double k11 = F1(x[i], y1[i], y2[i]);
		double k12 = F2(x[i], y1[i], y2[i]);
		
		double k21 = F1(x[i] + 0.5 * h, y1[i] + 0.5 * h * k11, y2[i] + 0.5 * h * k12);
		double k22 = F2(x[i] + 0.5 * h, y1[i] + 0.5 * h * k11, y2[i] + 0.5 * h * k12);
		
		double k31 = F1(x[i] + 0.5 * h, y1[i] + 0.5 * h * k21, y2[i] + 0.5 * h * k22);
		double k32 = F2(x[i] + 0.5 * h, y1[i] + 0.5 * h * k21, y2[i] + 0.5 * h * k22);
		
		double k41 = F1(x[i] + h, y1[i] + h * k31, y2[i] + h * k32);
		double k42 = F2(x[i] + h, y1[i] + h * k31, y2[i] + h * k32);
		
		x[i + 1] = x[i] + h;
		y1[i + 1] = y1[i] + (h / 6) * (k11 + 2 * k21 + 2 * k31 + k41);
		y2[i + 1] = y2[i] + (h / 6) * (k12 + 2 * k22 + 2 * k32 + k42);
		
		printf("X%d = %lf\tY1%d = %lf\tY2%d = %lf\n", i + 1, x[i + 1], i + 1, y1[i + 1], i + 1, y2[i + 1]);
		fprintf(file, "%lf\t%lf\t%lf\n", x[i + 1], y1[i + 1], y2[i + 1]);
	}
	
	
	fclose(file);
	free(x);
	free(y1);
	free(y2);
	return 0;
}


