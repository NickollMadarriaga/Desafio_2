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

extern const int capacidad;
extern huesped Huespedes[];
extern alojamiento Alojamientos[];
extern anfitrion Anfitriones[];
extern reservacion reservas[];
extern int totalAlojamientos;
extern int totalHuespedes;
extern int totalAnfitriones;
extern int totalReservas;
extern huesped* huespedActual;
extern anfitrion* anfitrionActual;
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
    void cargarHuespedes(const char* archivo, huesped arreglo[], int& total, int capacidad);
    void cargarAlojamientos(const char* archivo);
    void cargarAnfitriones(const char* archivo);
    void mostrarHuesped() const;
    void mostrarAnfitriones() const;
    void mostrarAlojamientos() const;
    anfitrion* buscarAnfitrion(const char* documento);
    alojamiento* buscarAlojamiento(int codigo);
    int siguienteCodigoReserva();
    void iniciarSesion();
    void crearReserva(int codAlojamiento, fecha fInicio, int duracion);
    void actualizarReservas( int diaHoy, int mesHoy, int anioHoy);
    void consultarReservacionesAnfitrion(alojamiento alojamientos[], int cantAlojamientos,
                                         reservacion reservacionesActivas[], int cantReservas,
                                         const std::string& docAnfitrion,
                                         const fecha& fechaInicio, const fecha& fechaFin);
    void anularReservacion();
    bool disponibilidadAlojamiento(alojamiento& a, fecha fInicio, int duracion);
    void guardarReservaEnArchivo(const reservacion& r);
    anfitrion* buscarAnfitrion(const string& documento);
};

#endif // SISTEMAUDEASTAY_H
