#ifndef HUESPED_H
#define HUESPED_H
#include <string>
#include <stdexcept>
using namespace std;

class huesped
{
private:
    string documento;
    string nombre;
    int antiguedad;
    double puntuacion;
public:
    huesped();
    huesped(string doc, string nom, int ant, double punt);

    string getDocumento() const;
    string getNombre() const;
};

#endif // HUESPED_H
