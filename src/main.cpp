#include <iostream>
#include "../include/carga.h"
#include "../include/arbol_capas.h"
#include "../include/lista_imagenes.h" // <-- IMPORTAMOS LA LISTA
#include "../include/reportes.h" 

using namespace std;

// Traemos las estructuras globales
extern ArbolCapas* arbol_capas; 
extern ListaImagenes* lista_imagenes; // <-- TRAEMOS LA LISTA

void menuPrincipal() {
    int opcion = 0;
    
    do {
        cout << "\n========================================" << endl;
        cout << "       GENERADOR DE IMAGENES     " << endl;
        cout << "========================================" << endl;
        cout << " 1. Realizar Carga Masiva" << endl;
        cout << " 2. Generar Reporte de Capas" << endl;
        cout << " 3. Generar Reporte de Imagenes" << endl;
        cout << " 4. Salir" << endl;
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
                graficarArbolCapas(arbol_capas);
                break;
            case 3:
                graficarListaImagenes(lista_imagenes); // <-- LLAMAMOS AL NUEVO REPORTE
                break;
            case 4:
                cout << "\nSaliendo del programa. ¡Nos vemos!" << endl;
                break;
            default:
                cout << "\nOpcion no valida. Por favor intente de nuevo." << endl;
        }
    } while(opcion != 4);
}

int main() {
    menuPrincipal();
    return 0;
}