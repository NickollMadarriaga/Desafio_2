#include "alojamiento.h"
#include <stdexcept>
#include <iostream>
using namespace std;
int fechasReservadas = 0;
string alojamiento::getDocumentoAnfitrion() const {
    return documentoAnfitrion;
}
alojamiento::alojamiento()
    : nombre(""), codigo(0), documentoAnfitrion(""), departamento(""), municipio(""),
    tipo(""), direccion(""), precioPorNoche(0.0), numFechas(0) {}

alojamiento::alojamiento(string nom, int cod, string docAnf, string depto,
                         string mun, string tip, string dir, double precio) {
    if (nom.empty() || docAnf.empty() || dir.empty())
        throw invalid_argument("Nombre, documento del anfitrión o dirección no pueden estar vacíos.");
    if (precio < 0)
        throw invalid_argument("El precio no puede ser negativo.");
    if (tip != "casa" && tip != "apartamento")
        throw invalid_argument("Tipo de alojamiento inválido (debe ser 'casa' o 'apartamento').");

    nombre = nom;
    codigo = cod;
    documentoAnfitrion = docAnf;
    departamento = depto;
    municipio = mun;
    tipo = tip;
    direccion = dir;
    precioPorNoche = precio;
    numFechas = 0;
}

int alojamiento::getCodigo() const { return codigo; }

string alojamiento::getNombre() const { return nombre; }

double alojamiento::getPrecioPorNoche() const { return precioPorNoche; }

bool alojamiento::disponible(fecha f, int duracion) {
    for (int i = 0; i < numFechas; i++) {
        if (fechaReservadas[i].getDia() == f.getDia() &&
            fechaReservadas[i].getMes() == f.getMes() &&
            fechaReservadas[i].getAnio() == f.getAnio()) {
            return false;
        }
    }
    return true;
}

void alojamiento::agregarFechaReservada(fecha f) {
    if (numFechas >= Max_Fechas)
        throw runtime_error("No se pueden agregar más fechas reservadas.");
    fechaReservadas[numFechas++] = f;
}

void alojamiento::mostrar() {
    cout << "Nombre: " << nombre << endl;
    cout << "Código: " << codigo << endl;
    cout << "Documento del anfitrión: " << documentoAnfitrion << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Precio por noche: " << precioPorNoche << endl;
}
void alojamiento::eliminarFechaReservada(const fecha& f) {
    for (int i = 0; i < fechasReservadas; ++i) {
        if (fechaReservadas[i].igual(f)) {
            // Mover los elementos posteriores una posición hacia atrás
            for (int j = i; j < fechasReservadas - 1; ++j) {
                fechaReservadas[j] = fechaReservadas[j + 1];
            }
            fechasReservadas--;
            break; // Solo una ocurrencia
        }
    }
}

