// -------------------------------Metodo de la Secante -------------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

double f(double x){// funcion a definir
    return(x);
}

int main(int argc, char *argv[])
{
    int i = 0; // contador de iteraciones
	int tol = 10; // exponente de la tolerancia
    double xViejo = 0, xViejoViejo = 1; // definir de acuerdo al comportamiento de f
    double xNuevo = 0; 
    double error = 0;
    //double errorPorcentual = 0;

    do{
        i++;
        xNuevo = xViejo - (f(xViejo) * (xViejoViejo - xViejo)) / (f(xViejoViejo) - f(xViejo)); // sale de considerar que f'(x_i) = f(x_i) / (x_i - x_(i+1))
        error = abs(xNuevo - xViejo);
        // errorPorcentual = abs((xNuevo - xViejo)/xViejo) * 100;
        // actualizamos variables para la siguiente iter:
        xViejoViejo = xViejo;
        xViejo = xNuevo; 
    } while(error > pow(10,-tol) && i < 10000);
    // impresion de resultados
	cout << "Iteraciones efectuadas: "<< i << endl;
	cout << "Xr = " << xViejo << endl;
    cout << "f(Xr) = " << f(xViejo) << endl; // para controlar que esté cerca de 0
	cout << "Error = " << error << endl;
    // cout << "Error porcentual = " << errorPorcentual << " %" << endl;

    return 0;
}