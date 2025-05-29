#include "sistemaudeastay.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>
#include <limits>
using namespace std;

long long contadorIteraciones = 0;

sistemaUdeaStay::sistemaUdeaStay() {
    capacidad = 100;
    huespedes = new huesped[capacidad];
    anfitriones = new anfitrion[capacidad];
    alojamientos = new alojamiento[capacidad];
    reservas = new reservacion[capacidad];
    historico= new reservacion[capacidad];
    totalHuespedes = 0;
    totalAnfitriones = 0;
    totalAlojamientos = 0;
    totalReservas = 0;
    huespedActual = nullptr;
    anfitrionActual = nullptr;
}
int sistemaUdeaStay::getTotalHuespedes() const { return totalHuespedes; }
int sistemaUdeaStay::getTotalAnfitriones() const { return totalAnfitriones; }
int sistemaUdeaStay::getTotalAlojamientos() const { return totalAlojamientos; }
int sistemaUdeaStay::getTotalReservas() const { return totalReservas; }
int sistemaUdeaStay::getTotalHistorico() const { return totalHistorico; }
huesped* sistemaUdeaStay::gethuespedActual() {
    return huespedActual;
}
anfitrion* sistemaUdeaStay::getanfitrionActual() {
    return anfitrionActual;
}
void sistemaUdeaStay::sethuespedActual(huesped* h) {
    huespedActual = h;
}
void sistemaUdeaStay::setanfitrionActual(anfitrion* a) {
    anfitrionActual = a;
}
string normalizarTexto(const string& texto) {
    string resultado;
    for (char c : texto) {
        switch (c) {
        case 'á': case 'Á': resultado += 'a'; break;
        case 'é': case 'É': resultado += 'e'; break;
        case 'í': case 'Í': resultado += 'i'; break;
        case 'ó': case 'Ó': resultado += 'o'; break;
        case 'ú': case 'Ú': resultado += 'u'; break;
        default:
            resultado += tolower(c); // aquí sí usamos tolower para todo lo demás
        }
    }
    return resultado;
}
void sistemaUdeaStay::iniciarSesion() {
    string documento;
    cout << "Ingrese su documento: ";
    cin >> documento;

    // Buscar en la lista de huéspedes
    for (int i = 0; i < totalHuespedes; ++i) {
        contadorIteraciones++;
        if (huespedes[i].getDocumento() == documento) {
            huespedActual = &huespedes[i];
            anfitrionActual = nullptr; // asegurarse de que el otro sea null
            cout << "Bienvenido, huésped " << huespedActual->getNombre() << ".\n";
            return;
        }
    }

    // Buscar en la lista de anfitriones
    for (int i = 0; i < totalAnfitriones; ++i) {
        contadorIteraciones++;
        if (anfitriones[i].getDocumento() == documento) {
            anfitrionActual = &anfitriones[i];
            huespedActual = nullptr;
            cout << "Bienvenido, anfitrión " << anfitrionActual->getNombre() << ".\n";
            return;
        }
    }

    cout << "Documento no encontrado. Por favor, verifique e intente de nuevo.\n";
}
void sistemaUdeaStay::cargarHuespedes(const std::string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de huéspedes.\n";
        return;
    }

    totalHuespedes = 0;
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string documento, nombre, antigStr, puntStr, reservasStr;

        // Leer los 4 campos principales
        getline(ss, documento, ',');
        getline(ss, nombre, ',');
        getline(ss, antigStr, ',');
        getline(ss, puntStr, ',');

        int antiguedad = stoi(antigStr);
        double puntuacion = stod(puntStr);

        // Crear el huésped directamente en el arreglo (como objeto)
        if (totalHuespedes < capacidad) {
            huespedes[totalHuespedes] = huesped(documento, nombre, antiguedad, puntuacion);
        } else {
            cout << "Capacidad máxima de huéspedes alcanzada.\n";
            break;
        }

        // Leer reservas asociadas si existen
        if (getline(ss, reservasStr, ',')) {
            stringstream sr(reservasStr);
            string reserva;

            while (getline(sr, reserva, ';')) {
                stringstream rstream(reserva);
                string codAlojStr, fInicioStr, fFinStr;

                getline(rstream, codAlojStr, '|');
                getline(rstream, fInicioStr, '|');
                getline(rstream, fFinStr, '|');

                int codAloj = stoi(codAlojStr);

                int y1, m1, d1, y2, m2, d2;
                sscanf(fInicioStr.c_str(), "%d-%d-%d", &y1, &m1, &d1);
                sscanf(fFinStr.c_str(), "%d-%d-%d", &y2, &m2, &d2);

                fecha fInicio(d1, m1, y1);
                fecha fFin(d2, m2, y2);

                // Acceder al huésped ya almacenado y agregarle la reserva
                huespedes[totalHuespedes].reservasAsociadas(codAloj, fInicio, fFin);
            }
        }

        totalHuespedes++;
    }

    archivo.close();
}

