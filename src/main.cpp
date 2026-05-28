#include <iostream>
#include "../include/carga.h"
#include "../include/arbol_capas.h"
#include "../include/lista_imagenes.h"
#include "../include/arbol_usuarios.h"
#include "../include/reportes.h" 

using namespace std;

extern ArbolCapas* arbol_capas; 
extern ListaImagenes* lista_imagenes;
extern ArbolUsuarios* arbol_usuarios; 

// --- SUB-MENU PARA GENERAR IMAGENES ---
void menuGeneracionImagenes() {
    int opcion = 0;
    do {
        cout << "\n--- GENERACION DE IMAGENES ---" << endl;
        cout << " 1. Por lista de imagenes" << endl;
        cout << " 2. Por capa individual" << endl;
        cout << " 3. Por usuario" << endl;
        cout << " 4. Por recorrido limitado" << endl;
        cout << " 5. Regresar al Menu Principal" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int idBuscar;
                cout << "\nIngrese el ID de la imagen a generar: ";
                cin >> idBuscar;
                generarImagenPorLista(idBuscar, lista_imagenes, arbol_capas);
                break;
            }
            case 2:
                cout << "\n[Generando imagen de capa individual...] -> Proximamente" << endl;
                break;
            case 3:
                cout << "\n[Generando imagen por usuario...] -> Proximamente" << endl;
                break;
            case 4:
                cout << "\n[Generando imagen por recorrido limitado...] -> Proximamente" << endl;
                break;
            case 5:
                cout << "\nRegresando..." << endl;
                break;
            default:
                cout << "\nOpcion no valida." << endl;
        }
    } while (opcion != 5);
}

void menuPrincipal() {
    int opcion = 0;
    do {
        cout << "\n========================================" << endl;
        cout << "       GENERADOR DE IMAGENES V1.0       " << endl;
        cout << "========================================" << endl;
        cout << " 1. Realizar Carga Masiva" << endl;
        cout << " 2. Generar Reporte de Capas" << endl;
        cout << " 3. Generar Reporte de Imagenes" << endl;
        cout << " 4. Generar Reporte de Usuarios" << endl;
        cout << " 5. Generar Imagen Final" << endl;
        cout << " 6. Salir" << endl;
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
                menuGeneracionImagenes();
                break;
            case 6:
                cout << "\nSaliendo del programa. ¡Nos vemos!" << endl;
                break;
            default:
                cout << "\nOpcion no valida. Por favor intente de nuevo." << endl;
        }
    } while(opcion != 6);
}

int main() {
    menuPrincipal();
    return 0;
}