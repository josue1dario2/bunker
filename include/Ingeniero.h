#ifndef INGENIERO_H
#define INGENIERO_H

#include "Grupo.h"

class Ingeniero : public Grupo {
private:
    int habilidad;  // 1-100: capacidad técnica
    bool reparando; // Si está actualmente reparando

public:
    Ingeniero(string n, int m);
    ~Ingeniero();

    void reaccionarAEvento(string evento) override;
    int calcularConsumoOxigeno() override;
    int calcularConsumoEnergia() override;
    int calcularConsumoDEMedicina() override;
    string darBeneficio() override;
    string obtenerTipo() override { return "Ingeniero"; }
    int obtenerRiesgo() override;  // Alto riesgo si se descontentan

    int repararGenerador();  // Retorna energía restaurada
};

#endif
