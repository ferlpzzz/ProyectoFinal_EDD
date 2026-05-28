#include <iostream>
#include "../include/carga.h"
#include "../include/arbol_capas.h"
#include "../include/reportes.h" // <-- IMPORTAMOS REPORTES

using namespace std;

// Traemos el arbol global que definimos en carga.cpp
extern ArbolCapas* arbol_capas; 

void menuPrincipal() {
    int opcion = 0;
    
    do {
        cout << "\n========================================" << endl;
        cout << "       GENERADOR DE IMAGENES      " << endl;
        cout << "========================================" << endl;
        cout << " 1. Realizar Carga Masiva" << endl;
        cout << " 2. Generar Reporte de Capas" << endl;
        cout << " 3. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Ingrese una opcion: ";
        
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\n[Iniciando Carga Masiva...]" << endl;
                cargarCapas("../entradas/capas.cap");
                cargarImagenes("../entradas/imagenes.im");
                cargarUsuarios("../entradas/usuarios.usr");
                break;
            case 2:
                // Llamamos a la nueva funcion de reportes
                graficarArbolCapas(arbol_capas);
                break;
            case 3:
                cout << "\nSaliendo del programa. ¡Nos vemos!" << endl;
                break;
            default:
                cout << "\nOpcion no valida. Por favor intente de nuevo." << endl;
        }
    } while(opcion != 3);
}

int main() {
    menuPrincipal();
    return 0;
}