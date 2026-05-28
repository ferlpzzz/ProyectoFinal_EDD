#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include "../include/carga.h"
#include "../include/matriz.h"
#include "../include/arbol_capas.h"
#include "../include/lista_imagenes.h"
#include "../include/arbol_usuarios.h" // <-- IMPORTAMOS EL ARBOL DE USUARIOS

using namespace std;

// Estructuras globales
ArbolCapas* arbol_capas = new ArbolCapas();
ListaImagenes* lista_imagenes = new ListaImagenes();
ArbolUsuarios* arbol_usuarios = new ArbolUsuarios(); // <-- NUESTRO NUEVO ARBOL

string limpiarCadena(string str) {
    string limpia = "";
    for (char c : str) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            limpia += c;
        }
    }
    return limpia;
}

// 1. LECTURA DEL ARCHIVO .CAP
void cargarCapas(string rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No pude abrir el archivo en la ruta: " << rutaArchivo << endl;
        return;
    }

    string linea;
    int id_capa_actual = -1;
    
    MatrizDispersa* matrizActual = nullptr; 

    cout << "--- INICIANDO CARGA DE CAPAS ---" << endl;

    while (getline(archivo, linea)) {
        linea = limpiarCadena(linea);
        
        if (linea.empty()) continue;

        size_t posLlaveAbre = linea.find('{');
        if (posLlaveAbre != string::npos) {
            string id_str = linea.substr(0, posLlaveAbre);
            
            if (id_str != "") {
                id_capa_actual = stoi(id_str);
                cout << ">> Creando Capa ID: " << id_capa_actual << endl;
                matrizActual = new MatrizDispersa(); 
            } else {
                cout << ">> ADVERTENCIA: Encontre una capa sin ID." << endl;
                id_capa_actual = 0;
            }
        } 
        else if (linea.find(';') != string::npos) {
            string dato = linea.substr(0, linea.find(';')); 
            stringstream ss(dato);
            string fila_str, col_str, color;

            getline(ss, fila_str, ',');
            getline(ss, col_str, ',');
            getline(ss, color, ',');

            int fila = stoi(fila_str);
            int columna = stoi(col_str);

            if (matrizActual != nullptr) {
                matrizActual->insertar(fila, columna, color);
            }
        }
        else if (linea.find('}') != string::npos) {
            if (matrizActual != nullptr) {
                arbol_capas->insertar(id_capa_actual, matrizActual);
                matrizActual = nullptr; 
            }
        }
    }

    archivo.close();
    cout << "--- LECTURA DE CAPAS FINALIZADA CON EXITO ---" << endl;
}

// 2. LECTURA DEL ARCHIVO .IM
void cargarImagenes(string rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No pude abrir el archivo en la ruta: " << rutaArchivo << endl;
        return;
    }

    string linea;
    cout << "\n--- INICIANDO CARGA DE IMAGENES ---" << endl;

    while (getline(archivo, linea)) {
        linea = limpiarCadena(linea);
        
        if (linea.empty()) continue;

        size_t posLlaveAbre = linea.find('{');
        size_t posLlaveCierra = linea.find('}');

        if (posLlaveAbre != string::npos && posLlaveCierra != string::npos) {
            string id_img_str = linea.substr(0, posLlaveAbre);
            int id_imagen = stoi(id_img_str);
            
            cout << "\n>> Procesando Imagen ID: " << id_imagen << endl;

            lista_imagenes->insertar(id_imagen);

            string capas_str = linea.substr(posLlaveAbre + 1, posLlaveCierra - posLlaveAbre - 1);
            
            if (capas_str.empty()) {
                cout << "   - Ninguna capa asignada (Se generara pixel negro)" << endl;
            } else {
                stringstream ss(capas_str);
                string id_capa;
                while (getline(ss, id_capa, ',')) {
                    cout << "   - Agregando Capa [" << id_capa << "] a la Imagen " << id_imagen << endl;
                    lista_imagenes->agregarCapa(id_imagen, stoi(id_capa));
                }
            }
        }
    }

    archivo.close();
    cout << "--- LECTURA DE IMAGENES FINALIZADA CON EXITO ---" << endl;
}

// 3. LECTURA DEL ARCHIVO .USR Y CONEXION AL ARBOL
void cargarUsuarios(string rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No pude abrir el archivo en la ruta: " << rutaArchivo << endl;
        return;
    }

    string linea;
    cout << "\n--- INICIANDO CARGA DE USUARIOS ---" << endl;

    while (getline(archivo, linea)) {
        linea = limpiarCadena(linea); 
        
        if (linea.empty()) continue;

        size_t posDosPuntos = linea.find(':');
        size_t posPuntoComa = linea.find(';');

        if (posDosPuntos != string::npos && posPuntoComa != string::npos) {
            string nombre_usuario = linea.substr(0, posDosPuntos);
            
            cout << "\n>> Procesando Usuario: " << nombre_usuario << endl;

            // AQUI OCURRE LA MAGIA: Guardamos el usuario en el arbol
            arbol_usuarios->insertar(nombre_usuario);

            string imagenes_str = linea.substr(posDosPuntos + 1, posPuntoComa - posDosPuntos - 1);
            
            if (imagenes_str.empty()) {
                cout << "   - Ninguna imagen asignada." << endl;
            } else {
                stringstream ss(imagenes_str);
                string id_img;
                while (getline(ss, id_img, ',')) {
                    // AQUI LE ASIGNAMOS LA IMAGEN AL USUARIO EN SU SUBLISTA
                    arbol_usuarios->agregarImagen(nombre_usuario, stoi(id_img));
                }
            }
        }
    }

    archivo.close();
    cout << "--- LECTURA DE USUARIOS FINALIZADA CON EXITO ---\n" << endl;
}