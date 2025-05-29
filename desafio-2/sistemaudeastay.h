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
void mostrarConsumoRecursos(int totalHuespedes, int totalAnfitriones,
                            int totalAlojamientos, int totalReservas,
                            int totalHistorico);
class sistemaUdeaStay
{
private:
    int capacidad = 100;
     huesped* huespedes;
     anfitrion* anfitriones;
     alojamiento* alojamientos;
     reservacion* reservas;
     reservacion* historico;
     int totalHuespedes;
     int totalAnfitriones;
     int totalAlojamientos;
     int totalReservas;
     int totalHistorico;
     huesped* huespedActual;
     anfitrion* anfitrionActual;
public:
    sistemaUdeaStay();
    ~sistemaUdeaStay();
    huesped* gethuespedActual();
    anfitrion* getanfitrionActual();
    void setanfitrionActual(anfitrion* a);
    void sethuespedActual(huesped* h);
    void cargarHuespedes(const std::string&);
    void cargarAlojamientos(const std::string&);
    void cargarAnfitriones(const std::string&);
    void cargarReservas( const string& archivo);
    void cargarHistorico(const string& archivo);
    void mostrarHuesped() const;
    void mostrarAnfitriones() const;
    void mostrarAlojamientos() const;
    alojamiento* buscarAlojamiento(int codigo);
    int siguienteCodigoReserva();
    void iniciarSesion();
    void crearReserva(int codAlojamiento, fecha fInicio, int duracion);
    void actualizarHistorico( const std::string&, const std::string&);
    void consultarReservacionesAnfitrion();
    void anularReservacion();
    bool disponibilidadAlojamiento(alojamiento& a, fecha fInicio, int duracion);
    void guardarReservaEnArchivo(const reservacion& r);
    void guardarReservas( const std::string& );
    void guardarHistorico(const std::string&);
    anfitrion* buscarAnfitrion(const string& documento);
    void mostrarAlojamientosDisponibles();
    int getTotalHuespedes() const;
    int getTotalAnfitriones() const;
    int getTotalAlojamientos() const;
    int getTotalReservas() const;
    int getTotalHistorico() const;
};

#endif // SISTEMAUDEASTAY_H
