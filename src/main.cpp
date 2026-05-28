#include <iostream>
#include "../include/carga.h"
#include "../include/arbol_capas.h"
#include "../include/lista_imagenes.h"
#include "../include/arbol_usuarios.h"
#include "../include/reportes.h" 

using namespace std;

// Traemos todas las estructuras globales
extern ArbolCapas* arbol_capas; 
extern ListaImagenes* lista_imagenes;
extern ArbolUsuarios* arbol_usuarios;

void menuPrincipal() {
    int opcion = 0;
    
    do {
        cout << "\n========================================" << endl;
        cout << "       GENERADOR DE IMAGENES      " << endl;
        cout << "========================================" << endl;
        cout << " 1. Realizar Carga Masiva" << endl;
        cout << " 2. Generar Reporte de Capas" << endl;
        cout << " 3. Generar Reporte de Imagenes" << endl;
        cout << " 4. Generar Reporte de Usuarios" << endl;
        cout << " 5. Salir" << endl;
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
                graficarListaImagenes(lista_imagenes);
                break;
            case 4:
                graficarArbolUsuarios(arbol_usuarios);
                break;
            case 5:
                cout << "\nSaliendo del programa. ¡Nos vemos!" << endl;
                break;
            default:
                cout << "\nOpcion no valida. Por favor intente de nuevo." << endl;
        }
    } while(opcion != 5);
}

int main() {
    menuPrincipal();
    return 0;
}