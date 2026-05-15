#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>

using namespace std;

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

void Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty()) {
        throw invalid_argument("El nombre del enrutador no puede estar vacio.");
    }

    if (existeEnrutador(nombre)) {
        throw runtime_error("El enrutador ya existe.");
    }

    enrutadores[nombre] = Enrutador(nombre);
    actualizarTablas();
}

void Red::eliminarEnrutador(const string& nombre) {
    if (!existeEnrutador(nombre)) {
        throw out_of_range("El enrutador no existe.");
    }

    enrutadores.erase(nombre);

    for (auto& par : enrutadores) {
        try {
            par.second.eliminarVecino(nombre);
        } catch (...) {
            // Si no era vecino, no pasa nada.
        }
    }

    actualizarTablas();
}

void Red::conectar(const string& origen, const string& destino, int costo) {
    if (origen.empty() || destino.empty()) {
        throw invalid_argument("Los nombres de los enrutadores no pueden estar vacios.");
    }

    if (origen == destino) {
        throw invalid_argument("No se puede conectar un enrutador consigo mismo.");
    }

    if (costo < 0) {
        throw invalid_argument("El costo del enlace no puede ser negativo.");
    }

    if (!existeEnrutador(origen)) {
        enrutadores[origen] = Enrutador(origen);
    }

    if (!existeEnrutador(destino)) {
        enrutadores[destino] = Enrutador(destino);
    }

    enrutadores[origen].agregarVecino(destino, costo);
    enrutadores[destino].agregarVecino(origen, costo);

    actualizarTablas();
}

void Red::desconectar(const string& origen, const string& destino) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        throw out_of_range("Uno de los enrutadores no existe.");
    }

    enrutadores[origen].eliminarVecino(destino);
    enrutadores[destino].eliminarVecino(origen);

    actualizarTablas();
}

map<string, int> Red::calcularDistanciasDesde(
    const string& origen,
    map<string, string>* anteriores
    ) const {
    map<string, int> distancias;
    map<string, bool> visitado;

    for (const auto& par : enrutadores) {
        distancias[par.first] = INT_MAX;
        visitado[par.first] = false;
    }

    if (!existeEnrutador(origen)) {
        throw out_of_range("El enrutador origen no existe.");
    }

    distancias[origen] = 0;

    for (size_t i = 0; i < enrutadores.size(); i++) {
        string actual = "";
        int menorCosto = INT_MAX;

        for (const auto& par : distancias) {
            if (!visitado[par.first] && par.second < menorCosto) {
                menorCosto = par.second;
                actual = par.first;
            }
        }

        if (actual == "") {
            break;
        }

        visitado[actual] = true;

        map<string, int> vecinos = enrutadores.at(actual).obtenerVecinos();

        for (const auto& vecino : vecinos) {
            string destino = vecino.first;
            int costoEnlace = vecino.second;

            if (distancias[actual] != INT_MAX &&
                distancias[actual] + costoEnlace < distancias[destino]) {

                distancias[destino] = distancias[actual] + costoEnlace;

                if (anteriores != nullptr) {
                    (*anteriores)[destino] = actual;
                }
            }
        }
    }

    return distancias;
}

vector<string> Red::construirCamino(
    const string& origen,
    const string& destino,
    const map<string, string>& anteriores
    ) const {
    vector<string> camino;

    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        throw out_of_range("Origen o destino no existe.");
    }

    if (origen == destino) {
        camino.push_back(origen);
        return camino;
    }

    string actual = destino;

    while (actual != origen) {
        camino.push_back(actual);

        auto it = anteriores.find(actual);

        if (it == anteriores.end()) {
            camino.clear();
            return camino;
        }

        actual = it->second;
    }

    camino.push_back(origen);
    reverse(camino.begin(), camino.end());

    return camino;
}

void Red::actualizarTablas() {
    for (auto& par : enrutadores) {
        string origen = par.first;

        map<string, string> anteriores;
        map<string, int> distancias = calcularDistanciasDesde(origen, &anteriores);
        map<string, vector<string>> caminos;

        for (const auto& destino : enrutadores) {
            string nombreDestino = destino.first;

            if (distancias[nombreDestino] == INT_MAX) {
                caminos[nombreDestino] = vector<string>();
            } else {
                caminos[nombreDestino] = construirCamino(origen, nombreDestino, anteriores);
            }
        }

        par.second.establecerTablaCostos(distancias);
        par.second.establecerTablaCaminos(caminos);
    }
}

