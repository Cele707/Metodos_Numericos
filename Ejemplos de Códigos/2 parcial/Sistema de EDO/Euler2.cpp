#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para evaluar las ecuaciones diferenciales
double F(double x, double *y, int index) {
	switch (index) {
	case 0: return 3 * x + y[1]; // F1(x, y1, y2) = 3x + y2
	case 1: return pow(x, 2) - y[0] - 1; // F2(x, y1, y2) = x^2 - y1 - 1
	default: return 0;
	}
}

int main() {
	double x0 = 0.0, xf = 1.0, h = 0;
	int n = 0, op_menu = 0;
	float num_ecuaciones_float;
	int num_ecuaciones;
	
	// Entrada de número de ecuaciones
	printf("Ingrese la cantidad de ecuaciones diferenciales: ");
	scanf("%f", &num_ecuaciones_float);
	num_ecuaciones = round(num_ecuaciones_float);
	
	// Apertura del archivo
	FILE *file = fopen("SistemaEDO-Euler2.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	// Definir el método para elegir h o n
	do {
		printf("\nSeleccione un método para definir el paso:\n");
		printf("1- Ingresar cantidad de subintervalos (n)\n");
		printf("2- Ingresar ancho del intervalo (h)\n");
		printf("3- Salir\n");
		printf("Respuesta: ");
		scanf("%d", &op_menu);
		
		switch (op_menu) {
		case 1:
			printf("Ingrese el valor de n: ");
			scanf("%d", &n);
			h = (xf - x0) / n;
			printf("El 'h' obtenido es de %lf\n", h);
			break;
		case 2:
			printf("Ingrese el valor de h: ");
			scanf("%lf", &h);
			n = (int)((xf - x0) / h);
			printf("El 'n' obtenido es de %d\n", n);
			break;
		case 3:
			fclose(file);
			return 0;
		default:
			printf("Opción no válida.\n");
		}
	} while (op_menu < 1 || op_menu > 2);
	
	// Asignación de memoria
	double *x = (double *)malloc((n + 2) * sizeof(double)); // Se usa n+2 por si hay que agregar x=1
	double *y = (double *)malloc((num_ecuaciones * (n + 2)) * sizeof(double));
	
	if (x == NULL || y == NULL) {
		printf("Error de asignación de memoria.\n");
		fclose(file);
		return 1;
	}
	
	// Condiciones iniciales
	x[0] = x0;
	y[0] = 0.0;
	y[1] = 1.0;
	for (int i = 2; i < num_ecuaciones; i++) {
		y[i] = 0.0;
	}
	
	// Imprimir y guardar condiciones iniciales
	fprintf(file, "%lf", x[0]);
	printf("\nX0 = %lf", x[0]);
	for (int i = 0; i < num_ecuaciones; i++) {
		fprintf(file, "\t%lf", y[i]);
		printf("\tY%d0 = %lf", i + 1, y[i]);
	}
	fprintf(file, "\n");
	printf("\n");
	
	// Método de Euler
	for (int i = 0; i < n; i++) {
		x[i + 1] = x[i] + h;
		for (int j = 0; j < num_ecuaciones; j++) {
			y[(i + 1) * num_ecuaciones + j] = y[i * num_ecuaciones + j] + h * F(x[i], &y[i * num_ecuaciones], j);
		}
		
		// Imprimir en consola y guardar en archivo
		printf("X%d = %lf", i + 1, x[i + 1]);
		fprintf(file, "%lf", x[i + 1]);
		for (int j = 0; j < num_ecuaciones; j++) {
			printf("\tY%d%d = %lf", j + 1, i + 1, y[(i + 1) * num_ecuaciones + j]);
			fprintf(file, "\t%lf", y[(i + 1) * num_ecuaciones + j]);
		}
		printf("\n");
		fprintf(file, "\n");
	}
	
	// Si el último valor de x no es exactamente 1.0, calcular para x=1.0
	if (fabs(x[n] - xf) > 1e-6) {
		x[n + 1] = xf;
		for (int j = 0; j < num_ecuaciones; j++) {
			y[(n + 1) * num_ecuaciones + j] = y[n * num_ecuaciones + j] + (xf - x[n]) * F(x[n], &y[n * num_ecuaciones], j);
		}
		
		// Imprimir en consola y guardar en archivo
		printf("X%d = %lf", n + 1, x[n + 1]);
		fprintf(file, "%lf", x[n + 1]);
		for (int j = 0; j < num_ecuaciones; j++) {
			printf("\tY%d%d = %lf", j + 1, n + 1, y[(n + 1) * num_ecuaciones + j]);
			fprintf(file, "\t%lf", y[(n + 1) * num_ecuaciones + j]);
		}
		printf("\n");
		fprintf(file, "\n");
	}
	
	// Cierre de archivo y liberación de memoria
	fclose(file);
	free(x);
	free(y);
	
	return 0;
}


