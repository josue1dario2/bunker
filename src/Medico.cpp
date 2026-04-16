#include "../include/Medico.h"
#include <iostream>
#include <cstdlib>

Medico::Medico(string n, int m)
    : Grupo(n, m), suministrosMedicos(80), experiencia(70 + rand() % 30) {
    nombre = "Equipo " + n;  // Ej: "Equipo Médico"
}

Medico::~Medico() {}

void Medico::reaccionarAEvento(string evento) {
    if (evento == "aceptado") {
        cout << "Los médicos se sienten útiles y aliviados." << endl;
        moral += 20;
    } else if (evento == "rechazado") {
        cout << "Los médicos protestan: 'Sin nosotros morirán'." << endl;
        moral -= 20;
    }
}

int Medico::calcularConsumoOxigeno() {
    return 2 * miembros;  // Consumo bajo (trabajan en zona controlada)
}

int Medico::calcularConsumoEnergia() {
    return 3 * miembros;  // Necesitan equipos médicos
}

int Medico::calcularConsumoDEMedicina() {
    return 4 * miembros;  // Consumo alto: usan medicinas constantemente
}

string Medico::darBeneficio() {
    return "Atención médica (+Salud, -Medicina)";
}

int Medico::obtenerRiesgo() {
    // Muy bajo riesgo, son pacíficos
    return 5;
}

int Medico::curarHeridas(int severidad) {
    if (suministrosMedicos < severidad) {
        return 0;  // No hay suficientes suministros
    }
    suministrosMedicos -= severidad;
    return 20 + (experiencia / 5);  // Más salud si son más experimentados
}
