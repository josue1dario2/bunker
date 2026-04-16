#include "../include/Saqueador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Saqueador::Saqueador(string n, int m)
    : Grupo(n, m), armas(50 + rand() % 50), lealtad(30 + rand() % 40), amenaza(false) {
    nombre = "Grupo de " + n;
    moral = 50;  // Más bajos en moral desde el inicio
}

Saqueador::~Saqueador() {}

void Saqueador::reaccionarAEvento(string evento) {
    if (evento == "aceptado") {
        cout << "Los saqueadores entran lentamente, observando todo con desconfianza." << endl;
        moral += 5;  // Poco cambio, son cínicos
        amenaza = false;
    } else if (evento == "rechazado") {
        cout << "¡ADVERTENCIA! Los saqueadores amenazan con forzar entrada." << endl;
        moral -= 20;
        amenaza = true;  // Intentarán golpe
    }
}

int Saqueador::calcularConsumoOxigeno() {
    return 3 * miembros;  // Consumo moderado
}

int Saqueador::calcularConsumoEnergia() {
    return 4 * miembros;  // Mantienen armas, sistemas de vigilancia
}

int Saqueador::calcularConsumoDEMedicina() {
    return 3 * miembros;  // Algunos heridos de batallas previas
}

string Saqueador::darBeneficio() {
    return "Defensa (+Armas, Control de recursos, RIESGO ALTO)";
}

int Saqueador::obtenerRiesgo() {
    // ALTÍSIMO RIESGO siempre
    if (amenaza) {
        return 95;  // Intento de golpe inmediato
    }
    if (lealtad < 40) {
        return 85;  // Muy probable deserción violenta
    }
    return 70;  // Riesgo permanente
}

bool Saqueador::intentarGolpe() {
    if (amenaza) {
        // 60% de probabilidad de golpe exitoso si no están satisfechos
        if (lealtad < 50 && (rand() % 100) < 60) {
            cout << "¡ALERTA CRÍTICA! Los saqueadores intentan tomar control del búnker!" << endl;
            return true;
        }
    }
    return false;
}
