#include <QCoreApplication>
#include "sistemaUdeaStay.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sistemaUdeaStay sistema;
    sistema.cargarHuespedes(std::string("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\huespedes.txt"));
    sistema.cargarAnfitriones(std::string("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\anfitriones.txt"));
    sistema.cargarAlojamientos(std::string("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\alojamientos.txt"));
    sistema.cargarReservas("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\reservas.txt");
    sistema.cargarHistorico("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\historico.txt");

    int opcion;
    do {
        cout << "\n=== Menú Principal ===\n";
        cout << "1. Iniciar sesión\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                sistema.iniciarSesion();
                if (sistema.gethuespedActual() != nullptr) {
                    int opH;
                    do {
                        cout << "\n=== Menú Huésped ===\n";
                        cout << "1. Ver alojamientos disponibles\n";
                        cout << "2. Anular reservación\n";
                        cout << "0. Cerrar sesión\n";
                        cout << "Opción: ";
                        cin >> opH;
                        switch (opH) {
                            case 1:
                                sistema.mostrarAlojamientosDisponibles();
                                break;
                            case 2:
                                sistema.anularReservacion();
                                break;
                            case 0:
                                sistema.sethuespedActual(nullptr);
                                break;
                            default:
                                cout << "Opción no válida.\n";
                        }
                    } while (opH != 0);
                } else if (sistema.getanfitrionActual() != nullptr) {
                    int opA;
                    do {
                        cout << "\n=== Menú Anfitrión ===\n";
                        cout << "1. Consultar reservaciones en mis alojamientos\n";
                        cout << "2. Actualizar histórico de reservaciones\n";
                        cout << "0. Cerrar sesión\n";
                        cout << "Opción: ";
                        cin >> opA;
                        switch (opA) {
                            case 1:
                                sistema.consultarReservacionesAnfitrion();
                                break;
                            case 2:
                                sistema.actualizarHistorico("C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\reservas.txt", "C:\\Users\\nicko\\OneDrive\\Documentos\\GitHub\\Desafio_2\\desafio-2\\build\\historico.txt");
                                break;
                            case 0:
                                sistema.setanfitrionActual(nullptr);
                                break;
                            default:
                                cout << "Opción no válida.\n";
                        }
                    } while (opA != 0);
                }
                break;

            case 0:
                cout << "Gracias por usar UdeAStay. ¡Hasta luego!\n";
                break;

            default:
                cout << "Opción no válida.\n";
        }

    } while (opcion != 0);

    return 0;
}
