#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>

using namespace std;

// Mi nodo para la matriz dispersa (basicamente el pixel que voy a pintar)
struct NodoMatriz {
    int fila;
    int columna;
    string color; // Aqui guardo el color en Hexadecimal, ej: "#e74c3c"
    
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

// La estructura principal de mi matriz dispersa
struct MatrizDispersa {
    // Pendiente: Aqui tengo que meter mis punteros a las cabeceras de filas y columnas
    // NodoCabecera* filas;
    // NodoCabecera* columnas;
    
    MatrizDispersa() {
        // Inicializo mi matriz vacia
    }
    
    // Aqui voy a meter los metodos que ya tenia para insertar, buscar, etc.
};

// El nodo para mi arbol de capas (ABB)
struct NodoCapa {
    int id_capa;
    MatrizDispersa* pixeles; // El corazon de la capa: ¡aqui meto mi matriz dispersa!
    
    // Mis punteros para moverme en el arbol binario de busqueda
    NodoCapa* izquierdo;
    NodoCapa* derecho;

    // Constructor para cuando necesite crear una capa nueva
    NodoCapa(int id) {
        id_capa = id;
        pixeles = new MatrizDispersa(); // Me aseguro de que cada capa nazca con su matriz lista para usarse
        izquierdo = derecho = nullptr;
    }
};

#endif