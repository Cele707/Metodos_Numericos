#include <iostream>
#include <vector>
using namespace std;

double f(double x ,double y) {
	return (-2 * x * y);
}

int main(int argc, char *argv[]) {
	double x0 = 0.0;
	double xf = 1.0; // Inicializado a un valor arbitrario
	double y0 = 1.0;
	double h = 0;
	int n = 0;
	double k1, k2, k3, k4;
	int op_menu=0;

	// Abrir el archivo para escritura
	FILE *file = fopen("RK4_tabla.txt", "w");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	// Escribir los valores iniciales en el archivo
	fprintf(file, "%lf\t%lf\n", x0, y0);
	
	printf("--Metodo de RK4 (Error de orden h^4)--\n");
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
		
		printf("\nTabla de Datos obtenida:\n");
		printf("X0 = %lf \tY0 = %lf", x0, y0); // Se imprime el primer el x0 e y0
		for(int i = 0; i < n; i++) {  // Cambié de n-1 a n para calcular todos los puntos
			k1 = f(x[i], y[i]);
			k2 = f(x[i] + 0.5 * h, y[i] + 0.5 * h * k1);
			k3 = f(x[i] + 0.5 * h, y[i] + 0.5 * h * k2);
			k4 = f(x[i] + h, y[i] + h * k3);
			
			y[i + 1] = y[i] + (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
			x[i + 1] = x[i] + h;
			printf("\nX%d = %lf \tY%d = %lf", i+1, x[i+1], i+1, y[i+1]);
			fprintf(file, "%lf\t%lf\n",x[i+1], y[i+1]);
		}
		return 0;
		
	} while(op_menu != 3);
	fclose(file);
}

