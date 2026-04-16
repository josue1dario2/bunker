#include "../include/Grupo.h"
#include <iostream>

Grupo::Grupo(string n, int m) : nombre(n), miembros(m), hambre(0), moral(100) {}

Grupo::~Grupo() {}

void Grupo::envejecer() {
    hambre += 10;  // El hambre aumenta con el tiempo
    if (hambre > 100) hambre = 100;

    // La moral disminuye si están hambrientos
    if (hambre > 70) {
        moral -= 5;
        if (moral < 0) moral = 0;
    }
}

void Grupo::afectarMoral(int cantidad) {
    moral += cantidad;
    if (moral > 100) moral = 100;
    if (moral < 0) moral = 0;
}

int Grupo::obtenerMiembros() const {
    return miembros;
}

string Grupo::obtenerNombre() const {
    return nombre;
}

int Grupo::obtenerMoral() const {
    return moral;
}
