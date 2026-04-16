# 🎯 Patrón Strategy - Implementación Profesional

## ¿Qué es el Patrón Strategy?

El **Patrón Strategy** es un patrón de diseño que permite **cambiar el algoritmo de un objeto en tiempo de ejecución**. En lugar de heredar comportamiento, lo **componemos** (composición sobre herencia).

```
SIN Strategy:
  Grupo -> reaccionarAEvento() -> [lógica complicada con if/else]

CON Strategy:
  Grupo -> estrategia -> ejecutar() -> [algoritmo específico]
```

---

## 📊 Comparación: Antes vs Después

### ❌ ANTES (Sin Strategy - Código Complejo)
```cpp
class Grupo {
public:
    void reaccionarAEvento(string evento) {
        if (evento == "aceptado" && tipo == "Ingeniero") {
            // 20 líneas de lógica específica
        } else if (evento == "aceptado" && tipo == "Medico") {
            // 15 líneas de lógica específica
        } else if (evento == "rechazado" && tipo == "Ingeniero") {
            // 25 líneas de lógica específica
        } // ... 50+ líneas más de if/else
    }
};
```

**Problemas:**
- 😞 Código espagueti (muchos if/else)
- 😞 Difícil de mantener
- 😞 Acoplamiento alto (todas las estrategias en una clase)
- 😞 Violencia a Open/Closed Principle

### ✅ DESPUÉS (Con Strategy - Código Limpio)
```cpp
// Interfaz de estrategias
class Estrategia {
public:
    virtual string ejecutar() = 0;
    virtual int calcularRiesgo() = 0;
};

// Cada estrategia es su propia clase
class EstrategiaAceptacion : public Estrategia {
    string ejecutar() override {
        return "El grupo entra al búnker con entusiasmo...";
    }
};

class EstrategiaRechazo : public Estrategia {
    string ejecutar() override {
        return "El grupo se retira con resentimiento...";
    }
};

// El grupo usa composición
class Grupo {
private:
    unique_ptr<Estrategia> estrategiaActual;

public:
    void establecerEstrategia(Estrategia* nueva) {
        estrategiaActual.reset(nueva);
    }

    string ejecutar() {
        return estrategiaActual->ejecutar();
    }
};
```

**Ventajas:**
- ✅ Código limpio y legible
- ✅ Fácil de extender (agregar nuevas estrategias)
- ✅ Bajo acoplamiento
- ✅ Respeta Open/Closed Principle
- ✅ Polimorfismo dinámico en tiempo de ejecución

---

## 🎮 Implementación en Protocolo Guardián

### Estructura de Clases

```cpp
┌─────────────────────────────────────────────┐
│           PATRÓN STRATEGY                   │
└─────────────────────────────────────────────┘

┌──────────────────┐
│   Estrategia     │  (Interfaz abstracta)
│      (ABC)       │
├──────────────────┤
│ + ejecutar()     │
│ + calcularRiesgo│
│ + calcularBeneficio() │
└────────┬─────────┘
         │
    ┌────┼────┬──────────┬─────────────┐
    ▼    ▼    ▼          ▼             ▼
┌─────┐┌─────┐┌─────────┐┌──────────┐
│ Aceptación
│ Rechazo
│ Neutral
│ Negociación
└─────┘└─────┘└─────────┘└──────────┘

┌──────────────────────┐
│  Grupo               │
├──────────────────────┤
│ -estrategiaActual    │ ◄── composición
│ +establecerEstrategia()
│ +ejecutarEstrategia()
└──────────────────────┘
```

---

## 💻 Código Implementado

### 1. Interfaz Estrategia (include/Estrategia.h)

```cpp
class Estrategia {
public:
    virtual ~Estrategia() {}
    virtual string ejecutar() = 0;           // Qué hace
    virtual int calcularRiesgo() = 0;        // Riesgo de sabotaje
    virtual int calcularBeneficio() = 0;     // Aporte al búnker
    virtual string obtenerNombre() = 0;      // Nombre para logs
};
```

### 2. Estrategias Concretas

```cpp
// Cuando es ACEPTADO
class EstrategiaAceptacion : public Estrategia {
    string ejecutar() override {
        return "El grupo entra al búnker con entusiasmo...";
    }
    int calcularRiesgo() override { return 10; }
    int calcularBeneficio() override { return 80; }
};

// Cuando es RECHAZADO
class EstrategiaRechazo : public Estrategia {
    string ejecutar() override {
        return "El grupo se retira con resentimiento...";
    }
    int calcularRiesgo() override { return 75; }
    int calcularBeneficio() override { return -50; }
};

// En espera
class EstrategiaNeutra : public Estrategia { /* ... */ };

// Negociando
class EstrategiaNegociacion : public Estrategia { /* ... */ };
```

### 3. Integración en Grupo

