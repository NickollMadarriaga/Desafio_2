#include "anfitrion.h"

anfitrion::anfitrion() : documento(""), nombre(""), antiguedad(0), puntuacion(0.0) {

}
anfitrion::anfitrion(string doc, string nom, int ant, double punt){
    if(doc.empty()) throw invalid_argument("El documento no puede estar vacio");
    if(nom.empty()) throw invalid_argument("El nombre no puede estar vacio");
    if(ant<0) throw invalid_argument("La antiguedad no puede ser negativa");
    if(punt<0.0 || punt>5.0) throw invalid_argument("Puntuación fuera del rango");

    documento= doc;
    nombre= nom;
    antiguedad= ant;
    puntuacion= punt;
}
string anfitrion::getDocumento() const { return documento; }
string anfitrion::getNombre() const { return nombre; }
int anfitrion::getAntiguedad()const {return antiguedad;}

double anfitrion::getPuntuacion() const {return puntuacion;}

