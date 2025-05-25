#include "huesped.h"

huesped::huesped() : documento(""), nombre(""), antiguedad(0), puntuacion(0.0) {}

huesped::huesped(string doc, string nom, int ant, double punt){
    if(doc.empty()) throw invalid_argument("El documento no puede estar vacio");
    if(nom.empty()) throw invalid_argument("El nombre no puede estar vacio");
    if(ant<0) throw invalid_argument("La antiguedad no puede ser negativa");
    if(punt<0.0 || punt>5.0) throw invalid_argument("Puntuación fuera del rango");

    documento= doc;
    nombre= nom;
    antiguedad= ant;
    puntuacion= punt;
}
string huesped::getDocumento() const { return documento; }
string huesped::getNombre() const { return nombre; }
int huesped::getAntiguedad()const {return antiguedad;}
double huesped::getPuntuacion() const {return puntuacion;}
