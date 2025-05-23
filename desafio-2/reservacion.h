#ifndef RESERVACION_H
#define RESERVACION_H
#include <string>
#include <stdexcept>
#include "Fecha.h"
using namespace std;

class reservacion
{
private:
    int codigoReserva;
    int codigoAlojamiento;
    string documentoHuesped;
    fecha fechaEntrada;
    int duracion; // en noches
    string metodoPago; // PSE, TCrédito
    fecha fechaPago;
    double monto;
    string anotacion; // hasta 1000 caracteres

public:
    reservacion();
    Reservacion(int codRes, int codAloj, string docHuesp, fecha entrada,
                int dur, string metodo, fecha pago, double monto, string nota);

    int getCodigoReserva() const;
    int getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    fecha getFechaEntrada() const;
    int getDuracion() const;
    string getMetodoPago() const;
    fecha getFechaPago() const;
    double getMonto() const;
    string getAnotacion() const;
};

#endif // RESERVACION_H
