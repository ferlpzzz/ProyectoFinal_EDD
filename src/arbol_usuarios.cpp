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

// Metodo privado para encontrar un usuario
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

// --- LOGICA DEL CRUD DE USUARIOS ---

NodoUsuario* ArbolUsuarios::encontrarMinimo(NodoUsuario* nodo) {
    NodoUsuario* actual = nodo;
    while (actual && actual->izquierda != nullptr) {
        actual = actual->izquierda;
    }
    return actual;
}

NodoUsuario* ArbolUsuarios::eliminarRecursivo(NodoUsuario* nodo, string nombre) {
    if (nodo == nullptr) return nodo;

    if (nombre < nodo->nombre) {
        nodo->izquierda = eliminarRecursivo(nodo->izquierda, nombre);
    } else if (nombre > nodo->nombre) {
        nodo->derecha = eliminarRecursivo(nodo->derecha, nombre);
    } else {
        // Caso 1 y 2: Sin hijos o con 1 hijo
        if (nodo->izquierda == nullptr) {
            NodoUsuario* temp = nodo->derecha;
            delete nodo;
            return temp;
        } else if (nodo->derecha == nullptr) {
            NodoUsuario* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Caso 3: Dos hijos. Buscamos el sucesor inorden (el menor del lado derecho)
        NodoUsuario* temp = encontrarMinimo(nodo->derecha);
        
        // Copiamos los datos al nodo actual
        nodo->nombre = temp->nombre;
        nodo->imagenes_cabeza = temp->imagenes_cabeza;
        
        // Desconectamos las imagenes del sucesor para no borrarlas por error
        temp->imagenes_cabeza = nullptr;

        // Eliminamos el sucesor
        nodo->derecha = eliminarRecursivo(nodo->derecha, temp->nombre);
    }
    return nodo;
}

void ArbolUsuarios::eliminarUsuario(string nombre) {
    NodoUsuario* usuario = buscarUsuario(raiz, nombre);
    if (usuario == nullptr) {
        cout << "Error: El usuario '" << nombre << "' no existe." << endl;
        return;
    }
    raiz = eliminarRecursivo(raiz, nombre);
    cout << "Usuario '" << nombre << "' eliminado exitosamente." << endl;
}

void ArbolUsuarios::modificarUsuario(string nombreViejo, string nombreNuevo) {
    NodoUsuario* viejo = buscarUsuario(raiz, nombreViejo);
    if (viejo == nullptr) {
        cout << "Error: El usuario '" << nombreViejo << "' no existe." << endl;
        return;
    }
    
    // Rescatamos las imagenes antes de borrar el nodo viejo
    NodoImagenUsuario* imagenesGuardadas = viejo->imagenes_cabeza;
    viejo->imagenes_cabeza = nullptr; // Lo desconectamos
    
    // Eliminamos el nodo viejo del arbol
    raiz = eliminarRecursivo(raiz, nombreViejo);
    
    // Insertamos el nuevo nodo (esto lo ordenara correctamente en el ABB)
    insertar(nombreNuevo);
    
    // Buscamos el nodo nuevo y le pegamos sus imagenes de vuelta
    NodoUsuario* nuevo = buscarUsuario(raiz, nombreNuevo);
    if (nuevo != nullptr) {
        nuevo->imagenes_cabeza = imagenesGuardadas;
    }
    
    cout << "Usuario modificado exitosamente. ('" << nombreViejo << "' -> '" << nombreNuevo << "')" << endl;
}

void ArbolUsuarios::eliminarImagenDeUsuario(string nombre, int id_imagen) {
    NodoUsuario* usuario = buscarUsuario(raiz, nombre);
    if (usuario == nullptr) {
        cout << "Error: El usuario '" << nombre << "' no existe." << endl;
        return;
    }

    NodoImagenUsuario* actual = usuario->imagenes_cabeza;
    NodoImagenUsuario* anterior = nullptr;

    while (actual != nullptr && actual->id_imagen != id_imagen) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Error: La imagen [" << id_imagen << "] no le pertenece a '" << nombre << "'." << endl;
        return;
    }

    // Desenlazamos el nodo de la lista simple
    if (anterior == nullptr) {
        usuario->imagenes_cabeza = actual->siguiente; // Era la cabeza
    } else {
        anterior->siguiente = actual->siguiente; // Estaba en medio o al final
    }

    delete actual;
    cout << "Imagen [" << id_imagen << "] eliminada de la lista del usuario '" << nombre << "'." << endl;
}