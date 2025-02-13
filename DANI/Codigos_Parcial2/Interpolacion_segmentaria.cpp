// -----------------------------------Interpolacion segmentaria-----------------------------------
// (spline cubica)

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int p = 5; // cantidad de datos
const int n = p-1; // cantidad de subintervalos
const int TAM = 4*n; // tamanio de las matrices A, b y z // sale de considerar que tenemos 4n incognitas y, por lo tanto, 4n ecuaciones

void armarMatrizSpline3(double x[p], double y[p], double A[TAM][TAM], double b[TAM]);
void reduccionGauss(double A[TAM][TAM], double b[TAM]); // incluye pivot. NO hace retrosustitucion
void retrosustitucion(double A[TAM][TAM], double b[TAM], double z[TAM]);

int main(int argc, char *argv[])
{
    // tabla de datos
    double x[p] = {1.0,1.2,1.7,2.5,2.6};
    double y[p] = {2.4,5.3,6.8,7.2,7.5};

    // matrices de spline 
    double A[TAM][TAM] = {0}; // matriz de coeficientes
    double b[TAM] = {0};  // vector de term. indep.
    double z[TAM] = {0}; // vector de resultados

    // var de interpolacion  
    char opcion = 0;
    double punto = 0, interpolacion = 0;
    int intervalo = 0;

    // ------------------- Armado de A | b -------------------
    armarMatrizSpline3(x,y,A,b);

    // ------------------- Reduccion por Gauss -------------------
    reduccionGauss(A,b);

    // ------------------- Calculo de incognitas -------------------
    retrosustitucion(A,b,z);

    // ------------------- Impresion de pol. trazadores -------------------
    cout << "------------------- Polinomios trazadores -------------------" << endl;
    for(int k = 0; k < n; k++){ // n trazadores (1 por intervalo)
        cout << "F[" << k << "] = "; 
        for(int j = 0; j < 4; j++){ // con 4 coeficientes c/u
            cout << "(" << z[4*k+j] << ") * x^" << 3-j;
            if(j != 3){
                cout << " + ";
            }
        }
        cout << endl;
    }

    // ------------------- Menu interactivo -------------------
    do{
        cout << "------------------- MENU -------------------" << endl;
        cout << "Ingrese 'e' para salir: ";
        cin >> opcion;
        switch(opcion){
            case 'e': // cierra el programa
                break;
            default:
                // carga del punto 
                cout << "Intervalo considerado: [" << x[0] << "," << x[n] << "]" << endl;
                cout << "Ingrese el x del punto a interpolar: ";
                cin >> punto;
                if(punto < x[0] || punto > x[n]){
                    cout << "ERROR: el punto NO pertenece al intervalo especificado." << endl;
                }
                else{
                    // determinacion del subintervalo
                    for(intervalo = 0; punto > x[intervalo+1]; intervalo++);
                    // calculo de y interpolado
                    interpolacion = 0;
                    for(int j = 0; j <= 3; j++){
                        interpolacion += z[4*intervalo+j] * pow(punto,3-j);
                    }
                    // impresion de resultados
                    cout << "El punto pertenece al intervalo: " << intervalo << endl;
                    cout << "Valor de y interpolado: y(punto) = " << interpolacion << endl;
                }
                break;
        }
    }while(opcion != 'e');

    return 0;
}

