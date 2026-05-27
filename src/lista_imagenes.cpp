#include "../include/lista_imagenes.h"

// Constructor
ListaImagenes::ListaImagenes() {
    cabeza = nullptr;
}

// Metodo para insertar una nueva imagen en la lista circular
void ListaImagenes::insertar(int id_imagen) {
    NodoImagen* nuevo = new NodoImagen(id_imagen);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
        cout << "   [Lista] Imagen " << id_imagen << " insertada como cabeza." << endl;
    } else {
        // Buscamos el ultimo nodo (el que esta justo antes de la cabeza)
        NodoImagen* ultimo = cabeza->anterior;

        // Conectamos el nuevo nodo al final
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;

        // Cerramos el circulo conectando el nuevo con la cabeza
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        
        cout << "   [Lista] Imagen " << id_imagen << " insertada en la lista circular." << endl;
    }
}

// Metodo para agregar el ID de una capa a la sub-lista de una imagen
void ListaImagenes::agregarCapa(int id_imagen, int id_capa) {
    if (cabeza == nullptr) return;

    // Buscamos la imagen en la lista circular
    NodoImagen* temp = cabeza;
    bool encontrada = false;
    do {
        if (temp->id_imagen == id_imagen) {
            encontrada = true;
            break;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);

    // Si la encontramos, le metemos la capa al final de su sub-lista
    if (encontrada) {
        NodoCapaLista* nuevaCapa = new NodoCapaLista(id_capa);
        
        if (temp->capas_cabeza == nullptr) {
            temp->capas_cabeza = nuevaCapa;
        } else {
            NodoCapaLista* aux = temp->capas_cabeza;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevaCapa;
        }
    }
}