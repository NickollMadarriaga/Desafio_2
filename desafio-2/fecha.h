#ifndef FECHA_H
#define FECHA_H
#include <stdexcept>
#include <ctime>


class fecha {
private:
    int dia, mes, anio;
public:
     fecha();
     fecha(int d, int m, int a);
     int getDia() const;
     int getMes() const;
     int getAnio() const;

     void setDia(int d);
     void setMes(int m);
     void setAnio(int a);
     fecha sumarDias(int d) const;
     void mostrarFecha()const;
     bool operator==(const fecha& otra) const;
     bool operator<(const fecha& otra) const;
     bool operator>(const fecha& otra) const;
     bool esDentroDe12Meses(const fecha& inicio) const;
    };


#endif // FECHA_H
