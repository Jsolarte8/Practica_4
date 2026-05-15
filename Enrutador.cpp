#include "enrutador.h"
#include <iostream>
#include <climits>

using namespace std;

Enrutador::Enrutador() {
    nombre = "";
}

Enrutador::Enrutador(const string& nombre) {
    this->nombre = nombre;
    tablaCostos[nombre] = 0;
    tablaCaminos[nombre] = {nombre};
}

string Enrutador::obtenerNombre() const {
    return nombre;
}

void Enrutador::agregarVecino(const string& destino, int costo) {
    if (costo < 0) {
        throw invalid_argument("El costo del enlace no puede ser negativo.");
    }

    vecinos[destino] = costo;
    tablaCostos[destino] = costo;
}

void Enrutador::eliminarVecino(const string& destino) {
    if (vecinos.find(destino) == vecinos.end()) {
        throw out_of_range("El vecino no existe.");
    }

    vecinos.erase(destino);
    tablaCostos.erase(destino);
    tablaCaminos.erase(destino);
}

map<string, int> Enrutador::obtenerVecinos() const {
    return vecinos;
}

void Enrutador::establecerTablaCostos(const map<string, int>& tabla) {
    tablaCostos = tabla;
}

void Enrutador::establecerTablaCaminos(const map<string, vector<string>>& caminos) {
    tablaCaminos = caminos;
}

map<string, int> Enrutador::obtenerTablaCostos() const {
    return tablaCostos;
}

map<string, vector<string>> Enrutador::obtenerTablaCaminos() const {
    return tablaCaminos;
}

void Enrutador::mostrarVecinos() const {
    cout << "\nVecinos de " << nombre << ":\n";

    if (vecinos.empty()) {
        cout << "  No tiene vecinos conectados.\n";
        return;
    }

    for (const auto& par : vecinos) {
        cout << "  -> " << par.first << " | costo: " << par.second << endl;
    }
}

void Enrutador::mostrarTablaCostos() const {
    cout << "\nTabla de costos de " << nombre << ":\n";

    if (tablaCostos.empty()) {
        cout << "  No hay costos calculados.\n";
        return;
    }

    for (const auto& par : tablaCostos) {
        cout << "  Destino: " << par.first << " | Costo: ";

        if (par.second == INT_MAX) {
            cout << "INF";
        } else {
            cout << par.second;
        }

        cout << endl;
    }
}

void Enrutador::mostrarTablaCaminos() const {
    cout << "\nTabla de caminos de " << nombre << ":\n";

    if (tablaCaminos.empty()) {
        cout << "  No hay caminos calculados.\n";
        return;
    }

    for (const auto& par : tablaCaminos) {
        cout << "  Destino: " << par.first << " | Camino: ";

        const vector<string>& camino = par.second;

        if (camino.empty()) {
            cout << "Sin camino";
        } else {
            for (size_t i = 0; i < camino.size(); i++) {
                cout << camino[i];

                if (i < camino.size() - 1) {
                    cout << " -> ";
                }
            }
        }

        cout << endl;
    }
}