//-------------------------------Metodo del punto fijo-------------------------------
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

double g(double x){ // despejar g(x) de f(x), tal que: f(x) => x = g(x)
	return exp(-x);
}

int main(int argc, char *argv[]) {
	int i = 0; // contador de iteraciones
	int tol = 10; // exponente de la tolerancia
	double xViejo = 0, xNuevo = 0; 
	double error = 0;
    //double errorPorcentual = 0;
	bool exitAll = false;

	do{
		i++;
		xNuevo = g(xViejo); // en la primer pasada, xViejo = 0, que es lo "estandar"
		// control de convergencia 
		if(abs((g(xViejo + 0.01) - g(xViejo)) / 0.01) > 1){ // "el valor absoluto de la derivada primera de g es mayor a 1"
															// utilizo la definicion de derivada para hacer una aproximacion y evitar calcular la derivada real
			cout << "No se cumple el criterio de convergencia.";
			exitAll = true;
		}
		else{
			error = abs(xNuevo - xViejo);
			//errorPorcentual = abs((xNuevo - xViejo)/xViejo) * 100;
			xViejo = xNuevo; // actualizamos xViejo para la siguiente iter
		}
	} while(error > pow(10,-tol) && exitAll == false);

	//impresion de resultados
	cout << "Iteraciones efectuadas: "<< i << endl;
	cout << "Xr = " << xViejo << endl;
	cout << "Error = " << error << endl;
	//cout << "Error porcentual = " << errorPorcentual << "%" << endl;

	return 0;
}