void Red::mostrarEnrutadores() const {
    cout << "\nEnrutadores en la red:\n";

    if (enrutadores.empty()) {
        cout << "  No hay enrutadores registrados.\n";
        return;
    }

    for (const auto& par : enrutadores) {
        cout << "  - " << par.first << endl;
    }
}

void Red::mostrarVecinos(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        throw out_of_range("El enrutador no existe.");
    }

    enrutadores.at(nombre).mostrarVecinos();
}

void Red::mostrarTablaCostos(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        throw out_of_range("El enrutador no existe.");
    }

    enrutadores.at(nombre).mostrarTablaCostos();
}

void Red::mostrarTablaCaminos(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        throw out_of_range("El enrutador no existe.");
    }

    enrutadores.at(nombre).mostrarTablaCaminos();
}

void Red::mostrarTodasLasTablas() const {
    cout << "\n===== TABLAS DE COSTOS DE TODA LA RED =====\n";

    if (enrutadores.empty()) {
        cout << "No hay enrutadores en la red.\n";
        return;
    }

    for (const auto& par : enrutadores) {
        par.second.mostrarTablaCostos();
        par.second.mostrarTablaCaminos();
    }
}

void Red::calcularRuta(const string& origen, const string& destino) const {
    if (!existeEnrutador(origen)) {
        throw out_of_range("El enrutador origen no existe.");
    }

    if (!existeEnrutador(destino)) {
        throw out_of_range("El enrutador destino no existe.");
    }

    map<string, string> anteriores;
    map<string, int> distancias = calcularDistanciasDesde(origen, &anteriores);

    if (distancias[destino] == INT_MAX) {
        cout << "\nNo existe camino entre " << origen << " y " << destino << ".\n";
        return;
    }

    vector<string> camino = construirCamino(origen, destino, anteriores);

    cout << "\nCamino mas corto de " << origen << " a " << destino << ": ";

    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i];

        if (i < camino.size() - 1) {
            cout << " -> ";
        }
    }

    cout << " | Costo total: " << distancias[destino] << endl;
}

void Red::calcularRutasDesde(const string& origen) const {
    if (!existeEnrutador(origen)) {
        throw out_of_range("El enrutador origen no existe.");
    }

    map<string, string> anteriores;
    map<string, int> distancias = calcularDistanciasDesde(origen, &anteriores);

    cout << "\nRutas desde " << origen << ":\n";

    for (const auto& par : distancias) {
        string destino = par.first;
        int costo = par.second;

        if (destino == origen) {
            continue;
        }

        cout << "  -> " << destino << " | ";

        if (costo == INT_MAX) {
            cout << "Sin camino | Costo: INF\n";
            continue;
        }

        vector<string> camino = construirCamino(origen, destino, anteriores);

        cout << "Camino: ";

        for (size_t i = 0; i < camino.size(); i++) {
            cout << camino[i];

            if (i < camino.size() - 1) {
                cout << " -> ";
            }
        }

        cout << " | Costo: " << costo << endl;
    }
}

void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de topologia.");
    }

    enrutadores.clear();

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "ROUTER") {
            string nombre;
            ss >> nombre;

            if (nombre.empty()) {
                throw invalid_argument("Linea ROUTER invalida en el archivo.");
            }

            if (!existeEnrutador(nombre)) {
                enrutadores[nombre] = Enrutador(nombre);
            }
        } else if (tipo == "ENLACE") {
            string origen, destino;
            int costo;

            ss >> origen >> destino >> costo;

            if (origen.empty() || destino.empty()) {
                throw invalid_argument("Linea ENLACE invalida en el archivo.");
            }

            if (costo < 0) {
                throw invalid_argument("El archivo contiene un costo negativo.");
            }

            if (!existeEnrutador(origen)) {
                enrutadores[origen] = Enrutador(origen);
            }

            if (!existeEnrutador(destino)) {
                enrutadores[destino] = Enrutador(destino);
            }

            enrutadores[origen].agregarVecino(destino, costo);
            enrutadores[destino].agregarVecino(origen, costo);
        } else {
            throw invalid_argument("Tipo de linea desconocido en el archivo: " + tipo);
        }
    }

    archivo.close();
    actualizarTablas();
}