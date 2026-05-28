#include <iostream>
#include <string>
#include "../include/carga.h"
#include "../include/arbol_capas.h"
#include "../include/lista_imagenes.h"
#include "../include/arbol_usuarios.h"
#include "../include/reportes.h" 

using namespace std;

extern ArbolCapas* arbol_capas; 
extern ListaImagenes* lista_imagenes;
extern ArbolUsuarios* arbol_usuarios; 

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
        
        // Blindaje contra letras o caracteres invalidos
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch(opcion) {
            case 1: {
                int idBuscar;
                cout << "\nIngrese el ID de la imagen a generar: ";
                if (!(cin >> idBuscar)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: ID invalido. Debes ingresar un numero." << endl;
                    break;
                }
                generarImagenPorLista(idBuscar, lista_imagenes, arbol_capas);
                break;
            }
            case 2: {
                int idCapa;
                cout << "\nIngrese el ID de la capa a generar: ";
                if (!(cin >> idCapa)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: ID invalido. Debes ingresar un numero." << endl;
                    break;
                }
                generarImagenPorCapa(idCapa, arbol_capas);
                break;
            }
            case 3: {
                string nombreUser;
                cout << "\nIngrese el nombre del usuario (ej. userA): ";
                cin >> nombreUser;

                NodoUsuario* actual = arbol_usuarios->raiz;
                while (actual != nullptr) {
                    if (actual->nombre == nombreUser) break;
                    if (nombreUser < actual->nombre) actual = actual->izquierda;
                    else actual = actual->derecha;
                }

                if (actual == nullptr) {
                    cout << "Error: El usuario '" << nombreUser << "' no existe." << endl;
                } else {
                    if (actual->imagenes_cabeza == nullptr) {
                        cout << "El usuario '" << nombreUser << "' no tiene imagenes asignadas." << endl;
                    } else {
                        cout << "Imagenes disponibles para " << nombreUser << ": ";
                        NodoImagenUsuario* aux = actual->imagenes_cabeza;
                        while (aux != nullptr) {
                            cout << "[" << aux->id_imagen << "] ";
                            aux = aux->siguiente;
                        }
                        
                        cout << "\nIngrese el ID de la imagen que desea generar: ";
                        int idImg;
                        if (!(cin >> idImg)) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Error: Debes ingresar un numero valido." << endl;
                            break;
                        }

                        bool laTiene = false;
                        aux = actual->imagenes_cabeza;
                        while (aux != nullptr) {
                            if (aux->id_imagen == idImg) laTiene = true;
                            aux = aux->siguiente;
                        }

                        if (laTiene) {
                            generarImagenPorLista(idImg, lista_imagenes, arbol_capas);
                        } else {
                            cout << "Error: La imagen " << idImg << " no pertenece a este usuario." << endl;
                        }
                    }
                }
                break;
            }
            case 4:
                cout << "\n[Generando imagen por recorrido limitado...] -> Proximamente" << endl;
                break;
            case 5:
                cout << "\nRegresando..." << endl;
                break;
            default:
                if (opcion != 0) cout << "\nOpcion no valida." << endl;
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
        
        // Blindaje principal
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

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
                if (opcion != 0) cout << "\nOpcion no valida. Por favor intente de nuevo." << endl;
        }
    } while(opcion != 6);
}

int main() {
    menuPrincipal();
    return 0;
}