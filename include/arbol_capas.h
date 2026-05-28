#ifndef ARBOL_CAPAS_H
#define ARBOL_CAPAS_H

#include "matriz.h"

// Este es el nodo del Arbol Binario
struct NodoCapas {
    int id_capa;
    MatrizDispersa* matriz; // El puntero a nuestra matriz ortogonal
    
    NodoCapas* izquierda;
    NodoCapas* derecha;

    NodoCapas(int id, MatrizDispersa* m) {
        id_capa = id;
        matriz = m;
        izquierda = derecha = nullptr;
    }
};

class ArbolCapas {
public:
    NodoCapas* raiz;

    ArbolCapas();
    void insertar(int id_capa, MatrizDispersa* matriz);
    
    // --- NUEVO METODO PARA BUSCAR LA CAPA ---
    MatrizDispersa* buscarCapa(int id_capa);

private:
    // Funcion recursiva para no perder los punteros al insertar
    NodoCapas* insertarRecursivo(NodoCapas* nodo, int id_capa, MatrizDispersa* matriz);
};

#endif