void sistemaUdeaStay::cargarAnfitriones(const std::string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de anfitriones.\n";
        return;
    }
    totalAnfitriones = 0;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string doc, nom;
        int ant;
        double punt;

        getline(ss, doc, ',');
        getline(ss, nom, ',');
        ss >> ant;
        ss.ignore(1);  // Para ignorar la coma o espacio después del entero
        ss >> punt;

        if (totalAnfitriones < capacidad) {
            anfitriones[totalAnfitriones++] = anfitrion(doc, nom, ant, punt);
        }
    }
    archivo.close();
}

void sistemaUdeaStay::cargarAlojamientos(const std::string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de alojamientos.\n";
        return;
    }
    totalAlojamientos = 0;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string codStr, nom, docAnf, depto, muni, tipo, dir, precStr, ameni;
        double prec;
        int cod;

        getline(ss, codStr, ',');
        getline(ss, nom, ',');
        getline(ss, docAnf, ',');
        getline(ss, depto, ',');
        getline(ss, muni, ',');
        getline(ss, tipo, ',');
        getline(ss, dir, ',');
        getline(ss, precStr, ',');
        getline(ss, ameni);

        cod = stoi(codStr);
        prec = stod(precStr);
        if (totalAlojamientos < capacidad) {
            alojamientos[totalAlojamientos++] = alojamiento(nom, cod, docAnf, depto, muni, tipo, dir, prec, ameni);
        }
    }
    archivo.close();
}
void sistemaUdeaStay::cargarReservas(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de reservas.\n";
        return;
    }

    totalReservas = 0;
    int codReserva, codAlojamiento, dia, mes, anio, duracion;
    int diaPago, mesPago, anioPago; // nuevos para la fecha de pago
    string documentoHuesped, metodoPago, anotacion;
    double monto;

    while (archivo >> codReserva >> codAlojamiento >> dia >> mes >> anio >> duracion
           >> documentoHuesped >> metodoPago >> diaPago >> mesPago >> anioPago >> monto) {
            contadorIteraciones++;
        getline(archivo >> ws, anotacion);  // Anotación puede contener espacios

        fecha f(dia, mes, anio);           // fecha de entrada
        fecha fPago(diaPago, mesPago, anioPago); // fecha de pago

        reservacion r(codReserva, codAlojamiento, documentoHuesped,
                      f, duracion, metodoPago, fPago, monto, anotacion);

        reservas[totalReservas++] = r;

        alojamiento* a = buscarAlojamiento(codAlojamiento);
        if (a != nullptr) {
            for (int i = 0; i < duracion; ++i) {
                a->agregarFechaReservada(f.sumarDias(i));
            }
        }
    }

    archivo.close();
}

void sistemaUdeaStay::cargarHistorico(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo histórico.\n";
        return;
    }

    totalHistorico = 0;
    int codReserva, codAlojamiento, dia, mes, anio, duracion;
    int diaPago, mesPago, anioPago; // nuevos
    string documentoHuesped, metodoPago, anotacion;
    double monto;

    while (archivo >> codReserva >> codAlojamiento >> dia >> mes >> anio >> duracion
           >> documentoHuesped >> metodoPago >> diaPago >> mesPago >> anioPago >> monto) {
            contadorIteraciones++;
        getline(archivo >> ws, anotacion);  // Anotación puede contener espacios

        fecha f(dia, mes, anio);            // fecha de entrada
        fecha fPago(diaPago, mesPago, anioPago);  // fecha de pago

        reservacion r(codReserva, codAlojamiento, documentoHuesped,
                      f, duracion, metodoPago, fPago, monto, anotacion);

        historico[totalHistorico++] = r;
    }

    archivo.close();
}
void sistemaUdeaStay::guardarHistorico(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar el histórico.\n";
        return;
    }

    for (int i = 0; i < totalHistorico; ++i) {
        contadorIteraciones++;
        historico[i].guardarEnArchivo(archivo);
    }

    archivo.close();
}

