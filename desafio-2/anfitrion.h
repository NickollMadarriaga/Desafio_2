#ifndef ANFITRION_H
#define ANFITRION_H
#include <string>
#include <stdexcept>
using namespace std;

class anfitrion
{
private:
    string documento;
    string nombre;
    int antiguedad;
    double puntuacion;
public:
    anfitrion();
    anfitrion(string doc, string nom, int ant, double punt);
    string getDocumento() const;
    string getNombre() const;
    int getAntiguedad() const;
    double getPuntuacion() const;
};

#endif // ANFITRION_H
