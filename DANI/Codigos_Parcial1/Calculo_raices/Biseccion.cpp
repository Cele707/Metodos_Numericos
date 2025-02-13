// ---------------------------- Metodo de Biseccion ----------------------------
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

double f(double x){
	return(log(pow(x,2)+1)-sin(x));
}

int main(int argc, char *argv[]) {
	
	int iter = 0; // contador de iteraciones
    int maxIter = 10; // cantidad max de iteraciones permitidas (gralmente. 10.000)
	int tol = 10; // exponente de la tolerancia
	char opcion = 0; // para elegir el tipo de error
	double a = 1.0, b = 2.0; // limites del intervalo
	double c = 0; // centro del intervalo
	double error = 0;
	
	if(f(a) * f(b) > 0)
	{
		cout << "No hay raices en el intervalo especificado.";
	} else{
		cout << "¿Como desea calcular el error?\n";
		cout << "a. Absoluto \nb. Porcentual\n:";
		cin>>opcion;

        error = (b-a)/2; // es una inicializacion nomas
		for(iter = 0; error > pow(10,-tol) && iter < maxIter; iter++){
            c = (double)(a+b)/2; // calculo del centro del intervalo
			// achicamiento del intervalo 
			if(f(a) * f(c) < 0){
				b = c;
			} else if(f(a) * f(c) > 0){
				a = c;
			} else {
				cout << "Se encontro la raiz exacta.\n";
				error = 0;
			}
			// calculo del error
			if(error != 0){ // solo puede ser 0 si se encontro la raiz exacta
				switch(opcion)
				{
				case 'a':
				case 'A':
					error = abs((double)(b-a)/2); // absoluto
					break;
				case 'b':
				case 'B':
					error = (double) ((b-a)/2) * (1/c) * 100; // porcentual
					break;
				}
			}
		}
		// impresion de resultados
		cout << "Iteraciones efectuadas: "<< iter << "\n";
		cout << "Xr = " << c << "\n";
		cout << "Error = " << error << "\n";
	}
	return 0;
}
