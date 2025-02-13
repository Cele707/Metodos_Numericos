// -------------------------------Metodo de Newton-Raphson-------------------------------

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

double f(double x){// funcion a definir
    return(log(pow(x,2)+1)-sin(x));
}
double fp1(double x){ // derivada primera de la funcion f
    return((2*x / (pow(x,2)+1)) - cos(x));
}

int main(int argc, char *argv[])
{
    int i = 0; // contador de iteraciones
    int iterMax = 1; 
	int tol = 10; // exponente de la tolerancia
    double xViejo = 1, xNuevo = 0; // definir xViejo segun comportamiento de f
    double error = 0;
    //double errorPorcentual = 0;
    bool exitAll = false;

    do{
        i++;
        xNuevo = xViejo - f(xViejo)/fp1(xViejo); // sale de considerar que f'(x_i) = f(x_i) / (x_i - x_i+1)
        error = abs(xNuevo - xViejo);
        // errorPorcentual = abs((xNuevo - xViejo)/xViejo) * 100;
        xViejo = xNuevo; // actualizamos xViejo para la siguiente iter
        if(abs(fp1(xNuevo) < pow(10,-tol))){ // controla que la derivada no sea demasiadoa chica
            cout << "Derivada demasiado chica" << endl;
            exitAll = true;
        }
    } while(error > pow(10,-tol) && i < iterMax && exitAll != true);
    // impresion de resultados
	cout << "Iteraciones efectuadas: "<< i << endl;
	cout << "Xr = " << xViejo << endl;
    cout << "f(Xr) = " << f(xViejo) << endl; // para controlar que esté cerca de 0
	cout << "Error = " << error << endl;
    // cout << "Error porcentual = " << errorPorcentual << " %" << endl;

    return 0;
}