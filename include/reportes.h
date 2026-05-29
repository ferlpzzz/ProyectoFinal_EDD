#ifndef REPORTES_H
#define REPORTES_H

#include "arbol_capas.h"
#include "lista_imagenes.h"
#include "arbol_usuarios.h"
#include "matriz.h"
#include <string>

using namespace std;

void graficarArbolCapas(ArbolCapas* arbol);
void graficarListaImagenes(ListaImagenes* lista);
void graficarArbolUsuarios(ArbolUsuarios* arbol);
void generarImagenPorLista(int id_imagen, ListaImagenes* lista, ArbolCapas* arbol);
void generarImagenPorCapa(int id_capa, ArbolCapas* arbol);
void generarImagenPorRecorrido(int n, int tipo, ArbolCapas* arbol);

void graficarMatrizLogica(int id_capa, MatrizDispersa* matriz);

#endif