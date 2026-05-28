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

// --- LOGICA DEL CRUD DE IMAGENES ---
void ListaImagenes::eliminarImagen(int id_imagen) {
    if (cabeza == nullptr) {
        cout << "Error: La lista de imagenes esta vacia." << endl;
        return;
    }

    NodoImagen* actual = cabeza;
    bool encontrada = false;

    // Buscamos el nodo a eliminar
    do {
        if (actual->id_imagen == id_imagen) {
            encontrada = true;
            break;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrada) {
        cout << "Error: La imagen [" << id_imagen << "] no existe en la lista general." << endl;
        return;
    }

    // 1. Antes de borrar la imagen, liberamos su sub-lista de capas de la memoria
    NodoCapaLista* capaAux = actual->capas_cabeza;
    while (capaAux != nullptr) {
        NodoCapaLista* borrarCapa = capaAux;
        capaAux = capaAux->siguiente;
        delete borrarCapa;
    }

    // 2. Desenlazamos el nodo de la lista circular
    if (actual->siguiente == actual) {
        // Caso A: Era la unica imagen en toda la lista
        cabeza = nullptr;
    } else {
        // Caso B: Hay mas imagenes. Conectamos al anterior con el siguiente.
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
        
        // Si la imagen a borrar era la cabeza, movemos la cabeza al siguiente nodo
        if (actual == cabeza) {
            cabeza = actual->siguiente;
        }
    }

    // 3. Borramos el nodo fisicamente
    delete actual;
    cout << "Imagen [" << id_imagen << "] eliminada de la lista circular exitosamente." << endl;
}