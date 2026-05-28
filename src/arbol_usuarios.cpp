#include "../include/arbol_usuarios.h"

ArbolUsuarios::ArbolUsuarios() {
    raiz = nullptr;
}

void ArbolUsuarios::insertar(string nombre) {
    raiz = insertarRecursivo(raiz, nombre);
}

NodoUsuario* ArbolUsuarios::insertarRecursivo(NodoUsuario* nodo, string nombre) {
    if (nodo == nullptr) {
        cout << "   [Arbol Usuarios] Usuario '" << nombre << "' guardado en el ABB." << endl;
        return new NodoUsuario(nombre);
    }

    // Comparamos alfabeticamente
    if (nombre < nodo->nombre) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, nombre);
    } else if (nombre > nodo->nombre) {
        nodo->derecha = insertarRecursivo(nodo->derecha, nombre);
    } else {
        cout << "   [Arbol Usuarios] El usuario '" << nombre << "' ya existe." << endl;
    }

    return nodo;
}

// Metodo privado para encontrar un usuario y meterle sus imagenes
NodoUsuario* ArbolUsuarios::buscarUsuario(NodoUsuario* nodo, string nombre) {
    if (nodo == nullptr || nodo->nombre == nombre) {
        return nodo;
    }
    if (nombre < nodo->nombre) {
        return buscarUsuario(nodo->izquierda, nombre);
    }
    return buscarUsuario(nodo->derecha, nombre);
}

void ArbolUsuarios::agregarImagen(string nombre, int id_imagen) {
    NodoUsuario* usuario = buscarUsuario(raiz, nombre);
    
    if (usuario != nullptr) {
        NodoImagenUsuario* nuevaImg = new NodoImagenUsuario(id_imagen);
        
        if (usuario->imagenes_cabeza == nullptr) {
            usuario->imagenes_cabeza = nuevaImg;
        } else {
            NodoImagenUsuario* aux = usuario->imagenes_cabeza;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevaImg;
        }
        cout << "   - Imagen [" << id_imagen << "] asignada a '" << nombre << "'" << endl;
    }
}