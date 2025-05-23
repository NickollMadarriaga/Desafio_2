#include "reservacion.h"
#include <string>

reservacion::reservacion() :codigoReserva(0), codigoAlojamiento(0), documentoHuesped(''),duracion(1), metodoPago('PSE'), monto(0.0), anotacion('') {}
reservacion::reservacion(int codRes, int codAloj, string docHuesp, Fecha entrada,int dur, string metodo, fecha pago, double m, string nota) {

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

int Reservacion::getCodigoReserva() const { return codigoReserva; }
int Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
string Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
fecha Reservacion::getFechaEntrada() const { return fechaEntrada; }
int Reservacion::getDuracion() const { return duracion; }
string Reservacion::getMetodoPago() const { return metodoPago; }
fecha Reservacion::getFechaPago() const { return fechaPago; }
double Reservacion::getMonto() const { return monto; }
string Reservacion::getAnotacion() const { return anotacion; }
