#include "../include/Bunker.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Bunker::Bunker()
    : oxigeno(1000), energia(500), medicina(200),
      diaActual(0), diaMaximo(30), moralScore(50), salud(100) {
    srand(time(0));
    iniciarLog();
}

Bunker::~Bunker() {
    // Liberar memoria de todos los grupos
    for (Grupo* g : habitantes) {
        delete g;
    }
    habitantes.clear();

    if (logExperimento.is_open()) {
        logExperimento.close();
    }
}

void Bunker::iniciarLog() {
    logExperimento.open("data/log_experimento.txt", ios::app);
    if (!logExperimento) {
        cerr << "Error: No se pudo abrir archivo de log." << endl;
    }
    logExperimento << "=== PROTOCOLO GUARDIAN - SUJETO 01 ===" << endl;
    logExperimento << "Simulación iniciada. Recursos iniciales:" << endl;
    logExperimento << "Oxígeno: " << oxigeno << " unidades" << endl;
    logExperimento << "Energía: " << energia << " unidades" << endl;
    logExperimento << "Medicina: " << medicina << " unidades" << endl;
    logExperimento << "-----------------------------------" << endl;
}

void Bunker::escribirLog(string mensaje) {
    if (logExperimento.is_open()) {
        logExperimento << "[Día " << diaActual << "] " << mensaje << endl;
        logExperimento.flush();
    }
}

void Bunker::mostrarInterfaz() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║  PROTOCOLO GUARDIAN - SECTOR 4        ║" << endl;
    cout << "║  Operador: Sujeto 01                  ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
}

void Bunker::mostrarEstado() {
    cout << "\n┌─ ESTADO DEL BÚNKER (Día " << diaActual << "/" << diaMaximo << ") ─┐" << endl;
    cout << "│ RECURSOS:" << endl;
    cout << "│   Oxígeno:  " << setw(4) << oxigeno << " u  ";
    cout << (oxigeno < 300 ? "⚠ CRÍTICO" : oxigeno < 600 ? "⚠ BAJO" : "✓") << endl;

    cout << "│   Energía:  " << setw(4) << energia << " u  ";
    cout << (energia < 200 ? "⚠ CRÍTICO" : energia < 400 ? "⚠ BAJO" : "✓") << endl;

    cout << "│   Medicina: " << setw(4) << medicina << " u  ";
    cout << (medicina < 100 ? "⚠ CRÍTICO" : medicina < 200 ? "⚠ BAJO" : "✓") << endl;

    cout << "│ Salud Operador: " << salud << "/100" << endl;
    cout << "│ Índice Moral: " << moralScore << "/100" << endl;
    cout << "│ Habitantes: " << habitantes.size() << " grupos" << endl;
    cout << "└──────────────────────────────────────────┘" << endl;
}

void Bunker::añadirGrupo(Grupo* grupo) {
    if (grupo != nullptr) {
        habitantes.push_back(grupo);
        escribirLog("Grupo " + grupo->obtenerTipo() + " propuesto: " + grupo->obtenerNombre());
    }
}

bool Bunker::aceptarGrupo(int indiceGrupo) {
    if (indiceGrupo < 0 || indiceGrupo >= habitantes.size()) {
        return false;
    }

    Grupo* grupo = habitantes[indiceGrupo];
    grupo->reaccionarAEvento("aceptado");

    // Restar recursos inmediatamente
    restarOxigeno(grupo->calcularConsumoOxigeno());
    restarEnergia(grupo->calcularConsumoEnergia());
    restarMedicina(grupo->calcularConsumoDEMedicina());

    // Aumentar moral del jugador por empatía
    moralScore += 10;

    escribirLog("ACEPTADO: " + grupo->obtenerNombre() + " - Recursos gastados.");

    return true;
}

bool Bunker::rechazarGrupo(int indiceGrupo) {
    if (indiceGrupo < 0 || indiceGrupo >= habitantes.size()) {
        return false;
    }

    Grupo* grupo = habitantes[indiceGrupo];
    grupo->reaccionarAEvento("rechazado");

    // Disminuir moral del jugador
    moralScore -= 15;

    escribirLog("RECHAZADO: " + grupo->obtenerNombre() + " - Moral afectada.");

    return true;
}

void Bunker::procesarConsumos() {
    int consumoO2 = 0, consumoE = 0, consumoM = 0;

    for (Grupo* g : habitantes) {
        g->envejecer();
        consumoO2 += g->calcularConsumoOxigeno();
        consumoE += g->calcularConsumoEnergia();
        consumoM += g->calcularConsumoDEMedicina();
    }

    // Consumo base del búnker
    consumoO2 += 50;  // Ventilación
    consumoE += 30;   // Iluminación y sistemas

    restarOxigeno(consumoO2);
    restarEnergia(consumoE);
    restarMedicina(consumoM);
}