```cpp
class Grupo {
protected:
    unique_ptr<Estrategia> estrategiaActual;  // COMPOSICIÓN

public:
    void establecerEstrategia(Estrategia* nueva) {
        estrategiaActual.reset(nueva);
    }

    string ejecutarEstrategia() {
        return estrategiaActual->ejecutar();
    }

    int obtenerRiesgoEstrategia() {
        return estrategiaActual->calcularRiesgo();
    }
};
```

### 4. Uso en Bunker

```cpp
bool Bunker::aceptarGrupo(int indiceGrupo) {
    Grupo* grupo = habitantes[indiceGrupo];

    // CAMBIAR ESTRATEGIA DINÁMICAMENTE
    grupo->establecerEstrategia(new EstrategiaAceptacion());

    // Mostrar la reacción
    cout << grupo->ejecutarEstrategia() << endl;
    cout << "Estrategia: " << grupo->obtenerNombreEstrategia() << endl;

    // Restar recursos
    restarOxigeno(grupo->calcularConsumoOxigeno());
    // ...
}
```

---

## 🎓 Por Qué Es "PRO"

### 1. **Composición sobre Herencia**
En lugar de tener muchas subclases de Grupo para cada comportamiento, usamos composición:

```cpp
// MAL: Demasiadas subclases
GrupoAceptado : Grupo { /* ... */ };
GrupoRechazado : Grupo { /* ... */ };
GrupoEnNegociacion : Grupo { /* ... */ };

// BIEN: Estrategias reutilizables
class Grupo {
    Estrategia* estrategia;  // Composición
};
```

### 2. **Flexibilidad en Tiempo de Ejecución**
Las estrategias se pueden cambiar dinámicamente:

```cpp
grupo->establecerEstrategia(new EstrategiaAceptacion());  // Cambio en tiempo de ejecución
// vs
GrupoAceptado grupo;  // Fijo en tiempo de compilación
```

### 3. **Fácil de Extender**
Agregar nuevas estrategias es trivial:

```cpp
// Agregar una nueva estrategia
class EstrategiaRevuelta : public Estrategia {
    string ejecutar() override { return "¡El grupo intenta golpe de estado!"; }
    int calcularRiesgo() override { return 99; }
};

// Usar la nueva estrategia
grupo->establecerEstrategia(new EstrategiaRevuelta());
```

### 4. **Respeta SOLID**
- **S** (Single Responsibility): Cada estrategia tiene una responsabilidad
- **O** (Open/Closed): Abierto para extensión (nuevas estrategias), cerrado para modificación
- **L** (Liskov): Todas las estrategias respetan el contrato
- **I** (Interface Segregation): Interface limpia y mínima
- **D** (Dependency Inversion): Grupo depende de abstracción (Estrategia)

---

## 📈 Impacto en la Presentación

**Profesor verá:**

```
Estudiante típico:
  "Tengo una clase Grupo con herencia y métodos virtuales"
  
Tú (CON Strategy):
  "Tengo una clase Grupo que usa el Patrón Strategy para 
   encapsular comportamientos intercambiables. Las estrategias 
   se pueden cambiar en tiempo de ejecución sin modificar la 
   clase Grupo. Respeta el principio Open/Closed de SOLID."
```

**Eso es lo que diferencia a un estudiante de Prog 2 "normal" 
de uno que entiende REALMENTE ingeniería de software.**

---

## 🔧 Cómo Continuar

### Agregar más Estrategias (Fácil)

```cpp
// include/Estrategia.h - Agregar al final
class EstrategiaGolpeDEstado : public Estrategia {
public:
    string ejecutar() override;
    int calcularRiesgo() override { return 95; }
    int calcularBeneficio() override { return -100; }
    string obtenerNombre() override { return "Golpe de Estado"; }
};
```

### Estrategias Avanzadas
```cpp
// Estrategia que depende de otros factores
class EstrategiaAdaptativa : public Estrategia {
private:
    int moral;      // Depende de la moral
    int hambre;     // Depende del hambre

public:
    EstrategiaAdaptativa(int m, int h) : moral(m), hambre(h) {}
    
    string ejecutar() override {
        if (hambre > 80) {
            return "El grupo está desesperado...";
        }
        return "El grupo permanece calmado.";
    }
};
```

---

## 📊 Resumen

| Aspecto | Sin Strategy | Con Strategy |
|---------|-------------|-------------|
| Líneas de código | 100+ | 50 |
| Complejidad | Espagueti | Limpia |
| Extensibilidad | Difícil | Fácil |
| Mantenibilidad | Baja | Alta |
| Nivel profesional | Básico | Avanzado |
| SOLID score | 1/5 | 5/5 |

---

## 🎯 Conclusión

El **Patrón Strategy** es uno de los patrones más usados en desarrollo profesional porque permite:

1. ✅ Cambiar comportamiento en tiempo de ejecución
2. ✅ Mantener el código limpio y DRY (Don't Repeat Yourself)
3. ✅ Respetar principios SOLID
4. ✅ Facilitar testing y debugging
5. ✅ Impresionar a profesores/entrevistadores

**Es la diferencia entre saber POO y entender arquitectura de software.**
