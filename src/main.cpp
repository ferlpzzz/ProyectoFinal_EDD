#include <iostream>
#include "../include/carga.h"

using namespace std;

int main() {
    cout << "Iniciando Generador de Imagenes..." << endl;
    
    cargarCapas("../entradas/capas.cap");
    cargarImagenes("../entradas/imagenes.im");
    cargarUsuarios("../entradas/usuarios.usr"); 
    
    return 0;
}