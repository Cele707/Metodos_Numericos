#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>

/*LEN CASO DE Q SE NOS DE UNA TABLA CON DATOS NO EQUIESPACIADOS SE DEBE ARMAR UNA NUEVA TABLA AHORA SI CON 
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
#define cant_datos 5

int main(int argc, char *argv[]) {
	double datos[cant_datos][2]= {{1,2.1}, {1.4, 3.45}, {1.8, 4.80}, {2.2, 6.15}, {2.6, 7.5}};
	//UNA VEZ QUE SE TIENEN LOS DATOS SE EMPIEZA A CALCULAR:
	double a = datos[0][0]; //primer valor
	double b = datos[cant_datos-1][0]; //ultimo valor
	
	double h = datos[1][0] - datos[0][0]; // como estan equiespaciados h es lo mismo para cualquier par de datos
	int n = cant_datos-1;
	
	int i;
	double suma = datos[0][1] + datos[cant_datos-1][1]; //los Y de las puntas
	for (i = 1; i < n; i++){
		suma = suma + 2 * datos[i][1];
		
	}
	suma = (h/2) * suma;
	
	printf("El resultado de la integral es: %lf\n",suma);
	return 0;
}


