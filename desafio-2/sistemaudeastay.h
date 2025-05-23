#ifndef SISTEMAUDEASTAY_H
#define SISTEMAUDEASTAY_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
using namespace std;

class sistemaUdeaStay
{
private:
    huesped* huespedes;
    anfitrion* anfitriones;
    alojamiento* alojamientos;
    int totalHuespedes;
    int totalAnfitriones;
    int totalAlojamientos;
public:
    sistemaUdeaStay(int capacidadMax);
    ~SistemaUdeaStay();
    void cargarHuespedes(const char* archivo);
    void cargarAlojamientos(const char* archivo);
    void cargarAnfitriones(const char* archivo);
    void mostrarHuesped() const;
    void mostrarAnfitriones() const;
    void mostrarAlojamientos() const;
    void actualizarReservas( int diaHoy, int mesHoy, int anioHoy);
};

#endif // SISTEMAUDEASTAY_H
