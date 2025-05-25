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
     fecha sumarDia(int d) const;
     void mostrarFecha()const;
     bool fechaMenor(const fecha& otra) const;
     bool igual(const fecha& otra) const;
    };


#endif // FECHA_H
