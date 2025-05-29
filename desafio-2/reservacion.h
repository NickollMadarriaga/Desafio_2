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
    int duracion; // en dias
    string metodoPago; // PSE, TCrédito
    fecha fechaPago;
    double monto;
    string anotacion; // hasta 1000 caracteres

public:
    reservacion();
    reservacion(int codRes, int codAloj, string docHuesp, fecha entrada,int dur, string metodo, fecha fPago, double monto, string nota);

    int getCodigoReserva() const;
    int getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    fecha getFechaEntrada() const;
    int getDuracion() const;
    string getMetodoPago() const;
    fecha getFechaPago() const;
    double getMonto() const;
    string getAnotacion() const;
    void setAnotacion(const string& nota);
    bool cruceFechas(fecha nuevaInicio, int nuevaDuracion);
    int generarCodigoReservaDesdeArchivo();
    void guardarEnArchivo(std::ofstream&) const;
    void mostrar() const;
};

#endif // RESERVACION_H
