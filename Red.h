#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include <vector>
#include "enrutador.h"

class Red {
private:
    std::map<std::string, Enrutador> enrutadores;

    std::map<std::string, int> calcularDistanciasDesde(
        const std::string& origen,
        std::map<std::string, std::string>* anteriores
        ) const;

    std::vector<std::string> construirCamino(
        const std::string& origen,
        const std::string& destino,
        const std::map<std::string, std::string>& anteriores
        ) const;

public:
    void agregarEnrutador(const std::string& nombre);
    void eliminarEnrutador(const std::string& nombre);

    void conectar(const std::string& origen, const std::string& destino, int costo);
    void desconectar(const std::string& origen, const std::string& destino);

    void actualizarTablas();

    void mostrarEnrutadores() const;
    void mostrarVecinos(const std::string& nombre) const;
    void mostrarTablaCostos(const std::string& nombre) const;
    void mostrarTablaCaminos(const std::string& nombre) const;
    void mostrarTodasLasTablas() const;

    void calcularRuta(const std::string& origen, const std::string& destino) const;
    void calcularRutasDesde(const std::string& origen) const;

    void cargarDesdeArchivo(const std::string& nombreArchivo);
    bool existeEnrutador(const std::string& nombre) const;
};

#endif