bool sistemaUdeaStay::disponibilidadAlojamiento(alojamiento& a, fecha fInicio, int duracion) {
    for (int i = 0; i < duracion; i++) {
        contadorIteraciones++;
        fecha f = fInicio.sumarDias(i);
        if (!a.disponible(f, 1)) {
            return false;
        }
    }
    return true;
}

alojamiento* sistemaUdeaStay::buscarAlojamiento(int codigo) {
    for (int i = 0; i < totalAlojamientos; ++i) {
        contadorIteraciones++;
        if (alojamientos[i].getCodigo() == codigo) {
            return &alojamientos[i];
        }
    }
    return nullptr;
}

int sistemaUdeaStay::siguienteCodigoReserva() {
    ifstream archivo("reservas.txt");
    int maxCodigo = 0;
    string linea;

    while (getline(archivo, linea)) {
        contadorIteraciones++;
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

void sistemaUdeaStay::guardarReservaEnArchivo(const reservacion& r) {
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
                << r.getFechaPago().getDia() << " "
                << r.getFechaPago().getMes()<< " "
                << r.getFechaPago().getAnio()<< " "
                << r.getMonto() << " "
                << r.getAnotacion() << "\n";
        archivo.close();
    }
}

void sistemaUdeaStay::crearReserva(int codAlojamiento, fecha fInicio, int duracion) {
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

    // Solicitar fecha del pago con validación
    int dia, mes, anio;
    try {
        cout << "Ingrese la fecha de hoy para el registro del pago:\n";
        cout << "Día: "; cin >> dia;
        cout << "Mes: "; cin >> mes;
        cout << "Año: "; cin >> anio;

        if (cin.fail() || dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1900) {
            throw runtime_error("Fecha inválida. Intente de nuevo.");
        }
    } catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: " << e.what() << endl;
        return;
    }
    fecha fPago(dia, mes, anio);

    double monto = a->getPrecioPorNoche() * duracion;

    string metodo;
    while (true) {
        try {
            cout << "1. PSE\n2. Tarjeta de crédito\nIngrese el método de pago: ";
            getline(cin >> ws, metodo);

            string metodoNormalizado = normalizarTexto(metodo);

            if (metodoNormalizado == "1" || metodoNormalizado == "pse") {
                metodo = "PSE";
                break;
            } else if (metodoNormalizado == "2" || metodoNormalizado == "tarjeta de credito" || metodoNormalizado == "tarjeta crédito" || metodoNormalizado == "tarjeta") {
                metodo = "Tarjeta de crédito";
                break;
            } else {
                throw invalid_argument("Método de pago no válido.");
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Intenta de nuevo.\n";
        }
    }


    // Pedir anotación opcional con validación
    string anotacion;
    try {
        string respuesta;
        cout << "¿Desea agregar una anotación especial? (s/n): ";
        getline(cin, respuesta);
        if (respuesta == "s" || respuesta == "S") {
            cout << "Ingrese la anotación: ";
            getline(cin, anotacion);
        } else {
            anotacion = "Reserva confirmada";
        }
    } catch (...) {
        anotacion = "Reserva confirmada";  // valor por defecto si algo falla
    }

    reservacion nueva(nuevoCodigo, codAlojamiento, huespedActual->getDocumento(),
                      fInicio, duracion, metodo, fPago, monto, anotacion);
    reservas[totalReservas++] = nueva;
    guardarReservaEnArchivo(nueva);

    for (int i = 0; i < duracion; i++) {
        contadorIteraciones++;
        fecha f = fInicio.sumarDias(i);
        a->agregarFechaReservada(f);
    }

    cout << "\nReserva confirmada:\n";
    cout << "Código de reserva: " << nuevoCodigo << endl;
    cout << "Nombre del huésped: " << huespedActual->getNombre() << endl;
    cout << "Código del alojamiento: " << codAlojamiento << endl;
    cout << "Desde: "; fInicio.mostrarFecha();
    cout << "Hasta: "; fInicio.sumarDias(duracion - 1).mostrarFecha();
    if (!anotacion.empty())
        cout << "Anotación: " << anotacion << endl;
}

anfitrion* sistemaUdeaStay::buscarAnfitrion(const string& documento) {
    for (int i = 0; i < totalAnfitriones; i++) {
        contadorIteraciones++;
        if (anfitriones[i].getDocumento() == documento) {
            return &anfitriones[i];
        }
    }
    return nullptr;
}

void sistemaUdeaStay::anularReservacion() {
    int codigo;
    cout << "Ingrese el código de la reservación a anular: ";
    cin >> codigo;

    int indice = -1;

    // Buscar la reservación por código
    for (int i = 0; i < totalReservas; ++i) {
        contadorIteraciones++;
        if (reservas[i].getCodigoReserva() == codigo) {
            // Verificar si el usuario actual tiene permiso
            alojamiento* a = buscarAlojamiento(reservas[i].getCodigoAlojamiento());
            bool permisoHuesped = (huespedActual != nullptr && reservas[i].getDocumentoHuesped() == huespedActual->getDocumento());
            bool permisoAnfitrion = (anfitrionActual != nullptr && a && a->getDocumentoAnfitrion() == anfitrionActual->getDocumento());

            if (permisoHuesped || permisoAnfitrion) {
                indice = i;
            } else {
                cout << "No tiene permisos para anular esta reservación.\n";
                return;
            }
            break;
        }
    }

    if (indice == -1) {
        cout << "Reservación no encontrada o no tiene permisos.\n";
        return;
    }

    // Liberar las fechas en el alojamiento correspondiente
    alojamiento* a = buscarAlojamiento(reservas[indice].getCodigoAlojamiento());
    if (a) {
        fecha fInicio = reservas[indice].getFechaEntrada();
        int duracion = reservas[indice].getDuracion();
        for (int i = 0; i < duracion; ++i) {
            a->eliminarFechaReservada(fInicio.sumarDias(i));
        }
    }

    // Eliminar del arreglo
    for (int i = indice; i < totalReservas - 1; ++i) {
        contadorIteraciones++;
        reservas[i] = reservas[i + 1];
    }
    totalReservas--;

    // Reescribir archivo actualizado
    ofstream out("reservas.txt");
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo de reservas para actualizar.\n";
        return;
    }

    for (int i = 0; i < totalReservas; ++i) {
        contadorIteraciones++;
        out << reservas[i].getCodigoReserva() << " "
            << reservas[i].getCodigoAlojamiento() << " "
            << reservas[i].getFechaEntrada().getDia() << " "
            << reservas[i].getFechaEntrada().getMes() << " "
            << reservas[i].getFechaEntrada().getAnio() << " "
            << reservas[i].getDuracion() << " "
            << reservas[i].getDocumentoHuesped() << " "
            << reservas[i].getMetodoPago() << " "
            << reservas[i].getMonto() << " "
        << reservas[i].getAnotacion() << "\n";
    }

    out.close();

    cout << "Reservación anulada exitosamente y fechas liberadas.\n";
}
void sistemaUdeaStay::guardarReservas(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // borra el contenido anterior
    if (!archivo) {
        cout << "Error al abrir el archivo de reservas para guardar.\n";
        return;
    }
    for (int i = 0; i < totalReservas; ++i) {
        contadorIteraciones++;
        reservas[i].guardarEnArchivo(archivo); // Método de la clase `reservacion`
    }
    archivo.close();
}
void sistemaUdeaStay::consultarReservacionesAnfitrion() {
    if (anfitrionActual == nullptr) {
        cout << "No hay un anfitrión autenticado.\n";
        return;
    }

    string docAnfitrion = anfitrionActual->getDocumento();

    cout << "Ingrese la fecha de inicio (dd mm aaaa): ";
    int di, mi, ai;
    cin >> di >> mi >> ai;
    fecha fechaInicio(di, mi, ai);

    cout << "Ingrese la fecha de fin (dd mm aaaa): ";
    int df, mf, af;
    cin >> df >> mf >> af;
    fecha fechaFin(df, mf, af);

    cout << "\n=== Reservaciones del Anfitrión entre ";
    fechaInicio.mostrarFecha(); cout << " y "; fechaFin.mostrarFecha(); cout << " ===\n";

    for (int i = 0; i < totalReservas; ++i) {
        contadorIteraciones++;
        int codAloj = reservas[i].getCodigoAlojamiento();
        fecha fechaEntrada = reservas[i].getFechaEntrada();

        for (int j = 0; j < totalAlojamientos; ++j) {
            contadorIteraciones++;
            if (alojamientos[j].getCodigo() == codAloj &&
                alojamientos[j].getDocumentoAnfitrion() == docAnfitrion) {

                if (!(fechaEntrada < fechaInicio) && !(fechaFin < fechaEntrada)) {
                    cout << "\nReserva #" << i + 1 << ":\n";
                    reservas[i].mostrar();
                }
            }
        }
    }
}
void sistemaUdeaStay::mostrarAlojamientosDisponibles() {
    cout << "\n¿Desea buscar por filtros [1] o por código de alojamiento [2]? ";
    int modoBusqueda;
    cin >> modoBusqueda;

    if (modoBusqueda == 2) {
        int codigo;
        cout << "Ingrese el código del alojamiento: ";
        cin >> codigo;

        alojamiento* alo = nullptr;
        for (int i = 0; i < totalAlojamientos; ++i) {
            contadorIteraciones++;
            if (alojamientos[i].getCodigo() == codigo) {
                alo = &alojamientos[i];
                break;
            }
        }

        if (!alo) {
            cout << "Alojamiento no encontrado.\n";
            return;
        }

        int dia, mes, anio, duracion;
        cout << "Fecha de entrada:\nDía: "; cin >> dia;
        cout << "Mes: "; cin >> mes;
        cout << "Año: "; cin >> anio;
        cout << "Duración (en días): "; cin >> duracion;

        try {
            fecha fechaInicio(dia, mes, anio);

            if (disponibilidadAlojamiento(*alo, fechaInicio, duracion)) {
                alo->mostrarAlojamiento();
                cout << "\n¿Desea reservar este alojamiento? (s/n): ";
                char conf; cin >> conf;
                if (conf == 's' || conf == 'S') {
                    crearReserva(alo->getCodigo(), fechaInicio, duracion);
                } else {
                    cout << "Operación cancelada.\n";
                }
            } else {
                cout << "Este alojamiento no está disponible en la fecha indicada.\n";
            }
        } catch (const exception& e) {
            cout << "Error en la fecha: " << e.what() << "\n";
        }

        return;
    }

 // Filtro 2
    string municipio;
    int dia, mes, anio, duracion;
    double precioMax = -1;
    double puntuacionMin = -1;

    cout << "\n=== Búsqueda de Alojamientos Disponibles ===\n";
    cout << "Municipio: ";
    getline(cin >> ws, municipio);
    cout << "Fecha de entrada:\nDía: "; cin >> dia;
    cout << "Mes: "; cin >> mes;
    cout << "Año: "; cin >> anio;
    cout << "Duración (en días): "; cin >> duracion;

    char opcion;
    cout << "¿Desea ingresar precio máximo? (s/n): "; cin >> opcion;
    if (opcion == 's' || opcion == 'S') {
        cout << "Precio máximo por noche: ";
        cin >> precioMax;
    }

    cout << "¿Desea ingresar puntuación mínima del anfitrión? (s/n): "; cin >> opcion;
    if (opcion == 's' || opcion == 'S') {
        cout << "Puntuación mínima: ";
        cin >> puntuacionMin;
    }

    try {
        fecha fechaInicio(dia, mes, anio);
        bool encontrados = false;
        int seleccionables[capacidad];
        int contSeleccionables = 0;

        cout << "\n=== Resultados ===\n";
        for (int i = 0; i < totalAlojamientos; ++i) {
            alojamiento& a = alojamientos[i];
            anfitrion* anfitrionDelAloj = buscarAnfitrion(a.getDocumentoAnfitrion());

            if (normalizarTexto(a.getMunicipio()) != normalizarTexto(municipio)) continue;
            if (precioMax != -1 && a.getPrecioPorNoche() > precioMax) continue;
            if (puntuacionMin != -1 && anfitrionDelAloj && anfitrionDelAloj->getPuntuacion() < puntuacionMin) continue;
            if (!disponibilidadAlojamiento(a, fechaInicio, duracion)) continue;

            cout << "\n[" << contSeleccionables + 1 << "] ";
            a.mostrarAlojamiento();
            encontrados = true;
            seleccionables[contSeleccionables++] = a.getCodigo();
        }

        if (!encontrados) {
            cout << "\nNo se encontraron alojamientos con los filtros aplicados.\n";
            return;
        }

        int seleccion;
        cout << "\nSeleccione un alojamiento por número para reservar (0 para cancelar): ";
        cin >> seleccion;

        if (seleccion > 0 && seleccion <= contSeleccionables) {
            crearReserva(seleccionables[seleccion - 1], fechaInicio, duracion);
        } else {
            cout << "Operación cancelada.\n";
        }
    } catch (const exception& e) {
        cout << "Error en la fecha: " << e.what() << "\n";
    }
}

