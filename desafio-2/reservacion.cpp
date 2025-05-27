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
//fecha reservacion::getFechaPago() const { return fechaPago; }
double reservacion::getMonto() const { return monto; }
string reservacion::getAnotacion() const { return anotacion; }

int reservacion::generarCodigoReservaDesdeArchivo() {
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
void reservacion::setAnotacion(const string& nota) {
    if (nota.length() > 1000) throw invalid_argument("Anotación demasiado larga.");
    anotacion = nota;
}

bool reservacion::cruceFechas(fecha nuevaInicio, int nuevaDuracion) {
    fecha finActual = fechaEntrada.sumarDias(duracion); // Fecha fin de esta reserva
    fecha finNueva = nuevaInicio.sumarDias(nuevaDuracion); // Fecha fin de la reserva nueva

    // Retorna true si hay cruce: inicio nuevo < fin actual && inicio actual < fin nuevo
    return (nuevaInicio < finActual && fechaEntrada < finNueva);
}

void reservacion::mostrar() const {
    cout << "Código de Reservación: " << codigoReserva << endl;
    cout << "Código del Alojamiento: " << codigoAlojamiento << endl;
    cout << "Documento del Huésped: " << documentoHuesped << endl;
    cout << "Fecha de Entrada: ";
    fechaEntrada.mostrarFecha();
    cout << "Duración: " << duracion << " noche(s)" << endl;
    cout << "Método de Pago: " << metodoPago << endl;
    cout << "Fecha de Pago: ";
    fechaPago.mostrarFecha();
    cout << "Monto Total: $" << monto << endl;
    cout << "Anotación: " << anotacion << endl;
}

void reservacion::guardarEnArchivo(ofstream& archivo) const {
    archivo << codigoReserva << " "
            << codigoAlojamiento << " "
            << fechaEntrada.getDia() << " "
            << fechaEntrada.getMes() << " "
            << fechaEntrada.getAnio() << " "
            << duracion << " "
            << documentoHuesped << " "
            << metodoPago << " "
            << monto << " "
            << anotacion << "\n";
}
