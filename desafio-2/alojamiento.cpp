#include "alojamiento.h"
#include <stdexcept>
#include <iostream>
using namespace std;

string alojamiento::getDocumentoAnfitrion() const {
    return documentoAnfitrion;
}
alojamiento::alojamiento()
    : nombre(""), codigo(0), documentoAnfitrion(""), departamento(""), municipio(""),
    tipo(""), direccion(""), amenidades(""), precioPorNoche(0.0), numFechas(0) {}

alojamiento::alojamiento(string nom, int cod, string docAnf, string depto,
                         string mun, string tip, string dir, double precio, string ameni) {
    if (nom.empty() || docAnf.empty() || dir.empty())
        throw invalid_argument("Nombre, documento del anfitrión o dirección no pueden estar vacíos.");
    if (precio < 0)
        throw invalid_argument("El precio no puede ser negativo.");
    if (tip != "Casa" && tip != "Apartamento")
        throw invalid_argument("Tipo de alojamiento inválido (debe ser 'Casa' o 'Apartamento').");

    nombre = nom;
    codigo = cod;
    documentoAnfitrion = docAnf;
    departamento = depto;
    municipio = mun;
    tipo = tip;
    direccion = dir;
    amenidades= ameni;
    precioPorNoche = precio;
    numFechas = 0;
}

int alojamiento::getCodigo() const { return codigo; }

string alojamiento::getNombre() const { return nombre; }

double alojamiento::getPrecioPorNoche() const { return precioPorNoche; }
string alojamiento::getAmenidades() const {return amenidades; }
string alojamiento::getMunicipio() const { return municipio;}

bool alojamiento::disponible(fecha f, int duracion) {
    for (int d = 0; d < duracion; d++) {
        fecha diaActual = f.sumarDias(d);
        for (int i = 0; i < numFechas; i++) {
            if (fechaReservadas[i] == diaActual) {
                return false;
            }
        }
    }
    return true;
}

void alojamiento::agregarFechaReservada(fecha f) {
    if (numFechas >= Max_Fechas)
        throw runtime_error("No se pueden agregar más fechas reservadas.");
    fechaReservadas[numFechas++] = f;
}

void alojamiento::mostrarAlojamiento() {
    cout << "Nombre: " << nombre << endl;
    cout << "Código: " << codigo << endl;
    cout << "Documento del anfitrión: " << documentoAnfitrion << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Amenidades: " << amenidades << endl;
    cout << "Precio por noche: " << precioPorNoche << endl;
}
void alojamiento::eliminarFechaReservada(const fecha& f) {
    for (int i = 0; i < numFechas; ++i) {
        if (fechaReservadas[i] == f) {
            // Mover los elementos posteriores una posición hacia atrás
            for (int j = i; j < numFechas - 1; ++j) {
                fechaReservadas[j] = fechaReservadas[j + 1];
            }
            numFechas--;
            break;
        }
    }
}

