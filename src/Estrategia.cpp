#include "../include/Estrategia.h"
#include <iostream>

// ═════════════════════════════════════════════════════════════════
// IMPLEMENTACIÓN DE ESTRATEGIAS
// ═════════════════════════════════════════════════════════════════

string EstrategiaAceptacion::ejecutar() {
    return "El grupo entra al búnker con entusiasmo. Comienzan "
           "inmediatamente a trabajar en sus funciones asignadas.";
}

string EstrategiaRechazo::ejecutar() {
    return "El grupo rechazado se retira con resentimiento. "
           "Una voz crispada por la radio: 'Lo lamentarás, Sujeto 01'";
}

string EstrategiaNeutra::ejecutar() {
    return "El grupo espera fuera del búnker. La tensión es palpable. "
           "Cada hora que pasa, su desesperación aumenta.";
}

string EstrategiaNegoциacion::ejecutar() {
    return "El grupo propone condiciones: 'Aceptaremos si nos garantizas "
           "medicina para los enfermos'. ¿Cedes a sus demandas?";
}
