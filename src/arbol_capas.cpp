#include "../include/arbol_capas.h"
#include <iostream>

using namespace std;

// Constructor
ArbolCapas::ArbolCapas() {
    raiz = nullptr;
}

// Metodo publico que llamaremos desde carga.cpp
void ArbolCapas::insertar(int id_capa, MatrizDispersa* matriz) {
    raiz = insertarRecursivo(raiz, id_capa, matriz);
}

// Metodo privado recursivo
NodoCapas* ArbolCapas::insertarRecursivo(NodoCapas* nodo, int id_capa, MatrizDispersa* matriz) {
    // Si llegamos a un espacio vacio, aqui metemos la capa
    if (nodo == nullptr) {
        cout << "   [Arbol] Capa " << id_capa << " guardada exitosamente en el ABB." << endl;
        return new NodoCapas(id_capa, matriz);
    }

    // Si el ID es menor, nos vamos por la rama izquierda
    if (id_capa < nodo->id_capa) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, id_capa, matriz);
    } 
    // Si el ID es mayor, nos vamos por la rama derecha
    else if (id_capa > nodo->id_capa) {
        nodo->derecha = insertarRecursivo(nodo->derecha, id_capa, matriz);
    } 
    // Si el ID ya existe, no hacemos nada para no duplicar
    else {
        cout << "   [Arbol] Advertencia: La capa " << id_capa << " ya existe." << endl;
    }

    return nodo; // Retornamos el nodo para no romper la cadena
}

// --- NUEVO METODO PARA BUSCAR LA CAPA ---
MatrizDispersa* ArbolCapas::buscarCapa(int id_capa) {
    NodoCapas* actual = raiz;
    while (actual != nullptr) {
        if (id_capa == actual->id_capa) return actual->matriz;
        if (id_capa < actual->id_capa) actual = actual->izquierda;
        else actual = actual->derecha;
    }
    return nullptr; // Retorna null si la capa no existe
}