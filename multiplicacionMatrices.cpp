//Author: DanielRP0
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main() {
    srand(time(0)); // generar números aleatorios

    int numFilas = 10; //
    int numColumnas = 10; //

    //  matrices
    int** matriz1 = new int*[numFilas];
    int** matriz2 = new int*[numFilas];
    int** matrizProducto = new int*[numFilas];
    for(int i = 0; i < numFilas; ++i) {
        matriz1[i] = new int[numColumnas];
        matriz2[i] = new int[numColumnas];
        matrizProducto[i] = new int[numColumnas];
    }

    // Llenar las primeras dos matrices con valores aleatorios en el rango de un byte
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            matriz1[i][j] = rand() % 256;
            matriz2[i][j] = rand() % 256;
        }
    }

    // Calcular el producto de las dos matrices
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            matrizProducto[i][j] = 0;
            for(int k = 0; k < numColumnas; ++k) {
                matrizProducto[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    // Imprimir las tres matrices
    std::cout << "Matriz 1:" << std::endl;
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }

    std::cout << "Matriz 2:" << std::endl;
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            cout << matriz2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz Producto:" << endl;
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            std::cout << matrizProducto[i][j] << " ";
        }
        cout << endl;
    }

    // Liberar la memoria
    for(int i = 0; i < numFilas; ++i) {
        delete [] matriz1[i];
        delete [] matriz2[i];
        delete [] matrizProducto[i];
    }
    delete [] matriz1;
    delete [] matriz2;
    delete [] matrizProducto;

    return 0;
}
