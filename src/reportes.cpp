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

void graficarListaImagenes(ListaImagenes* lista) {
    cout << "\nGenerando reporte de la Lista de Imagenes..." << endl;
    
    ofstream archivo("../output/lista_imagenes.dot");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo dot en output." << endl;
        return;
    }

    archivo << "digraph ListaImagenes {\n";
    archivo << "    rankdir=LR;\n"; // Hace que la lista principal se dibuje de izquierda a derecha
    archivo << "    node [shape=box, style=filled, fillcolor=lightgreen];\n";

    if (lista->cabeza != nullptr) {
        NodoImagen* actual = lista->cabeza;
        
        // 1. Declarar los nodos principales (Imágenes) en la misma linea horizontal
        archivo << "    { rank=same;\n";
        do {
            archivo << "        img" << actual->id_imagen << " [label=\"Imagen: " << actual->id_imagen << "\"];\n";
            actual = actual->siguiente;
        } while (actual != lista->cabeza);
        archivo << "    }\n";

        // 2. Crear los enlaces dobles circulares y las sub-listas de capas
        actual = lista->cabeza;
        do {
            // Enlace doble al siguiente nodo principal
            archivo << "    img" << actual->id_imagen << " -> img" << actual->siguiente->id_imagen << " [dir=both];\n";
            
            // Sub-lista de capas
            if (actual->capas_cabeza != nullptr) {
                NodoCapaLista* capa = actual->capas_cabeza;
                
                // Conectar la imagen con su primera capa
                archivo << "    capa" << actual->id_imagen << "_" << capa->id_capa 
                        << " [label=\"Capa: " << capa->id_capa << "\", fillcolor=lightyellow];\n";
                archivo << "    img" << actual->id_imagen << " -> capa" << actual->id_imagen << "_" << capa->id_capa << ";\n";
                
                // Conectar las capas siguientes
                while (capa->siguiente != nullptr) {
                    archivo << "    capa" << actual->id_imagen << "_" << capa->siguiente->id_capa 
                            << " [label=\"Capa: " << capa->siguiente->id_capa << "\", fillcolor=lightyellow];\n";
                    archivo << "    capa" << actual->id_imagen << "_" << capa->id_capa 
                            << " -> capa" << actual->id_imagen << "_" << capa->siguiente->id_capa << ";\n";
                    capa = capa->siguiente;
                }
            }
            actual = actual->siguiente;
        } while (actual != lista->cabeza);

    } else {
        archivo << "    vacia [label=\"Lista Vacia\"];\n";
    }

    archivo << "}\n";
    archivo.close();

    system("dot -Tpng ../output/lista_imagenes.dot -o ../output/lista_imagenes.png");
    cout << "Reporte generado exitosamente: revisa tu carpeta 'output'." << endl;
}