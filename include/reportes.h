#ifndef REPORTES_H
#define REPORTES_H

#include "arbol_capas.h"
#include "lista_imagenes.h"
#include "arbol_usuarios.h"
#include <string>

using namespace std;

void graficarArbolCapas(ArbolCapas* arbol);
void graficarListaImagenes(ListaImagenes* lista);
void graficarArbolUsuarios(ArbolUsuarios* arbol);
void generarImagenPorLista(int id_imagen, ListaImagenes* lista, ArbolCapas* arbol);
void generarImagenPorCapa(int id_capa, ArbolCapas* arbol);

// --- NUEVA FUNCION PARA EL RECORRIDO ---
void generarImagenPorRecorrido(int n, int tipo, ArbolCapas* arbol);

#endif