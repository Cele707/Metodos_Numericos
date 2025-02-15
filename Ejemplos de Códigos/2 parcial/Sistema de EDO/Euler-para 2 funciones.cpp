#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

double F1(double x, double y1, double y2) {
	return 3 * x + y2; // Ejemplo de función
}

double F2(double x, double y1, double y2) {
	return pow(x, 2) - y1 - 1; // Ejemplo de función
}

int main(int argc, char *argv[]) {
	double x0 = 0.0;
	double xf = 1.0; // Inicializado a un valor arbitrario
	double y10 = 0;
	double y20 = 1.0;
	double h = 0;
	int n = 0;//Definir número de pasos correctamente
	int op_menu=0;
	
	// Apertura del archivo para escribir resultados
	FILE *file = fopen("Euler_Sistema_EDO2.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	// Escribir los valores iniciales en el archivo
	fprintf(file, "%lf\t%lf\t%lf\n", x0, y10, y20);
	
	//Selccionar si h o n
	do {
		printf("\nSeleccione un método para definir el paso:\n");
		printf("1- Ingresar cantidad de subintervalos (n)\n");
		printf("2- Ingresar ancho del intervalo (h)\n");
		printf("3- Salir\n");
		printf("Respuesta: ");
		scanf("%d", &op_menu);
		printf("\n");
		switch(op_menu) {
		case 1:
			printf("Ingrese el valor de n: ");
			scanf("%d", &n);
			h = (xf - x0) / n;
			printf("El 'h' obtenido es de %lf\n", h);
			break;
		case 2:
			printf("Ingrese el valor de h: ");
			scanf("%lf", &h);
			n = (xf - x0) / h;
			n = ceil((xf - x0) / h);
			printf("El 'n' obtenido es de %d\n", n);
			break;
		case 3:
			fclose(file);// Cerrar el archivo antes de salir
			return 0;
		default:
			printf("Opción no válida.\n");
		}
	} while(op_menu < 1 || op_menu > 2);
	
	//Redimensionar los vectores después de definir n
	vector<double> x(n+1);
	vector<double> y1(n+1);
	vector<double> y2(n+1);
	
	// Inicialización de condiciones iniciales
	x[0] = x0;
	y1[0] = y10;
	y2[0] = y20;
	
	printf("\nX0 = %lf\tY10 = %lf\tY20 = %lf\n", x0, y10, y20);
	for(int i = 0; i < n; i++) {
		x[i+1] = x[i] + h;
		y1[i+1] = y1[i] + h * F1(x[i], y1[i], y2[i]);
		y2[i+1] = y2[i] + h * F2(x[i], y1[i], y2[i]);
		
		printf("X%d = %lf\tY1%d = %lf\tY2%d = %lf\n", i+1, x[i+1], i+1, y1[i+1], i+1, y2[i+1]);
		fprintf(file, "%lf\t%lf\t%lf\n", x[i+1], y1[i+1], y2[i+1]);
	}
	
	fclose(file);
	return 0;
	
	fclose(file);
}
