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
    fecha fechaReservadas[Max_Fechas];
    int numFechas;
public:
    alojamiento();
    alojamiento(string nom, int cod, string docAnf, string dep, string mun, string tipo, string dir, double precio);

    int getCodigo() const;
    string getNombre() const;
    string getMunicipio() const;
    string getDocumentoAnfitrion() const;
    double getPrecioPorNoche() const;
    bool disponible(fecha f, int duracion);
    void agregarFechaReservada (fecha f);
    void mostrarAlojamientos();
    void mostrar();
    void eliminarFechaReservada(const fecha& f);
};

#endif // ALOJAMIENTO_H
