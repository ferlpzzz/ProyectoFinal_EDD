#ifndef MATRIZ_H
#define MATRIZ_H

#include "structs.h"
#include <string>

using namespace std;

class MatrizDispersa {
public:
    NodoMatriz* raiz;

    // Constructor
    MatrizDispersa();

    // Metodos internos para buscar o crear las cabeceras
    NodoMatriz* buscarFila(int fila);
    NodoMatriz* buscarColumna(int columna);
    NodoMatriz* crearFila(int fila);
    NodoMatriz* crearColumna(int columna);

    // El metodo principal que usaremos desde carga.cpp
    void insertar(int fila, int columna, string color);
};

#endif