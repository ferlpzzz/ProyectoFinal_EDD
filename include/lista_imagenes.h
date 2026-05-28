#ifndef LISTA_IMAGENES_H
#define LISTA_IMAGENES_H

#include <iostream>

using namespace std;

// 1. Nodo simple para guardar los IDs de las capas DENTRO de la imagen
struct NodoCapaLista {
    int id_capa;
    NodoCapaLista* siguiente;
    
    NodoCapaLista(int id) {
        id_capa = id;
        siguiente = nullptr;
    }
};

// 2. Nodo doble para la Lista Circular de Imagenes
struct NodoImagen {
    int id_imagen;
    NodoCapaLista* capas_cabeza; // Puntero a la sub-lista de capas
    
    NodoImagen* siguiente;
    NodoImagen* anterior;

    NodoImagen(int id) {
        id_imagen = id;
        capas_cabeza = nullptr;
        siguiente = anterior = nullptr;
    }
};

// 3. La clase de la Lista Circular
class ListaImagenes {
public:
    NodoImagen* cabeza;

    ListaImagenes();
    void insertar(int id_imagen);
    void agregarCapa(int id_imagen, int id_capa);
    
    // --- NUEVO METODO CRUD ---
    void eliminarImagen(int id_imagen);
};

#endif