void armarMatrizSpline3(double x[p], double y[p], double A[TAM][TAM], double b[TAM]){
    /*
    Como tenemos 4 incognitas (a_k, b_k, c_k y d_k), podemos establecer la sig. equivalencia:
        a_k = z[4k]
        b_k = z[4k+1]
        c_k = z[4k+2]
        d_k = z[4k+3]
        con k = 0,...,n-1
    */

    // ---------------- Primeras 2n filas: [F_k(x_k) = y_k] y [F_k(x_(k+1)) = y_(k+1)]; k = 0,...,n-1 ----------------
    /*
    Originalmente:
        a_k * (x_k)^3 + b_k * (x_k)^2 + c_k * (x_k)^1 + d_k * (x_k)^0 = y_k
        a_k * (x_(k+1))^3 + b_k * (x_(k+1))^2 + c_k * (x_(k+1))^1 + d_k * (x_(k+1))^0 = y_k
        (Lo anterior se repite n veces, en ese orden)
    Tras aplicar la equivalencia:
        z[4k] * (x_k)^3 + z[4k+1] * (x_k)^2 + z[4k+2] * (x_k)^1 + z[4k+3] * (x_k)^0 = y_k
        z[4k] * (x_(k+1))^3 + z[4k+1] * (x_(k+1))^2 + z[4k+2] * (x_(k+1))^1 + z[4k+3] * (x_(k+1))^0 = y_k
        (Lo anterior se repite n veces, en ese orden)
    */
    for(int k = 0; k <= n-1; k++){
        for(int j = 0; j <= 3; j++){
            A[2*k][4*k+j] = pow(x[k],3-j);
            A[2*k+1][4*k+j] = pow(x[k+1],3-j);
        }
        b[2*k] = y[k];
        b[2*k+1] = y[k+1];
    }

    // ---------------- Siguientes n-1 filas: derivadas primeras ----------------
    /*
    Originalmente: 
        3 * a_k * x_(k+1)^2 + 2 * b_k * x_(k+1) + c_k = 3 * a_(k+1) * x_(k+1)^2 + 2 * b_(k+1) * x_(k+1) + c_(k+1)
    Tras aplicar la equivalencia: 
        3 * z[4k] * x_(k+1)^2 + 2 * z[4k+1] * x_(k+1) + z[4k+2] = 3 * z[4(k+1)] * x_(k+1)^2 + 2 * z[4(k+1)+1] * x_(k+1) + z[4(k+1)+2]
        => 3 * z[4k] * x_(k+1)^2 + 2 * z[4k+1] * x_(k+1) + z[4k+2] - (3 * z[4(k+1)] * x_(k+1)^2 + 2 * z[4(k+1)+1] * x_(k+1) + z[4(k+1)+2]) = 0
        => 3 * z[4k] * x_(k+1)^2 + 2 * z[4k+1] * x_(k+1) + z[4k+2] - 3 * z[4(k+1)] * x_(k+1)^2 - 2 * z[4(k+1)+1] * x_(k+1) - z[4(k+1)+2] = 0
    */
    // La seccion anterior cubrio desde la fila 0 a la 2n-1, dejando libre de la 2n en adelante. 
    // Por lo tanto, esta seccion debe cubrir de la 2n a la 3n-2
    for(int k = 0; k <= n-2; k++){
        for(int j = 0; j <= 2; j++){
            A[2*n+k][4*k+j] = (3-j) * pow(x[k+1],2-j);
            A[2*n+k][4*(k+1)+j] = -(3-j) * pow(x[k+1],2-j);
        }
    }

    // ---------------- Siguientes n-1 filas: derivadas segundas ----------------
    /*
    Originalmente:
        6 * a_k * x_(k+1) + 2 * b_k = 6 * a_(k+1) * x_(k+1) + 2 * b_(k+1)
    Tras aplicar la equivalencia:
        6 * z[4k] * x_(k+1) + 2 * z[4k+1] =  6 * z[4(k+1)] * x_(k+1) + 2 * z[4(k+1)+1]
        => 6 * z[4k] * x_(k+1) + 2 * z[4k+1] - (6 * z[4(k+1)] * x_(k+1) + 2 * z[4(k+1)+1]) = 0
        => 6 * z[4k] * x_(k+1) + 2 * z[4k+1] - 6 * z[4(k+1)] * x_(k+1) - 2 * z[4(k+1)+1] = 0
        => 2 * (3 * z[4k] * x_(k+1) + 1 * z[4k+1] - 3 * z[4(k+1)] * x_(k+1) - 1 * z[4(k+1)+1]) = 0
        => 3 * z[4k] * x_(k+1) + 1 * z[4k+1] - 3 * z[4(k+1)] * x_(k+1) - 1 * z[4(k+1)+1] = 0
    */
    // La seccion anterior cubrio de la fila 2n a la 3n-2, dejando libre de la 3n-1 en adelante.
    // Ergo: esta seccion debe cubrir de la 3n-1 a la 4n-3, dejando las ultimas dos filas para las ecuaciones impuestas.
    // (La ultima fila de la matriz es la 4*n-1)
    for(int k = 0; k <= n-2; k++){
        A[3*n-1+k][4*k] = 3 * x[k+1];
        A[3*n-1+k][4*k+1] = 1;
        A[3*n-1+k][4*k+4] = -3 * x[k+1];
        A[3*n-1+k][4*k+5] = -1;
    }

    // ---------------- Filas 2n a 4n-3 de b ----------------
    // (redundante? -> inicializamos b en 0)
    for(int i = 2*n; i <= 4*n-3; i++){
        b[i] = 0;
    }

    // ---------------- Ultimas 2 filas: ecuaciones impuestas ----------------
    // Esta seccion cubre las filas 4n-2 y 4n-1
    A[4*n-2][0] = 3 * x[0];
    A[4*n-2][1] = 1;
    A[4*n-1][4*n-4] = 3 * x[n]; 
    A[4*n-1][4*n-3] = 1;
    b[4*n-2] = 0; // redundante?
    b[4*n-1] = 0; // redundante?
}

void reduccionGauss(double A[TAM][TAM], double b[TAM]){
    int i = 0, j = 0, k = 0;
    double factor = 0;

    // var de pivoteo
    int indexMayor = 0;
    double aux = 0;

    for(i = 0; i < TAM-1; i++){ // recorre las filas hasta TAM-2 (inclusive), porque la fila TAM-1 no tiene nada debajo
        // pivoteo
        if(abs(A[i][i]) < pow(10,-5)){ // controla que el elemento de la diag. princ. no sea muy chico
            indexMayor = i;
            for(j = i+1; j < TAM; j++){ // busca el mayor de la columna
                if(abs(A[j][i]) > A[i][i]){
                    indexMayor = j;
                }
            }
            if(indexMayor != i){
                // intercambio de filas
                for(j = i; j < TAM; j++){ // coeficientes
                    aux = A[i][j];
                    A[i][j] = A[indexMayor][j];
                    A[indexMayor][j] = aux;
                }
                // terminos indep
                aux = b[i];
                b[i] = b[indexMayor];
                b[indexMayor] = aux;
            }
        }
        // reduccion 
        for(j = i+1; j < TAM; j++){ // recorre las demas filas, reduciendolas 
            factor = (-A[j][i]) / A[i][i]; // factor que multiplica la fila i que suma a la j
            for(k = i; k < TAM; k++){ // recorre las columnas de cada fila
                A[j][k] += factor * A[i][k];
            }
            b[j] += factor * b[i];
        }
    }
}

void retrosustitucion(double A[TAM][TAM], double b[TAM], double z[TAM]){
    for(int i = TAM-1; i >= 0; i--){ // por cada fila despeja una incognita
        z[i] = b[i];
        for(int j = (i+1); j < TAM; j++){
            z[i] -= A[i][j] * z[j];
        }
        z[i] /= A[i][i];
    }
}