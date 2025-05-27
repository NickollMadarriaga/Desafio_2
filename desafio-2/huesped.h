#ifndef HUESPED_H
#define HUESPED_H
#include <string>
#include <stdexcept>
#include "fecha.h"
using namespace std;

class huesped
{
private:
    string documento;
    string nombre;
    int antiguedad;
    double puntuacion;
    fecha fechasInicio[20];
    fecha fechasFin[20];
    int codigosAlojamiento[20];
    int totalReservasAsociadas;

public:
    huesped();
    huesped(string doc, string nom, int ant, double punt);
    string getDocumento() const;
    string getNombre() const;
    int getAntiguedad() const;
    double getPuntuacion() const;
    void reservasAsociadas(int codAlojamiento, fecha inicio, fecha fin);
};

#endif // HUESPED_H
