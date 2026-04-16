#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "../include/Bunker.h"
#include "../include/Ingeniero.h"
#include "../include/Medico.h"
#include "../include/Civil.h"
#include "../include/Saqueador.h"

using namespace std;

// Función para imprimir lentamente (efecto de máquina de escribir)
void printSlow(const string& text, int delayMs = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

// Función para imprimir con efecto de estática de radio
void printStatic(const string& text) {
    cout << "\n>>> [TRANSMISIÓN DE RADIO] >>>" << endl;
    printSlow(text, 20);
    cout << "\n<<< [FIN DE TRANSMISIÓN] <<<\n" << endl;
}

void mostrarMenu() {
    cout << "\n─────────────────────────────────────────" << endl;
    cout << "OPCIONES:" << endl;
    cout << "1. Procesar día siguiente" << endl;
    cout << "2. Ver estado del búnker" << endl;
    cout << "3. Listar habitantes" << endl;
    cout << "4. Simular evento de radio (añadir grupo)" << endl;
    cout << "5. Aceptar grupo solicitante" << endl;
    cout << "6. Rechazar grupo solicitante" << endl;
    cout << "7. Ver instrucciones" << endl;
    cout << "8. Ver coaliciones activas" << endl;
    cout << "0. Salir" << endl;
    cout << "─────────────────────────────────────────" << endl;
}

void mostrarInstrucciones() {
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║     PROTOCOLO GUARDIAN - MANUAL DEL OPERADOR  ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << "\nOBJETIVO: Sobrevivir 30 días gestionando recursos críticos" << endl;
    cout << "          mientras decides el destino de los sobrevivientes.\n" << endl;

    cout << "TIPOS DE GRUPOS:" << endl;
    cout << "  • INGENIEROS: Alto consumo, reparan energía, ALTO RIESGO si descontentos" << endl;
    cout << "  • MÉDICOS: Bajo consumo energía, curan heridas, muy seguros" << endl;
    cout << "  • CIVILES: Muy alto consumo (especialmente con niños), moral alta" << endl;
    cout << "  • SAQUEADORES: Defensa militar, RIESGO CRÍTICO de golpe de estado" << endl;

    cout << "\nRECURSOS:" << endl;
    cout << "  • OXÍGENO: Lo más crítico. Todos lo consumen constantemente" << endl;
    cout << "  • ENERGÍA: Necesaria para sistemas del búnker" << endl;
    cout << "  • MEDICINA: Cura heridas y enfermedades\n" << endl;

    cout << "DILEMAS MORALES:" << endl;
    cout << "  Cada decisión afecta tu 'Índice Moral' (0-100)." << endl;
    cout << "  Al final, se revelará tu verdadera naturaleza...\n" << endl;

    cout << "💡 CONSEJO: Toma tu tiempo en las decisiones importantes." << endl;
}

void generarEventoRadio(Bunker& bunker) {
    int tipoGrupo = rand() % 4;
    Grupo* nuevoGrupo = nullptr;

    string evento;

    switch (tipoGrupo) {
    case 0: {
        nuevoGrupo = new Ingeniero("Ingenieros", 8);
        evento = "Tres ingenieros buscan refugio. Prometen reparar nuestro generador "
                 "que está fallando. Pero consumirán mucha energía...";
        break;
    }
    case 1: {
        nuevoGrupo = new Medico("Médicos", 5);
        evento = "Un equipo médico solicita entrada. Dicen que pueden ayudarte con "
                 "tus heridas. Traen algunos suministros limitados.";
        break;
    }
    case 2: {
        bool tieneNinos = rand() % 2 == 0;
        nuevoGrupo = new Civil("Civiles", 15 + rand() % 10, tieneNinos);
        if (tieneNinos) {
            evento = "Civiles con NIÑOS están pidiendo entrada. El consumo de oxígeno "
                     "será masivo, pero... son niños.";
        } else {
            evento = "Un grupo de civiles adultos busca asilo. Pueden trabajar, pero "
                     "consumirán recursos.";
        }
        break;
    }
    case 3: {
        nuevoGrupo = new Saqueador("Saqueadores", 12);
        evento = "Saqueadores armados en la radio. Prometen protección y recursos "
                 "saqueados. El tono suena... amenazante.";
        break;
    }
    }

    if (nuevoGrupo != nullptr) {
        bunker.añadirGrupo(nuevoGrupo);
        printStatic(evento);
    }
}

int main() {
    Bunker bunker;

    // Pantalla de inicio
    cout << "\n";
    cout << "████████████████████████████████████████████████" << endl;
    cout << "█                                              █" << endl;
    cout << "█  PROTOCOLO GUARDIAN - SIMULADOR DE CRISIS   █" << endl;
    cout << "█  Año 2076 | Sector 4 | Sujeto 01           █" << endl;
    cout << "█                                              █" << endl;
    cout << "████████████████████████████████████████████████" << endl;

    this_thread::sleep_for(chrono::seconds(1));
    printSlow("Inicializando sistemas...", 25);
    this_thread::sleep_for(chrono::milliseconds(500));

    printStatic("Hola, Sujeto 01. Yo soy H.I.J.O., tu asistente de inteligencia. "
                "Se que esto es confuso, pero necesitamos que tomes decisiones. "
                "La humanidad depende de ello. O... eso creemos.");

    mostrarInstrucciones();

    bunker.mostrarInterfaz();
    bunker.mostrarEstado();

    bool juegoActivo = true;
    int ultimoGrupoGenerado = 0;

    while (juegoActivo) {
        mostrarMenu();
        cout << "Selecciona una opción: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 1: {
            juegoActivo = bunker.procesarDia();
            bunker.mostrarEstado();

            // Cada cierto número de días, generar evento de radio
            ultimoGrupoGenerado++;
            if (ultimoGrupoGenerado >= 3) {
                generarEventoRadio(bunker);
                ultimoGrupoGenerado = 0;
            }

            if (!juegoActivo) {
                bunker.generarFinales();
            }
            break;
        }
        case 2: {
            bunker.mostrarEstado();
            break;
        }
        case 3: {
            bunker.listarHabitantes();
            break;
        }
        case 4: {
            generarEventoRadio(bunker);
            break;
        }
        case 5: {
            bunker.listarHabitantes();
            cout << "\nSelecciona el índice del grupo a ACEPTAR: ";
            int indice;
            cin >> indice;
            if (bunker.aceptarGrupo(indice)) {
                cout << "✓ Grupo aceptado." << endl;
            } else {
                cout << "✗ Índice inválido." << endl;
            }
            break;
        }
        case 6: {
            bunker.listarHabitantes();
            cout << "\nSelecciona el índice del grupo a RECHAZAR: ";
            int indice;
            cin >> indice;
            if (bunker.rechazarGrupo(indice)) {
                cout << "✗ Grupo rechazado." << endl;
            } else {
                cout << "✗ Índice inválido." << endl;
            }
            break;
        }
        case 7: {
            mostrarInstrucciones();
            break;
        }
        case 8: {
            bunker.listarCoaliciones();
            break;
        }
        case 0: {
            cout << "\nSimulación abortada por el operador." << endl;
            juegoActivo = false;
            break;
        }
        default: {
            cout << "Opción no válida." << endl;
        }
        }
    }

    cout << "\nGracias por jugar Protocolo Guardián." << endl;
    return 0;
}
