#include "reservacion.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


reservacion::reservacion() :codigoReserva(0), codigoAlojamiento(0), documentoHuesped(""), duracion(1), metodoPago("PSE"), monto(0.0), anotacion("") {}
reservacion::reservacion(int codRes, int codAloj, string docHuesp, fecha entrada,int dur, string metodo, fecha pago, double m, string nota) {

    if (docHuesp.empty()) throw invalid_argument("Documento del huésped vacío.");
    if (dur <= 0) throw invalid_argument("Duración inválida.");
    if (metodo != "PSE" && metodo != "TCredito") throw invalid_argument("Método de pago inválido.");
    if (m < 0) throw invalid_argument("Monto inválido.");
    if (nota.length() > 1000) throw invalid_argument("Anotación demasiado larga.");

    codigoReserva = codRes;
    codigoAlojamiento = codAloj;
    documentoHuesped = docHuesp;
    fechaEntrada = entrada;
    duracion = dur;
    metodoPago = metodo;
    fechaPago = pago;
    monto = m;
    anotacion = nota;
}

int reservacion::getCodigoReserva() const { return codigoReserva; }
int reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
string reservacion::getDocumentoHuesped() const { return documentoHuesped; }
fecha reservacion::getFechaEntrada() const { return fechaEntrada; }
int reservacion::getDuracion() const { return duracion; }
string reservacion::getMetodoPago() const { return metodoPago; }
fecha reservacion::getFechaPago() const { return fechaPago; }
double reservacion::getMonto() const { return monto; }
string reservacion::getAnotacion() const { return anotacion; }

int generarCodigoReservaDesdeArchivo() {
    ifstream archivo("reservas.txt");
    int maxCod = 999; // Código base si no hay reservas

    if (!archivo.is_open()) {
        // Si no existe o no se puede abrir, empezar desde 1000
        return 1000;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int codRes;
        ss >> codRes;
        if (codRes > maxCod) {
            maxCod = codRes;
        }
    }

    archivo.close();
    return maxCod + 1;
}
bool reservacion::cruceFechas(fecha nuevaInicio, int nuevaDuracion) {
    fecha finActual = fechaEntrada.sumarDia(duracion); // Fecha fin de esta reserva
    fecha finNueva = nuevaInicio.sumarDia(nuevaDuracion); // Fecha fin de la reserva nueva

    // Retorna true si hay cruce: inicio nuevo < fin actual && inicio actual < fin nuevo
    return (nuevaInicio.esMenor(finActual) && fechaEntrada.esMenor(finNueva));
}

void guardarReserva(int codRes, int codAloj, int dia, int mes, int anio,
                    int duracion, const string& documentoHuesped,
                    const string& metodoPago, double monto) {
    ofstream archivo("reservas.txt", ios::app); // abrir en modo append
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de reservas para escribir.\n";
        return;
    }

    archivo << codRes << " "
            << codAloj << " "
            << dia << " "
            << mes << " "
            << anio << " "
            << duracion << " "
            << documentoHuesped << " "
            << metodoPago << " "
            << monto << endl;

    archivo.close();
    cout << "Reserva guardada exitosamente.\n";
}
