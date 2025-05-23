#include "fecha.h"

fecha::fecha() : dia(1), mes(1), anio(2024) {}

fecha::fecha(int d, int m, int a) {
    if (d < 1 || d > 31 || m < 1 || m > 12 || a < 2024) {
        throw std::invalid_argument("Fecha inválida");
    }
    dia = d; mes = m; anio = a;
}
int fecha::getDia() const {return dia; }
int fecha::getMes() const {return mes;}
int fecha::getAnio() const {return anio;}

void fecha::setDia(int d) {
    if (d < 1 || d > 31) throw std::invalid_argument("Día inválido");
    dia = d;
}

void fecha::setMes(int m) {
    if (m < 1 || m > 12) throw std::invalid_argument("Mes inválido");
    mes = m;
}

void fecha::setAnio(int a) {
    if (a < 2024) throw std::invalid_argument("Año inválido");
    anio = a;
}

