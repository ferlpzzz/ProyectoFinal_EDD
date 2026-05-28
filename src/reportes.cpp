#include "../include/reportes.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 

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

// Funcion recursiva para el arbol de usuarios
void escribirNodosUsuariosABB(NodoUsuario* nodo, ofstream& archivo) {
    if (nodo == nullptr) return;

    // Armamos un string con los IDs de las imagenes que tiene el usuario
    string imgs = "";
    NodoImagenUsuario* aux = nodo->imagenes_cabeza;
    while (aux != nullptr) {
        imgs += "[" + to_string(aux->id_imagen) + "] ";
        aux = aux->siguiente;
    }
    if (imgs == "") imgs = "Ninguna";

    // Escribimos la caja del nodo actual (ponemos comillas en el ID del nodo por si el nombre tiene espacios)
    archivo << "    \"" << nodo->nombre << "\" [label=\"Usuario: " << nodo->nombre << "\\nImagenes: " << imgs << "\"];\n";

    // Llamadas recursivas y dibujo de flechas
    if (nodo->izquierda != nullptr) {
        archivo << "    \"" << nodo->nombre << "\" -> \"" << nodo->izquierda->nombre << "\";\n";
        escribirNodosUsuariosABB(nodo->izquierda, archivo);
    }
    if (nodo->derecha != nullptr) {
        archivo << "    \"" << nodo->nombre << "\" -> \"" << nodo->derecha->nombre << "\";\n";
        escribirNodosUsuariosABB(nodo->derecha, archivo);
    }
}

void graficarArbolUsuarios(ArbolUsuarios* arbol) {
    cout << "\nGenerando reporte del Arbol de Usuarios..." << endl;
    
    ofstream archivo("../output/arbol_usuarios.dot");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo dot en output." << endl;
        return;
    }

    archivo << "digraph ArbolUsuarios {\n";
    archivo << "    node [shape=box, style=filled, fillcolor=orange, fontcolor=black];\n";
    
    if (arbol->raiz != nullptr) {
        escribirNodosUsuariosABB(arbol->raiz, archivo);
    } else {
        archivo << "    vacio [label=\"Arbol Vacio\"];\n";
    }

    archivo << "}\n";
    archivo.close();

    system("dot -Tpng ../output/arbol_usuarios.dot -o ../output/arbol_usuarios.png");
    cout << "Reporte generado exitosamente: revisa tu carpeta 'output'." << endl;
}


void generarImagenPorLista(int id_imagen, ListaImagenes* lista, ArbolCapas* arbol) {
    if (lista->cabeza == nullptr) {
        cout << "Error: La lista de imagenes esta vacia." << endl;
        return;
    }

    // 1. Buscar la imagen en la lista circular
    NodoImagen* imgActual = lista->cabeza;
    bool encontrada = false;
    do {
        if (imgActual->id_imagen == id_imagen) {
            encontrada = true;
            break;
        }
        imgActual = imgActual->siguiente;
    } while (imgActual != lista->cabeza);

    if (!encontrada) {
        cout << "Error: La imagen " << id_imagen << " no existe." << endl;
        return;
    }

    cout << "\n[Procesando Imagen " << id_imagen << "]" << endl;

    // 2. Calcular el tamano maximo del lienzo (Filas y Columnas)
    int anchoMax = 0;
    int altoMax = 0;
    NodoCapaLista* capaAux = imgActual->capas_cabeza;
    
    while (capaAux != nullptr) {
        MatrizDispersa* matrizCapa = arbol->buscarCapa(capaAux->id_capa);
        if (matrizCapa != nullptr) {
            int maxF = matrizCapa->getMaxFila();
            int maxC = matrizCapa->getMaxColumna();
            if (maxF > altoMax) altoMax = maxF;
            if (maxC > anchoMax) anchoMax = maxC;
        }
        capaAux = capaAux->siguiente;
    }

    if (altoMax == 0 || anchoMax == 0) {
        cout << "La imagen no tiene capas validas (Se generaria pixel negro)." << endl;
        return;
    }

    // 3. Generar el archivo DOT con el nodo tipo HTML (Tabla de Colores)
    string rutaDot = "../output/imagen_final_" + to_string(id_imagen) + ".dot";
    ofstream archivo(rutaDot);
    
    archivo << "digraph ImagenFinal {\n";
    archivo << "    node [shape=none, margin=0];\n"; // margin=0 quita bordes extra
    archivo << "    tabla [label=<\n";
    archivo << "        <table border=\"0\" cellspacing=\"0\" cellpadding=\"15\">\n";

    // Recorremos la cuadricula celda por celda
    for (int f = 1; f <= altoMax; f++) {
        archivo << "            <tr>\n";
        for (int c = 1; c <= anchoMax; c++) {
            string colorFinal = "transparent";
            
            // Revisamos cada capa en orden. Si la capa superior tiene color, sobreescribe al de abajo.
            NodoCapaLista* capaRevisar = imgActual->capas_cabeza;
            while (capaRevisar != nullptr) {
                MatrizDispersa* mat = arbol->buscarCapa(capaRevisar->id_capa);
                if (mat != nullptr) {
                    string colorPixel = mat->obtenerPixel(f, c);
                    if (colorPixel != "") {
                        colorFinal = colorPixel;
                    }
                }
                capaRevisar = capaRevisar->siguiente;
            }
            
            // Pintamos el cuadrito de color en HTML
            if (colorFinal != "transparent") {
                archivo << "                <td bgcolor=\"" << colorFinal << "\"></td>\n";
            } else {
                archivo << "                <td bgcolor=\"white\"></td>\n";
            }
        }
        archivo << "            </tr>\n";
    }

    archivo << "        </table>\n";
    archivo << "    >];\n";
    archivo << "}\n";
    archivo.close();

    // 4. Compilar con Graphviz
    string comando = "dot -Tpng " + rutaDot + " -o ../output/imagen_final_" + to_string(id_imagen) + ".png";
    system(comando.c_str());
    
    cout << "¡Imagen Final " << id_imagen << " dibujada exitosamente en la carpeta 'output'!" << endl;
}