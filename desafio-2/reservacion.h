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
    reservacion(int codRes, int codAloj, string docHuesp, fecha entrada,int dur, string metodo, fecha pago, double monto, string nota);

    int getCodigoReserva() const;
    int getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    fecha getFechaEntrada() const;
    int getDuracion() const;
    string getMetodoPago() const;
    fecha getFechaPago() const;
    double getMonto() const;
    string getAnotacion() const;
    bool cruceFechas(fecha nuevaInicio, int nuevaDuracion);
    void guardarReserva(int codRes, int codAloj, int dia, int mes, int anio,
                        int duracion, const string& documentoHuesped,
                        const string& metodoPago, double monto);
    int generarCodigoReservaDesdeArchivo();
    void anularReservacion();
    void mostrar() const;
};

#endif // RESERVACION_H