void sistemaUdeaStay::actualizarHistorico(const string& archivoReservas, const string& archivoHistorico) {
    cout << "\n=== Actualizar Histórico ===\n";
    int dia, mes, anio;
    cout << "Ingrese la fecha de corte:\nDía: "; cin >> dia;
    cout << "Mes: "; cin >> mes;
    cout << "Año: "; cin >> anio;

    fecha fechaCorte(dia, mes, anio);

    // Validar que la fecha de corte no sea menor que las del histórico
    for (int i = 0; i < totalHistorico; ++i) {
        contadorIteraciones++;
        if (historico[i].getFechaEntrada() > fechaCorte) {
            cout << "Error: La fecha de corte no puede ser menor que fechas en el histórico.\n";
            return;
        }
    }

    // Crear nuevos arreglos temporales
    reservacion nuevasReservas[capacidad];
    int nuevaTotal = 0;

    for (int i = 0; i < totalReservas; ++i) {
        if (reservas[i].getFechaEntrada() < fechaCorte) {
            // Mover al histórico
            if (totalHistorico < capacidad) {
                historico[totalHistorico++] = reservas[i];
            }
        } else {
            // Conservar en reservas si está dentro de los próximos 12 meses
            if (reservas[i].getFechaEntrada().esDentroDe12Meses(fechaCorte)) {
                nuevasReservas[nuevaTotal++] = reservas[i];
            }
        }
    }

    // Actualizar arreglo de reservas
    for (int i = 0; i < nuevaTotal; ++i) {
        contadorIteraciones++;
        reservas[i] = nuevasReservas[i];
    }
    totalReservas = nuevaTotal;

    guardarReservas(archivoReservas);
    guardarHistorico(archivoHistorico);

    cout << "Histórico actualizado. Reservas anteriores al ";
    cout << dia << "/" << mes << "/" << anio << " fueron movidas al archivo histórico.\n";
}
void mostrarConsumoRecursos(int totalHuespedes, int totalAnfitriones, int totalAlojamientos,
                            int totalReservas, int totalHistorico) {
    long long memoriaTotal = 0;
    memoriaTotal += totalHuespedes * sizeof(huesped);
    memoriaTotal += totalAnfitriones * sizeof(anfitrion);
    memoriaTotal += totalAlojamientos * sizeof(alojamiento);
    memoriaTotal += totalReservas * sizeof(reservacion);
    memoriaTotal += totalHistorico * sizeof(reservacion);

    cout << "\n=== Medición del consumo de recursos ===\n";
    cout << "Iteraciones totales realizadas: " << contadorIteraciones << "\n";
    cout << "Memoria total consumida (bytes): " << memoriaTotal << " B\n";
}
sistemaUdeaStay::~sistemaUdeaStay() {
    delete[] huespedes;
    delete[] anfitriones;
    delete[] alojamientos;
    delete[] reservas;
    delete[] historico;

}
