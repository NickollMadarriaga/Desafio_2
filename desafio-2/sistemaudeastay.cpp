#include "sistemaudeastay.h"
#include "reservacion.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

// Variables globales necesarias
const int capacidad = 100;
huesped Huespedes[capacidad];
alojamiento Alojamientos[capacidad];
anfitrion Anfitriones[capacidad];
reservacion reservas[capacidad];
int totalAlojamientos = 0;
int totalHuespedes = 0;
int totalAnfitriones = 0;
int totalReservas = 0;
int diaHoy = 24, mesHoy = 5, anioHoy = 2025; // Simulación de fecha actual

sistemaUdeaStay::sistemaUdeaStay() {}
// Variables globales para el usuario actual
huesped* huespedActual = nullptr;
anfitrion* anfitrionActual = nullptr;

void iniciarSesion() {
    string documento;
    cout << "Ingrese su documento: ";
    cin >> documento;

    // Buscar en la lista de huéspedes
    for (int i = 0; i < totalHuespedes; ++i) {
        if (Huespedes[i].getDocumento() == documento) {
            huespedActual = &Huespedes[i];
            anfitrionActual = nullptr; // asegurarse de que el otro sea null
            cout << "Bienvenido, huésped " << huespedActual->getNombre() << ".\n";
            return;
        }
    }

    // Buscar en la lista de anfitriones
    for (int i = 0; i < totalAnfitriones; ++i) {
        if (Anfitriones[i].getDocumento() == documento) {
            anfitrionActual = &Anfitriones[i];
            huespedActual = nullptr;
            cout << "Bienvenido, anfitrión " << anfitrionActual->getNombre() << ".\n";
            return;
        }
    }

    cout << "Documento no encontrado. Por favor, verifique e intente de nuevo.\n";
}
void cargarHuespedes(const char* nombreArchivo, huesped* arreglo, int& total, int max) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de huéspedes.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string doc, nom;
        int ant;
        double punt;

        getline(ss, doc, ',');
        getline(ss, nom, ',');
        ss >> ant;
        ss.ignore(1); // ignorar la coma
        ss >> punt;

        if (total < max) {
            arreglo[total++] = huesped(doc, nom, ant, punt);
        }
    }

    archivo.close();
}

void cargarAnfitriones(const char* archivo) {
    ifstream in(archivo);
    if (!in.is_open()) {
        cout << "Error al abrir archivo de anfitriones.\n";
        return;
    }

    string linea;
    while (getline(in, linea) && totalAnfitriones < capacidad) {
        stringstream ss(linea);
        string doc, nom;
        int ant;
        double punt;

        getline(ss, doc, ',');
        getline(ss, nom, ',');
        ss >> ant;
        ss.ignore(1);
        ss >> punt;

        Anfitriones[totalAnfitriones++] = anfitrion(doc, nom, ant, punt);
    }

    in.close();
}

void cargarAlojamientos(const char* archivo) {
    ifstream in(archivo);
    if (!in.is_open()) {
        cout << "Error al abrir archivo de alojamientos.\n";
        return;
    }

    string linea;
    while (getline(in, linea) && totalAlojamientos < capacidad) {
        stringstream ss(linea);
        string codStr, nom, docAnf, depto, muni, tipo, dir;
        double prec;
        int cod;

        getline(ss, codStr, ',');
        getline(ss, nom, ',');
        getline(ss, docAnf, ',');
        getline(ss, depto, ',');
        getline(ss, muni, ',');
        getline(ss, tipo, ',');
        getline(ss, dir, ',');
        ss >> prec;
        cod = stoi(codStr);

        Alojamientos[totalAlojamientos++] = alojamiento(nom, cod, docAnf, depto, muni, tipo, dir, prec);
    }

    in.close();
}

bool disponibilidadAlojamiento(alojamiento& a, fecha fInicio, int duracion) {
    for (int i = 0; i < duracion; i++) {
        fecha f = fInicio.sumarDia(i);
        if (!a.disponible(f, 1)) {
            return false;
        }
    }
    return true;
}

alojamiento* buscarAlojamiento(int codigo) {
    for (int i = 0; i < totalAlojamientos; ++i) {
        if (Alojamientos[i].getCodigo() == codigo) {
            return &Alojamientos[i];
        }
    }
    return nullptr;
}

int siguienteCodigoReserva() {
    ifstream archivo("reservas.txt");
    int maxCodigo = 0;
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int cod;
        ss >> cod;
        if (cod > maxCodigo) {
            maxCodigo = cod;
        }
    }

    archivo.close();
    return maxCodigo + 1;
}

void guardarReservaEnArchivo(const reservacion& r) {
    ofstream archivo("reservas.txt", ios::app);
    if (archivo.is_open()) {
        archivo << r.getCodigoReserva() << " "
                << r.getCodigoAlojamiento() << " "
                << r.getFechaEntrada().getDia() << " "
                << r.getFechaEntrada().getMes() << " "
                << r.getFechaEntrada().getAnio() << " "
                << r.getDuracion() << " "
                << r.getDocumentoHuesped() << " "
                << r.getMetodoPago() << " "
                << r.getMonto() << "\n";
        archivo.close();
    }
}

void crearReserva(int codAlojamiento, fecha fInicio, int duracion) {
    alojamiento* a = buscarAlojamiento(codAlojamiento);
    if (!a || !a->disponible(fInicio, duracion)) {
        cout << "El alojamiento no está disponible en las fechas indicadas.\n";
        return;
    }

    for (int i = 0; i < totalReservas; ++i) {
        if (reservas[i].getDocumentoHuesped() == huespedActual->getDocumento() &&
            reservas[i].cruceFechas(fInicio, duracion)) {
            cout << "Ya tienes otra reserva activa en esas fechas.\n";
            return;
        }
    }

    int nuevoCodigo = siguienteCodigoReserva();

    // Pedir al huésped la fecha del pago (fecha actual)
    int dia, mes, anio;
    cout << "Ingrese la fecha de hoy para el registro del pago:\n";
    cout << "Día: "; cin >> dia;
    cout << "Mes: "; cin >> mes;
    cout << "Año: "; cin >> anio;
    fecha fPago(dia, mes, anio);

    double monto = a->getPrecioPorNoche() * duracion;

    string metodo;
    cout << "1. PSE\n2. Tarjeta de crédito\nIngrese el método de pago: ";
    getline(cin >> ws, metodo);

    reservacion nueva(nuevoCodigo, codAlojamiento, huespedActual->getDocumento(),
                      fInicio, duracion, metodo, fPago, monto, "Reserva confirmada");
    reservas[totalReservas++] = nueva;
    guardarReservaEnArchivo(nueva);

    for (int i = 0; i < duracion; i++) {
        fecha f = fInicio.sumarDia(i);
        a->agregarFechaReservada(f);
    }

    cout << "\nReserva confirmada:\n";
    cout << "Código de reserva: " << nuevoCodigo << endl;
    cout << "Nombre del huésped: " << huespedActual->getNombre() << endl;
    cout << "Código del alojamiento: " << codAlojamiento << endl;
    cout << "Desde: "; fInicio.mostrarFecha();
    cout << "Hasta: "; fInicio.sumarDia(duracion).mostrarFecha();
}

anfitrion* buscarAnfitrion(const string& documento) {
    for (int i = 0; i < totalAnfitriones; i++) {
        if (Anfitriones[i].getDocumento() == documento) {
            return &Anfitriones[i];
        }
    }
    return nullptr;
}
