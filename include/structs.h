#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>

using namespace std;

// Mi nodo para la matriz dispersa (basicamente el pixel que voy a pintar)
struct NodoMatriz {
    int fila;
    int columna;
    string color; // Aqui guardo el color en Hexadecimal

    // Mis punteros ortogonales para moverme por toda la matriz
    NodoMatriz* arriba;
    NodoMatriz* abajo;
    NodoMatriz* izquierda;
    NodoMatriz* derecha;

    // Constructor para inicializar mi pixel limpio
    NodoMatriz(int f, int c, string col) {
        fila = f;
        columna = c;
        color = col;
        arriba = abajo = izquierda = derecha = nullptr;
    }
};

// NOTA: Mas adelante aqui agregaremos el Nodo del Arbol de Capas 
// y el Nodo de la Lista de Imagenes, pero por ahora lo dejamos asi de limpio.

#endif