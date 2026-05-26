#include <iostream>
#include "../include/carga.h"

using namespace std;

int main() {
    cout << "Iniciando Generador de Imagenes..." << endl;
    
    // Cambio la ruta para leer mi archivo oficial de capas en lugar del de prueba
    cargarCapas("../entradas/capas.cap");
    
    return 0;
}
