#ifndef GRUPO_H
#define GRUPO_H

#include <string>
#include <memory>
using namespace std;

// Forward declaration
class Estrategia;

// Clase base abstracta para los grupos de sobrevivientes
class Grupo {
protected:
    string nombre;
    int miembros;
    int hambre;        // Estado de necesidad
    int moral;         // Estado emocional del grupo

    // PATRÓN STRATEGY: Composición de algoritmos
    unique_ptr<Estrategia> estrategiaActual;

public:
    Grupo(string n, int m);
    virtual ~Grupo();

    // Métodos virtuales puros (interface que deben implementar las subclases)
    virtual void reaccionarAEvento(string evento) = 0;
    virtual int calcularConsumoOxigeno() = 0;
    virtual int calcularConsumoEnergia() = 0;
    virtual int calcularConsumoDEMedicina() = 0;
    virtual string darBeneficio() = 0;
    virtual string obtenerTipo() = 0;
    virtual int obtenerRiesgo() = 0;  // 0-100: probabilidad de sabotaje

    // Métodos concretos
    void envejecer();
    void afectarMoral(int cantidad);
    int obtenerMiembros() const;
    string obtenerNombre() const;
    int obtenerMoral() const;

    // PATRÓN STRATEGY: Métodos para cambiar comportamiento dinámicamente
    void establecerEstrategia(Estrategia* nueva);
    string ejecutarEstrategia();
    int obtenerRiesgoEstrategia() const;
    int obtenerBeneficioEstrategia() const;
    string obtenerNombreEstrategia() const;
};

#endif
