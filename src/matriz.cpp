#include "../include/matriz.h"
#include <iostream>

using namespace std;

// Constructor: inicializa el nodo raiz (esquina superior izquierda)
MatrizDispersa::MatrizDispersa() {
    raiz = new NodoMatriz(-1, -1, "RAIZ");
}

// Busca si ya existe una cabecera para la fila
NodoMatriz* MatrizDispersa::buscarFila(int fila) {
    NodoMatriz* temp = raiz->abajo;
    while (temp != nullptr) {
        if (temp->fila == fila) return temp;
        temp = temp->abajo;
    }
    return nullptr;
}

// Busca si ya existe una cabecera para la columna
NodoMatriz* MatrizDispersa::buscarColumna(int columna) {
    NodoMatriz* temp = raiz->derecha;
    while (temp != nullptr) {
        if (temp->columna == columna) return temp;
        temp = temp->derecha;
    }
    return nullptr;
}

// Crea una nueva cabecera de fila de forma ordenada
NodoMatriz* MatrizDispersa::crearFila(int fila) {
    NodoMatriz* nuevaFila = new NodoMatriz(fila, -1, "FILA");
    NodoMatriz* actual = raiz;
    
    // Avanza mientras haya nodos y el siguiente sea de una fila menor
    while (actual->abajo != nullptr && actual->abajo->fila < fila) {
        actual = actual->abajo;
    }
    
    // Conecta los punteros arriba y abajo
    nuevaFila->abajo = actual->abajo;
    if (actual->abajo != nullptr) {
        actual->abajo->arriba = nuevaFila;
    }
    actual->abajo = nuevaFila;
    nuevaFila->arriba = actual;
    
    return nuevaFila;
}

// Crea una nueva cabecera de columna de forma ordenada
NodoMatriz* MatrizDispersa::crearColumna(int columna) {
    NodoMatriz* nuevaCol = new NodoMatriz(-1, columna, "COL");
    NodoMatriz* actual = raiz;
    
    // Avanza mientras haya nodos y el siguiente sea de una columna menor
    while (actual->derecha != nullptr && actual->derecha->columna < columna) {
        actual = actual->derecha;
    }
    
    // Conecta los punteros izquierda y derecha
    nuevaCol->derecha = actual->derecha;
    if (actual->derecha != nullptr) {
        actual->derecha->izquierda = nuevaCol;
    }
    actual->derecha = nuevaCol;
    nuevaCol->izquierda = actual;
    
    return nuevaCol;
}

// Inserta un pixel en la matriz ortogonal
void MatrizDispersa::insertar(int fila, int columna, string color) {
    NodoMatriz* nuevo = new NodoMatriz(fila, columna, color);

    // 1. Asegurar que existan las cabeceras
    NodoMatriz* nodoFila = buscarFila(fila);
    if (nodoFila == nullptr) {
        nodoFila = crearFila(fila);
    }

    NodoMatriz* nodoColumna = buscarColumna(columna);
    if (nodoColumna == nullptr) {
        nodoColumna = crearColumna(columna);
    }

    // 2. Insertar en la fila (movimiento horizontal)
    NodoMatriz* actualF = nodoFila;
    while (actualF->derecha != nullptr && actualF->derecha->columna < columna) {
        actualF = actualF->derecha;
    }
    nuevo->derecha = actualF->derecha;
    if (actualF->derecha != nullptr) {
        actualF->derecha->izquierda = nuevo;
    }
    actualF->derecha = nuevo;
    nuevo->izquierda = actualF;

    // 3. Insertar en la columna (movimiento vertical)
    NodoMatriz* actualC = nodoColumna;
    while (actualC->abajo != nullptr && actualC->abajo->fila < fila) {
        actualC = actualC->abajo;
    }
    nuevo->abajo = actualC->abajo;
    if (actualC->abajo != nullptr) {
        actualC->abajo->arriba = nuevo;
    }
    actualC->abajo = nuevo;
    nuevo->arriba = actualC;
}

// --- METODOS NUEVOS PARA GENERAR LA IMAGEN ---

string MatrizDispersa::obtenerPixel(int fila, int columna) {
    NodoMatriz* auxFila = buscarFila(fila);
    if (auxFila == nullptr) return ""; // Si la fila no existe, es un espacio vacio

    NodoMatriz* actual = auxFila->derecha;
    while (actual != nullptr) {
        if (actual->columna == columna) {
            return actual->color;
        }
        actual = actual->derecha;
    }
    return ""; // Si llegamos aca, la celda especifica esta vacia
}

int MatrizDispersa::getMaxFila() {
    if (raiz == nullptr || raiz->abajo == nullptr) return 0;
    NodoMatriz* aux = raiz->abajo;
    int maxF = 0;
    while (aux != nullptr) {
        if (aux->fila > maxF) maxF = aux->fila;
        aux = aux->abajo;
    }
    return maxF;
}

int MatrizDispersa::getMaxColumna() {
    if (raiz == nullptr || raiz->derecha == nullptr) return 0;
    NodoMatriz* aux = raiz->derecha;
    int maxC = 0;
    while (aux != nullptr) {
        if (aux->columna > maxC) maxC = aux->columna;
        aux = aux->derecha;
    }
    return maxC;
}