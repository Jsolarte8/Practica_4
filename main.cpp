#include <iostream>
#include <limits>
#include "Red.h"

using namespace std;

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenu() {
    cout << "\n --RED DE ENRUTADORES-- \n";
    cout << "1. Agregar enrutador\n";
    cout << "2. Eliminar enrutador\n";
    cout << "3. Conectar enrutadores\n";
    cout << "4. Desconectar enrutadores\n";
    cout << "5. Mostrar enrutadores\n";
    cout << "6. Mostrar vecinos de un enrutador\n";
    cout << "7. Mostrar tabla de costos de un enrutador\n";
    cout << "8. Mostrar tabla de caminos de un enrutador\n";
    cout << "9. Calcular ruta entre dos enrutadores\n";
    cout << "10. Calcular todas las rutas desde un enrutador\n";
    cout << "11. Mostrar todas las tablas de la red\n";
    cout << "12. Cargar topologia desde archivo\n";
    cout << "13. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Red red;
    int opcion = 0;
    string origen, destino, archivo;
    int costo;

    do {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail()) {
            limpiarEntrada();
            cout << "Error: debe ingresar un numero.\n";
            continue;
        }

        try {
            switch (opcion) {
            case 1:
                cout << "Nombre del enrutador: ";
                cin >> origen;

                red.agregarEnrutador(origen);

                cout << "Enrutador agregado correctamente.\n";
                break;

            case 2:
                cout << "Nombre del enrutador a eliminar: ";
                cin >> origen;

                red.eliminarEnrutador(origen);

                cout << "Enrutador eliminado correctamente.\n";
                break;

            case 3:
                cout << "Enrutador origen: ";
                cin >> origen;

                cout << "Enrutador destino: ";
                cin >> destino;

                cout << "Costo del enlace: ";
                cin >> costo;

                if (cin.fail()) {
                    limpiarEntrada();
                    throw invalid_argument("El costo debe ser un numero entero.");
                }

                red.conectar(origen, destino, costo);

                cout << "Enrutadores conectados correctamente.\n";
                break;

            case 4:
                cout << "Enrutador origen: ";
                cin >> origen;

                cout << "Enrutador destino: ";
                cin >> destino;

                red.desconectar(origen, destino);

                cout << "Enrutadores desconectados correctamente.\n";
                break;

            case 5:
                red.mostrarEnrutadores();
                break;

            case 6:
                cout << "Nombre del enrutador: ";
                cin >> origen;

                red.mostrarVecinos(origen);
                break;

            case 7:
                cout << "Nombre del enrutador: ";
                cin >> origen;

                red.mostrarTablaCostos(origen);
                break;

            case 8:
                cout << "Nombre del enrutador: ";
                cin >> origen;

                red.mostrarTablaCaminos(origen);
                break;

            case 9:
                cout << "Enrutador origen: ";
                cin >> origen;

                cout << "Enrutador destino: ";
                cin >> destino;

                red.calcularRuta(origen, destino);
                break;

            case 10:
                cout << "Enrutador origen: ";
                cin >> origen;

                red.calcularRutasDesde(origen);
                break;

            case 11:
                red.mostrarTodasLasTablas();
                break;

            case 12:
                cout << "Nombre del archivo de topologia: ";
                cin >> archivo;

                red.cargarDesdeArchivo(archivo);

                cout << "Topologia cargada correctamente.\n";
                break;

            case 13:
                cout << "Saliendo del programa...\n";
                break;

            default:
                throw invalid_argument("Opcion invalida.");
            }
        } catch (const invalid_argument& e) {
            cout << "Excepcion invalid_argument: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Excepcion out_of_range: " << e.what() << endl;
        } catch (const runtime_error& e) {
            cout << "Excepcion runtime_error: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Excepcion general: " << e.what() << endl;
        }

    } while (opcion != 13);

    return 0;
}