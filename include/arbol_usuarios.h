#ifndef ARBOL_USUARIOS_H
#define ARBOL_USUARIOS_H

#include <iostream>
#include <string>

using namespace std;

// 1. Nodo simple para guardar las imagenes que tiene asignadas el usuario
struct NodoImagenUsuario {
    int id_imagen;
    NodoImagenUsuario* siguiente;
    
    NodoImagenUsuario(int id) {
        id_imagen = id;
        siguiente = nullptr;
    }
};

// 2. Nodo del Arbol para el Usuario
struct NodoUsuario {
    string nombre;
    NodoImagenUsuario* imagenes_cabeza; // La sub-lista de sus imagenes
    
    NodoUsuario* izquierda;
    NodoUsuario* derecha;

    NodoUsuario(string nom) {
        nombre = nom;
        imagenes_cabeza = nullptr;
        izquierda = derecha = nullptr;
    }
};

// 3. La clase del Arbol de Usuarios
class ArbolUsuarios {
public:
    NodoUsuario* raiz;

    ArbolUsuarios();
    void insertar(string nombre);
    void agregarImagen(string nombre, int id_imagen);

private:
    NodoUsuario* insertarRecursivo(NodoUsuario* nodo, string nombre);
    NodoUsuario* buscarUsuario(NodoUsuario* nodo, string nombre);
};

#endif