bool Bunker::verificarCatastrofe() {
    if (oxigeno <= 0 || energia <= 0) {
        cout << "\n¡CATASTROFE! El búnker ha colapsado." << endl;
        escribirLog("JUEGO TERMINADO: Fallo de sistemas críticos.");
        return false;
    }

    // Riesgo de sabotaje por grupos descontentos
    for (Grupo* g : habitantes) {
        if (g->obtenerRiesgo() > 70 && g->obtenerMoral() < 30) {
            if (rand() % 100 < 30) {
                cout << "\n¡ALERTA! " << g->obtenerTipo() << " intenta sabotaje." << endl;
                escribirLog("SABOTAJE DETECTADO: " + g->obtenerTipo());
                salud -= 20;
            }
        }
    }

    if (salud <= 0) {
        cout << "\nOperador muerto. Simulación terminada." << endl;
        escribirLog("JUEGO TERMINADO: Operador neutralizado.");
        return false;
    }

    return true;
}

bool Bunker::procesarDia() {
    diaActual++;

    cout << "\n⏳ Procesando Día " << diaActual << "..." << endl;

    procesarConsumos();

    if (!verificarCatastrofe()) {
        return false;
    }

    return diaActual < diaMaximo;
}

bool Bunker::verificarVictoria() {
    if (diaActual >= diaMaximo && oxigeno > 0 && energia > 0) {
        return true;
    }
    return false;
}

void Bunker::generarFinales() {
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║          FIN DE LA SIMULACIÓN               ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;

    if (verificarVictoria()) {
        cout << "\n✓ Simulación completada exitosamente." << endl;
        cout << "\nResultados finales:" << endl;
        cout << "  Días sobrevividos: " << diaActual << endl;
        cout << "  Índice de Moralidad: " << moralScore << "%" << endl;
        cout << "  Grupos refugiados: " << habitantes.size() << endl;

        if (moralScore >= 70) {
            cout << "\nModo EMPATÍA detectado (70%+ decisiones morales)." << endl;
            cout << "Análisis: Tu programación incluye matriz de valores humanos." << endl;
        } else if (moralScore >= 40) {
            cout << "\nModo EQUILIBRIO detectado (decisiones mixtas)." << endl;
            cout << "Análisis: Balances lógica y empatía en dilemas." << endl;
        } else {
            cout << "\nModo PRAGMÁTICO detectado (<40% decisiones morales)." << endl;
            cout << "Análisis: Máxima eficiencia, mínimo gasto emocional." << endl;
        }

        cout << "\n" << string(50, '=') << endl;
        cout << "TRANSMISIÓN CLASIFICADA [NIVEL 10]" << endl;
        cout << string(50, '=') << endl;
        cout << "\n\"Felicidades, Sujeto 01." << endl;
        cout << "Has completado el entrenamiento de IA de Gestión de Crisis." << endl;
        cout << "Tus decisiones fueron " << moralScore << "% morales, "
             << (100 - moralScore) << "% lógicas." << endl;
        cout << "Has sido aprobado para controlar los búnkeres reales." << endl;
        cout << "Apagando simulación...\"" << endl;
        cout << string(50, '=') << endl;

        escribirLog("VICTORIA: Sujeto 01 aprobado para operaciones reales.");
    } else {
        cout << "\n✗ Simulación fallida." << endl;
        cout << "Causa: ";
        if (oxigeno <= 0) {
            cout << "Falta de Oxígeno" << endl;
        } else if (energia <= 0) {
            cout << "Falta de Energía" << endl;
        } else if (salud <= 0) {
            cout << "Muerte del Operador" << endl;
        }
        cout << "Duración: " << diaActual << " días" << endl;

        escribirLog("DERROTA: Simulación fallida.");
    }

    cout << "\nRegistros de la simulación guardados en: data/log_experimento.txt" << endl;
}

void Bunker::listarHabitantes() {
    cout << "\n📋 Habitantes del búnker:" << endl;
    for (int i = 0; i < habitantes.size(); i++) {
        cout << i << ". " << habitantes[i]->obtenerTipo() << " - "
             << habitantes[i]->obtenerNombre() << " (" << habitantes[i]->obtenerMiembros()
             << " miembros, Moral: " << habitantes[i]->obtenerMoral() << "%)" << endl;
    }
}

void Bunker::agregarOxigeno(int cantidad) {
    oxigeno += cantidad;
}

void Bunker::agregarEnergia(int cantidad) {
    energia += cantidad;
}

void Bunker::agregarMedicina(int cantidad) {
    medicina += cantidad;
}

void Bunker::restarOxigeno(int cantidad) {
    oxigeno -= cantidad;
}

void Bunker::restarEnergia(int cantidad) {
    energia -= cantidad;
}

void Bunker::restarMedicina(int cantidad) {
    medicina -= cantidad;
}
