#ifndef SISTEMAUDEASTAY_H
#define SISTEMAUDEASTAY_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
#include "reservacion.h"
using namespace std;

class sistemaUdeaStay
{
private:
    huesped* huespedes;
    anfitrion* anfitriones;
    alojamiento* alojamientos;
    reservacion* reservas;
    int totalHuespedes;
    int totalAnfitriones;
    int totalAlojamientos;
public:
    sistemaUdeaStay(int capacidadMax);
    sistemaUdeaStay();
    void cargarHuespedes(const char* archivo);
    void cargarAlojamientos(const char* archivo);
    void cargarAnfitriones(const char* archivo);
    void mostrarHuesped() const;
    void mostrarAnfitriones() const;
    void mostrarAlojamientos() const;
    anfitrion* buscarAnfitrion(const char* documento);
    alojamiento* buscarAlojamiento(int codigo);
    int siguienteCodigoReserva();
    void crearReserva(int codAlojamiento, fecha fInicio, int duracion);
    void actualizarReservas( int diaHoy, int mesHoy, int anioHoy);
    void consultarReservacionesAnfitrion(alojamiento alojamientos[], int cantAlojamientos,
                                         reservacion reservacionesActivas[], int cantReservas,
                                         const char* docAnfitrion,
                                         const char* fechaInicio, const char* fechaFin);
};

#endif // SISTEMAUDEASTAY_H
