#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define num_ecuaciones 3 //ES NECAEARIO HARDCODEAR CUANTAS FUNCIONES HAY EN EL SISTEMA
// Función para evaluar las ecuaciones diferenciales
double F(double x, double *y, int index) {
	switch (index) {
	case 0: return y[1]; 
	case 1: return y[2];
	case 2: return 4*y[2] - 24*y[0] + 24*pow(x,2) - 16;
	default: return 0; // Si hay más ecuaciones, añadir más casos aquí
	}
}

int main() {
	double x0 = 0.0, xf = 2.0, h = 0;
	int n = 0, op_menu = 0;
	
	// Apertura del archivo para guardar resultados
	FILE *file = fopen("RK4_Sistema_EDO.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	// Entrada del método para definir h o n
	do {
		printf("Seleccione un método para definir el paso:\n");
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
			break;
		case 2:
			printf("Ingrese el valor de h: ");
			scanf("%lf", &h);
			n = (int)((xf - x0) / h);
			n = ceil((xf - x0) / h);
			break;
		case 3:
			fclose(file);
			return 0;
		default:
			printf("Opción no válida.\n");
		}
	} while (op_menu < 1 || op_menu > 2);
	
	// Asignación de memoria dinámica para arreglos
	double *x = (double *)malloc((n + 1) * sizeof(double));
	double *y = (double *)malloc(num_ecuaciones * sizeof(double));
	
	if (x == NULL || y == NULL) {
		printf("Error de asignación de memoria.\n");
		fclose(file);
		return 1;
	}
	
	// Inicialización de condiciones iniciales
	x[0] = x0;
	y[0] = 0.0; // Condición inicial para y1
	y[1] = -1.0; // Condición inicial para y2
	y[2] = 4.0;
	for (int i = 2; i < num_ecuaciones; i++) {
		y[i] = 0.0; // Inicializar las demás ecuaciones en 0 por defecto
	}
	
	// Guardar condiciones iniciales
	fprintf(file, "%lf", x[0]);
	printf("\nX0 = %lf", x[0]);
	for (int i = 0; i < num_ecuaciones; i++) {
		fprintf(file, "\t%lf", y[i]);
		printf("\tY%d0 = %lf", i + 1, y[i]);
	}
	fprintf(file, "\n");
	printf("\n");
	
	// Aplicar el método de Runge-Kutta de cuarto orden (RK4)
	for (int i = 0; i < n; i++) {
		x[i + 1] = x[i] + h;
		
		double k1[num_ecuaciones], k2[num_ecuaciones], k3[num_ecuaciones], k4[num_ecuaciones];
		
		// Calcular k1 para cada ecuación
		for (int j = 0; j < num_ecuaciones; j++) {
			k1[j] = h * F(x[i], y, j);
		}
		
		// Calcular k2 para cada ecuación
		for (int j = 0; j < num_ecuaciones; j++) {
			double y_temp[num_ecuaciones];
			for (int k = 0; k < num_ecuaciones; k++) {
				y_temp[k] = y[k] + 0.5 * k1[k];
			}
			k2[j] = h * F(x[i] + 0.5 * h, y_temp, j);
		}
		
		// Calcular k3 para cada ecuación
		for (int j = 0; j < num_ecuaciones; j++) {
			double y_temp[num_ecuaciones];
			for (int k = 0; k < num_ecuaciones; k++) {
				y_temp[k] = y[k] + 0.5 * k2[k];
			}
			k3[j] = h * F(x[i] + 0.5 * h, y_temp, j);
		}
		
		// Calcular k4 para cada ecuación
		for (int j = 0; j < num_ecuaciones; j++) {
			double y_temp[num_ecuaciones];
			for (int k = 0; k < num_ecuaciones; k++) {
				y_temp[k] = y[k] + k3[k];
			}
			k4[j] = h * F(x[i] + h, y_temp, j);
		}
		
		// Actualizar las soluciones para y
		for (int j = 0; j < num_ecuaciones; j++) {
			y[j] = y[j] + (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6.0;
		}
		
		// Imprimir en consola y guardar en archivo
		fprintf(file, "%lf", x[i + 1]);
		printf("X%d = %lf", i + 1, x[i + 1]);
		for (int j = 0; j < num_ecuaciones; j++) {
			fprintf(file, "\t%lf", y[j]);
			printf("\tY%d%d = %lf", j + 1, i + 1, y[j]);
		}
		fprintf(file, "\n");
		printf("\n");
	}
	
	// Cerrar archivo y liberar memoria
	fclose(file);
	free(x);
	free(y);
	
	return 0;
}
