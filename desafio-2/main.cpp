#include <QCoreApplication>
#include "sistemaUdeaStay.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sistemaUdeaStay sistema;
        // Cargar datos iniciales
        sistema.cargarHuespedes("huespedes.txt", Huespedes, totalHuespedes, capacidad);
        sistema.cargarAnfitriones("anfitriones.txt");
        sistema.cargarAlojamientos("alojamientos.txt");

        cout << "=== Bienvenido a UdeAStay ===\n";
        sistema.iniciarSesion();

        if (huespedActual) {
            int opcion;
            do {
                cout << "\n--- Menú Huésped ---\n";
                cout << "1. Crear reserva\n";
                cout << "2. Anular reserva\n";
                cout << "3. Salir\n";
                cout << "Seleccione una opción: ";
                cin >> opcion;

                if (opcion == 1) {
                    int codAloj, duracion, d, m, a;
                    cout << "Código del alojamiento: "; cin >> codAloj;
                    cout << "Fecha de entrada (día mes año): "; cin >> d >> m >> a;
                    cout << "Duración en noches: "; cin >> duracion;
                    sistema.crearReserva(codAloj, fecha(d, m, a), duracion);
                } else if (opcion == 2) {
                    sistema.anularReservacion();
                }

            } while (opcion != 3);
        } else if (anfitrionActual) {
            int opcion;
            do {
                cout << "\n--- Menú Anfitrión ---\n";
                cout << "1. Consultar reservaciones\n";
                cout << "2. Anular reserva\n";
                cout << "3. Salir\n";
                cout << "Seleccione una opción: ";
                cin >> opcion;

                if (opcion == 1) {
                    int d1, m1, a1, d2, m2, a2;
                    cout << "Ingrese fecha de inicio (día mes año): "; cin >> d1 >> m1 >> a1;
                    cout << "Ingrese fecha de fin (día mes año): "; cin >> d2 >> m2 >> a2;
                    sistema.consultarReservacionesAnfitrion(Alojamientos, totalAlojamientos,
                                                    reservas, totalReservas,
                                                    anfitrionActual->getDocumento(),
                                                    fecha(d1, m1, a1), fecha(d2, m2, a2));
                } else if (opcion == 2) {
                    sistema.anularReservacion();
                }

            } while (opcion != 3);
        }

        cout << "Gracias por usar UdeAStay. Hasta pronto.\n";
        return a.exec();
    }



