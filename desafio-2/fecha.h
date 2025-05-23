#ifndef FECHA_H
#define FECHA_H
#include <stdexcept>
#include <ctime>

class fecha
{
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
    };


#endif // FECHA_H
