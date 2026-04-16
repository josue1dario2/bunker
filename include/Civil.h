#ifndef CIVIL_H
#define CIVIL_H

#include "Grupo.h"

class Civil : public Grupo {
private:
    bool tieneNinos;      // Si el grupo incluye niños
    int productividad;    // 1-100: cuánto contribuyen al búnker

public:
    Civil(string n, int m, bool ninos = false);
    ~Civil();

    void reaccionarAEvento(string evento) override;
    int calcularConsumoOxigeno() override;
    int calcularConsumoEnergia() override;
    int calcularConsumoDEMedicina() override;
    string darBeneficio() override;
    string obtenerTipo() override { return "Civil"; }
    int obtenerRiesgo() override;  // Muy bajo riesgo

    void aumentarProductividad(int cantidad);
    bool obtenerTieneNinos() const { return tieneNinos; }
};

#endif
