#include "fecha.h"
#include <iostream>
using namespace std;

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
#include <ctime>

// Función auxiliar para saber si un año es bisiesto
bool esBisiesto(int a) {
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}

fecha fecha::sumarDia(int d) const {
    tm tiempo = {};
    tiempo.tm_mday = dia;
    tiempo.tm_mon = mes - 1;
    tiempo.tm_year = anio - 1900;
    mktime(&tiempo);

    tiempo.tm_mday += d;
    mktime(&tiempo);  // Normaliza la fecha

    return fecha(tiempo.tm_mday, tiempo.tm_mon + 1, tiempo.tm_year + 1900);
}
void fecha::mostrarFecha() const {
    static const char* dias[] = { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado" };
    static const char* meses[] = { "enero", "febrero", "marzo", "abril", "mayo", "junio",
                                  "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };

    tm t = {};
    t.tm_mday = this->dia;
    t.tm_mon = this->mes - 1;  // mes en tm va de 0 a 11
    t.tm_year = this->anio - 1900;

    mktime(&t);  // Normaliza y calcula el día de la semana

    cout << dias[t.tm_wday] << ", " << this->dia
         << " de " << meses[this->mes - 1]
         << " del " << this->anio << endl;
}
