#include "sistemaudeastay.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

sistemaUdeaStay::sistemaUdeaStay() {}

void cargarHuespedes(const char* nombreArchivo, huesped* arreglo, int& total, int max) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de huéspedes.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string doc, nom;
        int ant;
        double punt;

        getline(ss, doc, ',');
        getline(ss, nom, ',');
        ss >> ant;
        ss.ignore(1); // ignorar la coma
        ss >> punt;

        if (total < max) {
            arreglo[total++] = huesped(doc, nom, ant, punt);
        }
    }

    archivo.close();
}
void cargarAnfitriones(const char* archivo) {
    ifstream in(archivo);
    if (!in.is_open()) {
        cout << "Error al abrir archivo de anfitriones.\n";
        return;
    }

    string linea;
    while (getline(in, linea) && totalAnfitriones < capacidad) {
        stringstream ss(linea);
        string doc, nom;
        int ant;
        double punt;

        getline(ss, doc, ',');
        getline(ss, nom, ',');
        ss >> ant;
        ss.ignore(1);
        ss >> punt;

        anfitriones[totalAnfitriones++] = Anfitrion(doc, nom, ant, punt);
    }

    in.close();
}

void cargarAlojamientos(const char* archivo) {
    ifstream in(archivo);
    if (!in.is_open()) {
        cout << "Error al abrir archivo de alojamientos.\n";
        return;
    }

    string linea;
    while (getline(in, linea) && totalAlojamientos < capacidad) {
        stringstream ss(linea);
        string cod, nom, docAnf, depto, muni, tipo, dir;
        double prec;

        getline(ss, cod, ',');
        getline(ss, nom, ',');
        getline(ss, docAnf, ',');
        getline(ss, depto, ',');
        getline(ss, muni, ',');
        getline(ss, tipo, ',');
        getline(ss, dir, ',');
        ss >> prec;

        alojamientos[totalAlojamientos++] = alojamiento(cod, nom, docAnf, depto, muni, tipo, dir, prec);
    }

    in.close();
}
void actualizarReservas() {
    tm fechaActual = {};
    fechaActual.tm_mday =diaHoy;
    fechaActual.tm_mon= mesHoy - 1;
    fechaActual.tm_year= anioHoy -1900;
    mktime(&fechaActual); //Normaliza

    ifstream archivo("reservas.txt");
    if (!archivo.is_open())
    ofstream archivoNuevo("reservas_temp.txt");
    ofstream historico("historico.txt", ios::app); // modo append

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int codRes, codAloj, dur, d, m, a;
        string doc, pago;
        double monto;

        ss >> codRes >> codAloj >> d >> m >> a >> dur >> doc >> pago >> monto;

        // Comparar fecha de entrada + duración con la fecha actual
        tm fechaEntrada = {};
        fechaEntrada.tm_mday = d;
        fechaEntrada.tm_mon = m - 1;
        fechaEntrada.tm_year = a - 1900;
        mktime(&fechaEntrada);

        tm fechaSalida = fechaEntrada;
        fechaSalida.tm_mday += dur;
        mktime(&fechaSalida);

        if (difftime(mktime(hoy), mktime(&fechaSalida)) > 0) {
            // Ya pasó, va al histórico
            historico << linea << endl;
        } else {
            // Sigue activa
            archivoNuevo << linea << endl;
        }
    }

    archivo.close();
    archivoNuevo.close();
    historico.close();

    remove("reservas.txt");
    rename("reservas_temp.txt", "reservas.txt");

    cout << "Histórico actualizado con éxito.\n";
}
