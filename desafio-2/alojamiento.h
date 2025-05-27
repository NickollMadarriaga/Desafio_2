#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include <string>
#include <stdexcept>
#include "fecha.h"
using namespace std;
const int Max_Fechas =100;
class alojamiento
{
private:
    string nombre;
    int codigo;
    string documentoAnfitrion;
    string departamento;
    string municipio;
    string tipo;
    string direccion;
    double precioPorNoche;
    string amenidades;
    fecha fechaReservadas[Max_Fechas];
    int numFechas;
public:
    alojamiento();
    alojamiento(string nom, int cod, string docAnf, string dep, string mun, string tipo, string dir, double precio, string ameni);

    int getCodigo() const;
    string getNombre() const;
    string getMunicipio() const;
    string getDepartamento() const;
    string getTipo() const;
    string getDireccion () const;
    string getDocumentoAnfitrion() const;
    double getPrecioPorNoche() const;
    string getAmenidades() const;
    bool disponible(fecha f, int duracion);
    void agregarFechaReservada (fecha f);
    void mostrarAlojamiento();
    void eliminarFechaReservada(const fecha& f);
};

#endif // ALOJAMIENTO_H
