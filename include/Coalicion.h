#ifndef COALICION_H
#define COALICION_H

#include <vector>
#include <string>
#include <memory>
#include "Grupo.h"

using namespace std;

// ═════════════════════════════════════════════════════════════════
// COALICION - Múltiples grupos actuando como una entidad única
// ═════════════════════════════════════════════════════════════════

class Coalicion {
private:
    vector<Grupo*> miembros;           // Grupos que forman la coalición
    string objetivo;                   // "sobrevivencia", "poder", "sabotaje"
    int fuerzaTotal;                   // Suma de poder de los miembros
    int unidadGrupal;                  // 0-100: qué tan unidos están
    bool esActiva;                     // ¿La coalición está operativa?

    // Métodos privados
    void calcularFuerza();
    void calcularUnidad();

public:
    Coalicion(string obj = "sobrevivencia");
    ~Coalicion();

    // Gestión de miembros
    void agregarGrupo(Grupo* grupo);
    void removerGrupo(Grupo* grupo);
    int obtenerNumeroMiembros() const { return miembros.size(); }
    vector<Grupo*> obtenerMiembros() const { return miembros; }

    // Información de la coalición
    int obtenerFuerzaTotal() const { return fuerzaTotal; }
    int obtenerUnidad() const { return unidadGrupal; }
    string obtenerObjetivo() const { return objetivo; }
    bool esAceptada() const { return esActiva; }

    // Acciones de la coalición
    string ejecutarAccion();           // Qué hace la coalición
    int calcularRiesgoConjunto();      // Riesgo combinado
    int calcularBeneficioConjunto();   // Beneficio combinado

    // Dinámicas internas
    void procesarDia();                // Cambios diarios en unidad
    void afectarUnidad(int cantidad);  // Aumentar/disminuir unidad
    void activar() { esActiva = true; }
    void desactivar() { esActiva = false; }

    // Predicciones
    bool intentaraGolpe();             // ¿Intentará un golpe de estado?
    bool seDisolvera();                // ¿Se disuelve la coalición?
};

#endif
