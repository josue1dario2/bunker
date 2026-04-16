#ifndef SAQUEADOR_H
#define SAQUEADOR_H

#include "Grupo.h"

class Saqueador : public Grupo {
private:
    int armas;         // 0-100: arsenal disponible
    int lealtad;       // 1-100: qué tan confiables son (BAJO = peligro)
    bool amenaza;      // Si están actualmente amenazando

public:
    Saqueador(string n, int m);
    ~Saqueador();

    void reaccionarAEvento(string evento) override;
    int calcularConsumoOxigeno() override;
    int calcularConsumoEnergia() override;
    int calcularConsumoDEMedicina() override;
    string darBeneficio() override;
    string obtenerTipo() override { return "Saqueador"; }
    int obtenerRiesgo() override;  // ALTÍSIMO riesgo

    int obtenerArmas() const { return armas; }
    int obtenerLealtad() const { return lealtad; }
    bool intentarGolpe();  // Retorna true si amenazan
};

#endif
