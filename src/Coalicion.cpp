#include "../include/Coalicion.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Coalicion::Coalicion(string obj)
    : objetivo(obj), fuerzaTotal(0), unidadGrupal(100), esActiva(false) {}

Coalicion::~Coalicion() {}

void Coalicion::agregarGrupo(Grupo* grupo) {
    if (grupo != nullptr) {
        miembros.push_back(grupo);
        calcularFuerza();
        calcularUnidad();
    }
}

void Coalicion::removerGrupo(Grupo* grupo) {
    auto it = find(miembros.begin(), miembros.end(), grupo);
    if (it != miembros.end()) {
        miembros.erase(it);
        calcularFuerza();
        calcularUnidad();
    }
}

void Coalicion::calcularFuerza() {
    fuerzaTotal = 0;
    for (Grupo* g : miembros) {
        // Fuerza = número de miembros + moral + riesgo
        fuerzaTotal += g->obtenerMiembros();
        fuerzaTotal += (g->obtenerMoral() / 10);
        fuerzaTotal += (g->obtenerRiesgo() / 10);
    }
    // Bonus por unidad
    fuerzaTotal = fuerzaTotal * (100 + unidadGrupal) / 100;
}

void Coalicion::calcularUnidad() {
    if (miembros.empty()) {
        unidadGrupal = 0;
        return;
    }

    // La unidad es el promedio de moral de los miembros
    int moralPromedio = 0;
    for (Grupo* g : miembros) {
        moralPromedio += g->obtenerMoral();
    }
    unidadGrupal = moralPromedio / miembros.size();
}

string Coalicion::ejecutarAccion() {
    if (!esActiva) {
        return "Coalición inactiva.";
    }

    string descripcion = "Coalición de " + to_string(miembros.size()) + " grupos (" +
                        objetivo + ") actúa conjuntamente:\n";

    if (objetivo == "sobrevivencia") {
        descripcion += "✓ Los grupos trabajan juntos para la supervivencia común.";
    } else if (objetivo == "poder") {
        descripcion += "⚔ La coalición busca dominio sobre el búnker.";
    } else if (objetivo == "sabotaje") {
        descripcion += "💣 La coalición planea sabotaje coordinado.";
    }

    return descripcion;
}

int Coalicion::calcularRiesgoConjunto() {
    if (!esActiva || miembros.empty()) {
        return 0;
    }

    // El riesgo de una coalición es mayor que la suma individual
    int riesgoBase = 0;
    for (Grupo* g : miembros) {
        riesgoBase += g->obtenerRiesgo();
    }

    // Multiplicador: coalición = más peligroso
    // Especialmente si busca poder o sabotaje
    float multiplicador = 1.0f;
    if (objetivo == "poder") {
        multiplicador = 1.5f;  // 50% más peligroso
    } else if (objetivo == "sabotaje") {
        multiplicador = 1.8f;  // 80% más peligroso
    }

    int riesgoConjunto = riesgoBase * multiplicador * (unidadGrupal / 100.0f);
    return min(99, riesgoConjunto);  // Máximo 99%
}

int Coalicion::calcularBeneficioConjunto() {
    if (!esActiva || miembros.empty()) {
        return 0;
    }

    // El beneficio también se multiplica
    int beneficio = 0;
    for (Grupo* g : miembros) {
        beneficio += g->obtenerBeneficioEstrategia();
    }

    // La unidad mejora el beneficio
    beneficio = beneficio * (100 + unidadGrupal) / 100;
    return beneficio;
}

void Coalicion::procesarDia() {
    if (!esActiva || miembros.empty()) {
        return;
    }

    // Si hay conflicto interno, la unidad baja
    for (Grupo* g : miembros) {
        if (g->obtenerMoral() < 40) {
            afectarUnidad(-5);  // Moral baja = menos unidad
        }
    }

    // La unidad tiende a converger hacia el promedio de moral
    calcularUnidad();

    // Recalcular fuerza
    calcularFuerza();

    // Si la unidad baja mucho, la coalición podría disolverse
    if (unidadGrupal < 20) {
        cout << "\n⚠ La coalición de " << objetivo << " está colapsando..." << endl;
    }
}

void Coalicion::afectarUnidad(int cantidad) {
    unidadGrupal += cantidad;
    if (unidadGrupal > 100) unidadGrupal = 100;
    if (unidadGrupal < 0) unidadGrupal = 0;
}

bool Coalicion::intentaraGolpe() {
    if (!esActiva || objetivo != "poder") {
        return false;
    }

    // Probabilidad de golpe basada en:
    // - Fuerza de la coalición
    // - Unidad grupal
    // - Riesgo combinado

    int probabilidad = (fuerzaTotal / 2) + (unidadGrupal / 2);

    if (probabilidad > 70 && (rand() % 100) < 40) {
        cout << "\n🚨 ¡ALERTA CRÍTICA! La coalición intenta golpe de estado!" << endl;
        return true;
    }

    return false;
}

bool Coalicion::seDisolvera() {
    if (!esActiva || miembros.empty()) {
        return true;
    }

    // La coalición se disuelve si:
    // - Unidad muy baja (<10%)
    // - Todos los miembros muy hambrientos
    // - Moral promedio muy baja

    if (unidadGrupal < 10) {
        return true;
    }

    int moralPromedio = 0;
    for (Grupo* g : miembros) {
        moralPromedio += g->obtenerMoral();
    }
    moralPromedio /= miembros.size();

    if (moralPromedio < 20) {
        return true;
    }

    return false;
}
