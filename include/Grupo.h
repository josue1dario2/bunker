#ifndef GRUPO_H
#define GRUPO_H

#include <string>
using namespace std;

// Clase base abstracta para los grupos de sobrevivientes
class Grupo {
protected:
    string nombre;
    int miembros;
    int hambre;        // Estado de necesidad
    int moral;         // Estado emocional del grupo

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
};

#endif
