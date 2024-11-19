//Author: DanielRP0
#include <iostream>
#include <cstdlib>
#include <ctime>

#define BLOCK_SIZE 16

using namespace std;
__global__ void iniMatriz(int* matriz, int numFilas, int numColumnas) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < numFilas && col < numColumnas) {
        curandState state;
        curand_init(clock64(), row * numColumnas + col, 0, &state);
        matriz[row * numColumnas + col] = curand(&state) % 256;
    }
}

__global__ void sacarProducto(int* matriz1, int* matriz2, int* sacarProducto, int numFilas, int numColumnas) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < numFilas && col < numColumnas) {
        int sum = 0;
        for(int i = 0; i < numColumnas; ++i) {
            sum += matriz1[row * numColumnas + i] * matriz2[i * numColumnas + col];
        }
        sacarProducto[row * numColumnas + col] = sum;
    }
}

void printMatriz(int* matriz, int numFilas, int numColumnas) {
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            cout << matriz[i * numColumnas + j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numFilas = 3;
    int numColumnas = 3;

    int* matriz1;
    int* matriz2;
    int* matrizProducto;

    cudaMallocManaged(&matriz1, numFilas * numColumnas * sizeof(int));
    cudaMallocManaged(&matriz2, numFilas * numColumnas * sizeof(int));
    cudaMallocManaged(&matrizProducto, numFilas * numColumnas * sizeof(int));

    dim3 hilosPorBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 numBlocks((numColumnas + hilosPorBlock.x - 1) / hilosPorBlock.x, (numFilas + hilosPorBlock.y - 1) / hilosPorBlock.y);

    iniMatriz<<>>(matriz1, numFilas, numColumnas);
    cudaDeviceSynchronize();

    iniMatriz<<>>(matriz2, numFilas, numColumnas);
    cudaDeviceSynchronize();

    sacarProducto<<>>(matriz1, matriz2, matrizProducto, numFilas, numColumnas);
    cudaDeviceSynchronize();

    cout << "Matriz 1:" << endl;
    printMatriz(matriz1, numFilas, numColumnas);

    cout << "Matriz 2:" << endl;
    printMatriz(matriz2, numFilas, numColumnas);

    cout << "Matriz Producto:" << endl;
    printMatriz(matrizProducto, numFilas, numColumnas);

    cudaFree(matriz1);
    cudaFree(matriz2);
    cudaFree(matrizProducto);

    return 0;
}
