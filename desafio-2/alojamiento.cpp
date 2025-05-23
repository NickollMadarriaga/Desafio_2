#include "alojamiento.h"

alojamiento::alojamiento() : nombre(""), codigo(0), documentoAnfitrion(""), departamento(""),municipio(""), tipo(""), direccion(""), precioPorNoche(0.0), numFechas(0) {}

alojamiento::alojamiento(string nom, int cod, string docAnf, string depto,string mun, string tip, string dir, double precio) {
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
        if (fechasReservadas[i].getDia() == f.getDia() &&
            fechasReservadas[i].getMes() == f.getMes() &&
            fechasReservadas[i].getAnio() == f.getAnio()) {
            return false;
        }
    }
    return true;
}

void alojamiento::agregarFechaReservada(fecha f) {
    if (numFechas >= Max_Fechas)
        throw runtime_error("No se pueden agregar más fechas reservadas.");
    fechasReservadas[numFechas++] = f;
}
