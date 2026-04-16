#ifndef MEDICO_H
#define MEDICO_H

#include "Grupo.h"

class Medico : public Grupo {
private:
    int suministrosMedicos;  // 0-100: cantidad de medicinas disponibles
    int experiencia;         // 1-100: capacidad de diagnóstico

public:
    Medico(string n, int m);
    ~Medico();

    void reaccionarAEvento(string evento) override;
    int calcularConsumoOxigeno() override;
    int calcularConsumoEnergia() override;
    int calcularConsumoDEMedicina() override;
    string darBeneficio() override;
    string obtenerTipo() override { return "Medico"; }
    int obtenerRiesgo() override;  // Bajo riesgo

    int curarHeridas(int severidad);  // Retorna salud restaurada
    int obtenerSuministros() const { return suministrosMedicos; }
};

#endif
