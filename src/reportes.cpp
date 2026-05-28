#include "../include/reportes.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // Para usar la funcion system()

using namespace std;

// Funcion recursiva privada para escribir los nodos en el archivo
void escribirNodosABB(NodoCapas* nodo, ofstream& archivo) {
    if (nodo == nullptr) return;

    // Escribimos la caja del nodo actual
    archivo << "    nodo" << nodo->id_capa << " [label=\"Capa: " << nodo->id_capa << "\"];\n";

    // Si tiene hijo izquierdo, dibujamos la flecha
    if (nodo->izquierda != nullptr) {
        archivo << "    nodo" << nodo->id_capa << " -> nodo" << nodo->izquierda->id_capa << ";\n";
        escribirNodosABB(nodo->izquierda, archivo);
    }

    // Si tiene hijo derecho, dibujamos la flecha
    if (nodo->derecha != nullptr) {
        archivo << "    nodo" << nodo->id_capa << " -> nodo" << nodo->derecha->id_capa << ";\n";
        escribirNodosABB(nodo->derecha, archivo);
    }
}

// Funcion principal que crea el archivo .dot y genera el PNG
void graficarArbolCapas(ArbolCapas* arbol) {
    cout << "\nGenerando reporte del Arbol de Capas..." << endl;
    
    // Creamos el archivo .dot en la carpeta output
    ofstream archivo("../output/arbol_capas.dot");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo dot en la carpeta output." << endl;
        return;
    }

    // Encabezado de Graphviz
    archivo << "digraph ArbolCapas {\n";
    archivo << "    node [shape=box, style=filled, fillcolor=lightblue];\n";
    
    // Llamamos a la recursividad si el arbol no esta vacio
    if (arbol->raiz != nullptr) {
        escribirNodosABB(arbol->raiz, archivo);
    } else {
        archivo << "    vacio [label=\"Arbol Vacio\"];\n";
    }

    archivo << "}\n";
    archivo.close();

    // Ejecutamos el comando en la terminal para convertir el .dot a .png
    system("dot -Tpng ../output/arbol_capas.dot -o ../output/arbol_capas.png");
    
    cout << "Reporte generado exitosamente: revisa tu carpeta 'output'." << endl;
}