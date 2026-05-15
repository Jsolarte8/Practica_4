#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <vector>

class Enrutador {
private:
    std::string nombre;
    std::map<std::string, int> vecinos;       // vecino -> costo directo
    std::map<std::string, int> tablaCostos;   // destino -> costo minimo
    std::map<std::string, std::vector<std::string>> tablaCaminos; // destino -> camino completo

public:
    Enrutador();
    Enrutador(const std::string& nombre);

    std::string obtenerNombre() const;

    void agregarVecino(const std::string& destino, int costo);
    void eliminarVecino(const std::string& destino);

    std::map<std::string, int> obtenerVecinos() const;

    void establecerTablaCostos(const std::map<std::string, int>& tabla);
    void establecerTablaCaminos(const std::map<std::string, std::vector<std::string>>& caminos);

    std::map<std::string, int> obtenerTablaCostos() const;
    std::map<std::string, std::vector<std::string>> obtenerTablaCaminos() const;

    void mostrarVecinos() const;
    void mostrarTablaCostos() const;
    void mostrarTablaCaminos() const;
};

#endif