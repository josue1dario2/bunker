#ifndef BUNKER_H
#define BUNKER_H

#include <vector>
#include <string>
#include <fstream>
#include "Grupo.h"
#include "Coalicion.h"

using namespace std;

class Bunker {
private:
    // Recursos principales
    int oxigeno;
    int energia;
    int medicina;

    // Control del juego
    int diaActual;
    int diaMaximo;  // 30 días para completar
    int moralScore; // Contador oculto de moralidad (0-100)
    int salud;      // Salud del operador

    // Habitantes
    vector<Grupo*> habitantes;

    // SISTEMA DE COALICIONES - Dinámicas emergentes
    vector<Coalicion> coaliciones;

    // Archivos
    ofstream logExperimento;

    // Métodos privados
    void escribirLog(string mensaje);
    void procesarConsumos();
    bool verificarCatastrofe();
    void procesarCoaliciones();
    void formarCoaliciones();
    void verificarGolpesDEstado();

public:
    Bunker();
    ~Bunker();

    // Control del juego
    bool procesarDia();
    void mostrarEstado();
    void mostrarInterfaz();

    // Gestión de grupos
    void añadirGrupo(Grupo* grupo);
    bool aceptarGrupo(int indiceGrupo);  // El jugador acepta un grupo
    bool rechazarGrupo(int indiceGrupo); // El jugador rechaza un grupo
    void listarHabitantes();

    // Gestión de coaliciones
    void listarCoaliciones();
    int obtenerNumeroCoaliciones() const { return coaliciones.size(); }

    // Getters
    int obtenerOxigeno() const { return oxigeno; }
    int obtenerEnergia() const { return energia; }
    int obtenerMedicina() const { return medicina; }
    int obtenerDia() const { return diaActual; }
    int obtenerMoral() const { return moralScore; }
    int obtenerSalud() const { return salud; }
    vector<Grupo*> obtenerHabitantes() const { return habitantes; }

    // Setters para recursos
    void agregarOxigeno(int cantidad);
    void agregarEnergia(int cantidad);
    void agregarMedicina(int cantidad);
    void restarOxigeno(int cantidad);
    void restarEnergia(int cantidad);
    void restarMedicina(int cantidad);

    // Lógica del juego
    bool verificarVictoria();
    void generarFinales();
    void iniciarLog();
};

#endif
