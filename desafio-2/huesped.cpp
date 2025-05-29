#include "huesped.h"
#include <iostream>

huesped::huesped() : documento(""), nombre(""), antiguedad(0), puntuacion(0.0) {}

huesped::huesped(string doc, string nom, int ant, double punt){
    documento= doc;
    nombre= nom;
    antiguedad= ant;
    puntuacion= punt;
    totalReservasAsociadas =0;
}
string huesped::getDocumento() const { return documento; }
string huesped::getNombre() const { return nombre; }
int huesped::getAntiguedad()const {return antiguedad;}
double huesped::getPuntuacion() const {return puntuacion;}

void huesped::reservasAsociadas(int codAloj, fecha fInicio, fecha fFin) {
    if (totalReservasAsociadas < 20) {
        codigosAlojamiento[totalReservasAsociadas] = codAloj;
        fechasInicio[totalReservasAsociadas] = fInicio;
        fechasFin[totalReservasAsociadas] = fFin;
        totalReservasAsociadas++;
    } else {
        cout << "El huésped ya tiene el máximo de reservas asociadas.\n";
    }
}
