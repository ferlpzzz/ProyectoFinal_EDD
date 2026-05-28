#include "../include/reportes.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;

void escribirNodosABB(NodoCapas* nodo, ofstream& archivo) {
    if (nodo == nullptr) return;

    archivo << "    nodo" << nodo->id_capa << " [label=\"Capa: " << nodo->id_capa << "\"];\n";

    if (nodo->izquierda != nullptr) {
        archivo << "    nodo" << nodo->id_capa << " -> nodo" << nodo->izquierda->id_capa << ";\n";
        escribirNodosABB(nodo->izquierda, archivo);
    }
    if (nodo->derecha != nullptr) {
        archivo << "    nodo" << nodo->id_capa << " -> nodo" << nodo->derecha->id_capa << ";\n";
        escribirNodosABB(nodo->derecha, archivo);
    }
}

void graficarArbolCapas(ArbolCapas* arbol) {
    cout << "\nGenerando reporte del Arbol de Capas..." << endl;
    
    ofstream archivo("../output/arbol_capas.dot");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo dot en la carpeta output." << endl;
        return;
    }

    archivo << "digraph ArbolCapas {\n";
    archivo << "    node [shape=box, style=filled, fillcolor=lightblue];\n";
    
    if (arbol->raiz != nullptr) {
        escribirNodosABB(arbol->raiz, archivo);
    } else {
        archivo << "    vacio [label=\"Arbol Vacio\"];\n";
    }

    archivo << "}\n";
    archivo.close();

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
    archivo << "    rankdir=LR;\n"; 
    archivo << "    node [shape=box, style=filled, fillcolor=lightgreen];\n";

    if (lista->cabeza != nullptr) {
        NodoImagen* actual = lista->cabeza;
        
        archivo << "    { rank=same;\n";
        do {
            archivo << "        img" << actual->id_imagen << " [label=\"Imagen: " << actual->id_imagen << "\"];\n";
            actual = actual->siguiente;
        } while (actual != lista->cabeza);
        archivo << "    }\n";

        actual = lista->cabeza;
        do {
            archivo << "    img" << actual->id_imagen << " -> img" << actual->siguiente->id_imagen << " [dir=both];\n";
            
            if (actual->capas_cabeza != nullptr) {
                NodoCapaLista* capa = actual->capas_cabeza;
                
                archivo << "    capa" << actual->id_imagen << "_" << capa->id_capa 
                        << " [label=\"Capa: " << capa->id_capa << "\", fillcolor=lightyellow];\n";
                archivo << "    img" << actual->id_imagen << " -> capa" << actual->id_imagen << "_" << capa->id_capa << ";\n";
                
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

void escribirNodosUsuariosABB(NodoUsuario* nodo, ofstream& archivo) {
    if (nodo == nullptr) return;

    string imgs = "";
    NodoImagenUsuario* aux = nodo->imagenes_cabeza;
    while (aux != nullptr) {
        imgs += "[" + to_string(aux->id_imagen) + "] ";
        aux = aux->siguiente;
    }
    if (imgs == "") imgs = "Ninguna";

    archivo << "    \"" << nodo->nombre << "\" [label=\"Usuario: " << nodo->nombre << "\\nImagenes: " << imgs << "\"];\n";

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

    string rutaDot = "../output/imagen_final_" + to_string(id_imagen) + ".dot";
    ofstream archivo(rutaDot);
    
    archivo << "digraph ImagenFinal {\n";
    archivo << "    node [shape=none, margin=0];\n"; 
    archivo << "    tabla [label=<\n";
    archivo << "        <table border=\"0\" cellspacing=\"0\" cellpadding=\"15\">\n";

    for (int f = 1; f <= altoMax; f++) {
        archivo << "            <tr>\n";
        for (int c = 1; c <= anchoMax; c++) {
            string colorFinal = "transparent";
            
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

    string comando = "dot -Tpng " + rutaDot + " -o ../output/imagen_final_" + to_string(id_imagen) + ".png";
    system(comando.c_str());
    
    cout << "¡Imagen Final " << id_imagen << " dibujada exitosamente en la carpeta 'output'!" << endl;
}

// --- MAGIA PARA GENERAR CAPA INDIVIDUAL ---
void generarImagenPorCapa(int id_capa, ArbolCapas* arbol) {
    MatrizDispersa* matriz = arbol->buscarCapa(id_capa);
    if (matriz == nullptr) {
        cout << "Error: La capa " << id_capa << " no existe en el arbol." << endl;
        return;
    }

    cout << "\n[Procesando Capa Individual " << id_capa << "]" << endl;

    int altoMax = matriz->getMaxFila();
    int anchoMax = matriz->getMaxColumna();

    if (altoMax == 0 || anchoMax == 0) {
        cout << "La capa esta vacia." << endl;
        return;
    }

    string rutaDot = "../output/capa_individual_" + to_string(id_capa) + ".dot";
    ofstream archivo(rutaDot);
    
    archivo << "digraph CapaIndividual {\n";
    archivo << "    node [shape=none, margin=0];\n"; 
    archivo << "    tabla [label=<\n";
    archivo << "        <table border=\"0\" cellspacing=\"0\" cellpadding=\"15\">\n";

    for (int f = 1; f <= altoMax; f++) {
        archivo << "            <tr>\n";
        for (int c = 1; c <= anchoMax; c++) {
            string colorPixel = matriz->obtenerPixel(f, c);
            
            if (colorPixel != "") {
                archivo << "                <td bgcolor=\"" << colorPixel << "\"></td>\n";
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

    string comando = "dot -Tpng " + rutaDot + " -o ../output/capa_individual_" + to_string(id_capa) + ".png";
    system(comando.c_str());
    
    cout << "¡Capa individual " << id_capa << " dibujada exitosamente en la carpeta 'output'!" << endl;
}