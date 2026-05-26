#include <iostream>
#include "../include/carga.h"

using namespace std;

int main() {
    cout << "Iniciando Generador de Imagenes..." << endl;
    
    // El PDF dice que el orden estricto de carga es: 1. Capas, 2. Imagenes, 3. Usuarios [cite: 194, 195, 196, 197]
    cargarCapas("../entradas/capas.cap");
    cargarImagenes("../entradas/imagenes.im");
    
    return 0;
}