#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <string>
using namespace std;

// ═════════════════════════════════════════════════════════════════
// PATRÓN STRATEGY - Encapsula algoritmos de comportamiento
// ═════════════════════════════════════════════════════════════════

class Estrategia {
public:
    virtual ~Estrategia() {}

    // Algoritmos intercambiables
    virtual string ejecutar() = 0;           // Qué hace el grupo
    virtual int calcularRiesgo() = 0;        // Qué tan peligroso es
    virtual int calcularBeneficio() = 0;     // Qué beneficio aporta
    virtual string obtenerNombre() = 0;      // Nombre de la estrategia
};

// ═════════════════════════════════════════════════════════════════
// ESTRATEGIAS CONCRETAS
// ═════════════════════════════════════════════════════════════════

// Cuando el grupo es ACEPTADO - Cooperación total
class EstrategiaAceptacion : public Estrategia {
public:
    string ejecutar() override;
    int calcularRiesgo() override { return 10; }
    int calcularBeneficio() override { return 80; }
    string obtenerNombre() override { return "Cooperación Completa"; }
};

// Cuando el grupo es RECHAZADO - Puede sabotear
class EstrategiaRechazo : public Estrategia {
public:
    string ejecutar() override;
    int calcularRiesgo() override { return 75; }
    int calcularBeneficio() override { return -50; }
    string obtenerNombre() override { return "Sabotaje/Hostilidad"; }
};

// Modo NEUTRO - Esperan fuera
class EstrategiaNeutra : public Estrategia {
public:
    string ejecutar() override;
    int calcularRiesgo() override { return 40; }
    int calcularBeneficio() override { return 0; }
    string obtenerNombre() override { return "Espera Tensa"; }
};

// Modo NEGOCIACIÓN - Piden condiciones
class EstrategiaNegoциacion : public Estrategia {
public:
    string ejecutar() override;
    int calcularRiesgo() override { return 30; }
    int calcularBeneficio() override { return 50; }
    string obtenerNombre() override { return "Negociación Activa"; }
};

#endif
