#include "../include/Ingeniero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Ingeniero::Ingeniero(string n, int m)
    : Grupo(n, m), habilidad(75 + rand() % 25), reparando(false) {
    nombre = "Grupo de " + n;  // Ej: "Grupo de Ingenieros"
}

Ingeniero::~Ingeniero() {}

void Ingeniero::reaccionarAEvento(string evento) {
    if (evento == "aceptado") {
        cout << "Los ingenieros asientan profesionalmente." << endl;
        moral += 15;
    } else if (evento == "rechazado") {
        cout << "Los ingenieros se sienten traicionados. RIESGO DE SABOTAJE." << endl;
        moral -= 30;
        reparando = false;
    }
}

int Ingeniero::calcularConsumoOxigeno() {
    return 3 * miembros;  // Consumo alto: trabajan
}

int Ingeniero::calcularConsumoEnergia() {
    return 5 * miembros;  // Consumen mucha energía en herramientas
}

int Ingeniero::calcularConsumoDEMedicina() {
    return 1 * miembros;  // Bajo consumo
}

string Ingeniero::darBeneficio() {
    if (reparando) {
        return "Restaurando energía (+15 Energía/día)";
    }
    return "Mantenimiento pasivo (+5 Energía/día)";
}

int Ingeniero::obtenerRiesgo() {
    // Mayor riesgo si están descontentos
    if (moral < 30) {
        return 80;  // Altísimo riesgo de sabotaje
    } else if (moral < 60) {
        return 50;  // Riesgo moderado
    }
    return 10;  // Riesgo bajo
}

int Ingeniero::repararGenerador() {
    if (moral < 50) {
        return 0;  // No cooperan si están descontentos
    }
    reparando = true;
    return 15 + (habilidad / 5);  // Más energía si son más hábiles
}
