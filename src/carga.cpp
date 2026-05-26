#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // La uso para separar los datos usando las comas
#include "../include/carga.h"

using namespace std;

// Funcion clave que arme para quitar espacios, saltos y tabs. Asi el programa no me truena
string limpiarCadena(string str) {
    string limpia = "";
    for (char c : str) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            limpia += c; // Solo guardo los caracteres que me sirven
        }
    }
    return limpia;
}

void cargarCapas(string rutaArchivo) {
    // Intento abrir mi archivo en modo lectura
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No pude abrir el archivo en la ruta: " << rutaArchivo << endl;
        return;
    }

    string linea;
    int id_capa_actual = -1; // Bandera para saber a que capa le estoy metiendo pixeles

    cout << "--- INICIANDO CARGA DE CAPAS ---" << endl;

    // Leo el archivo linea por linea hasta el final
    while (getline(archivo, linea)) {
        linea = limpiarCadena(linea); // Lo primero que hago es limpiar la basura de la linea
        
        if (linea.empty()) continue; // Si la linea quedo vacia, la ignoro y paso a la siguiente

        // Si encuentro una llave que abre '{', significa que empieza la definicion de una capa
        size_t posLlaveAbre = linea.find('{');
        if (posLlaveAbre != string::npos) {
            string id_str = linea.substr(0, posLlaveAbre); // Extraigo lo que esta antes de la llave
            
            if (id_str != "") {
                id_capa_actual = stoi(id_str); // Lo convierto a numero
                cout << ">> Creando Capa ID: " << id_capa_actual << endl;
            } else {
                cout << ">> ADVERTENCIA: Encontre una capa sin ID." << endl;
                id_capa_actual = 0; // Le pongo 0 por defecto para que no se arruine la insercion
            }
        } 
        // Si encuentro un punto y coma ';', significa que es la definicion de un pixel
        else if (linea.find(';') != string::npos) {
            // Le quito el punto y coma para quedarme solo con el texto "fila,columna,#color"
            string dato = linea.substr(0, linea.find(';')); 
            stringstream ss(dato);
            string fila_str, col_str, color;

            // Uso stringstream para separar los 3 datos cada vez que encuentre una coma
            getline(ss, fila_str, ',');
            getline(ss, col_str, ',');
            getline(ss, color, ',');

            // Convierto las coordenadas a enteros
            int fila = stoi(fila_str);
            int columna = stoi(col_str);

            cout << "   Pixel detectado -> Fila: " << fila << " | Col: " << columna << " | Color: " << color << endl;
            
            // TODO: Proximamente aqui llamare a mi arbol de capas para insertar la matriz
        }
        // Si encuentro la llave que cierra '}', termino de armar la capa actual
        else if (linea.find('}') != string::npos) {
            cout << "<< Fin de configuracion para la Capa " << id_capa_actual << "\n" << endl;
        }
    }

    archivo.close(); // Siempre cierro mi archivo por buenas practicas
    cout << "--- LECTURA FINALIZADA CON EXITO ---" << endl;
}