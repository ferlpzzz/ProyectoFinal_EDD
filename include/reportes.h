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

// --- NUEVA FUNCION PARA GENERAR LA IMAGEN FINAL ---
void generarImagenPorLista(int id_imagen, ListaImagenes* lista, ArbolCapas* arbol);

#endif