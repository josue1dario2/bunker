#include "../include/Civil.h"
#include <iostream>
#include <cstdlib>

Civil::Civil(string n, int m, bool ninos)
    : Grupo(n, m), tieneNinos(ninos), productividad(40 + rand() % 40) {
    nombre = n;
    if (tieneNinos) {
        nombre += " (CON NIÑOS)";
        // Los niños reducen productividad pero aumentan moral
        productividad -= 20;
    }
}

Civil::~Civil() {}

void Civil::reaccionarAEvento(string evento) {
    if (evento == "aceptado") {
        if (tieneNinos) {
            cout << "Los niños gritan de alegría. Los adultos lloran de alivio." << endl;
        } else {
            cout << "Los civiles entran al búnker con expresión de alivio." << endl;
        }
        moral += 25;
    } else if (evento == "rechazado") {
        if (tieneNinos) {
            cout << "Se escuchan gritos desesperados de niños. Silencio." << endl;
        } else {
            cout << "Los civiles se van con odio en la mirada." << endl;
        }
        moral -= 15;
    }
}

int Civil::calcularConsumoOxigeno() {
    int base = 4 * miembros;
    if (tieneNinos) {
        base += 2 * miembros;  // Los niños necesitan más oxígeno
    }
    return base;
}

int Civil::calcularConsumoEnergia() {
    return 2 * miembros;  // Bajo consumo de energía
}

int Civil::calcularConsumoDEMedicina() {
    int base = 2 * miembros;
    if (tieneNinos) {
        base += 3 * miembros;  // Los niños enferman más frecuentemente
    }
    return base;
}

string Civil::darBeneficio() {
    if (tieneNinos) {
        return "Futura generación (+Moral, Consumo muy alto)";
    }
    return "Mano de obra (+Productividad)";
}

int Civil::obtenerRiesgo() {
    // Civiles NO son una amenaza
    return 2;
}

void Civil::aumentarProductividad(int cantidad) {
    productividad += cantidad;
    if (productividad > 100) productividad = 100;
}
