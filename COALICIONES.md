# 🔗 Sistema de Coaliciones - Dinámicas Emergentes

## ¿Qué son las Coaliciones?

Una **coalición** es cuando múltiples grupos se unen para formar una entidad única con objetivos comunes. Esto crea **dinámicas emergentes** que hacen el juego más realista y complejo.

```
SIN Coaliciones:
  Grupo A | Grupo B | Grupo C  (Actúan independientemente)

CON Coaliciones:
  ┌─────────────────────────────────┐
  │ COALICIÓN (Sabotaje)            │
  │ ├── Grupo A (Rechazado)         │
  │ ├── Grupo B (Descontento)       │
  │ └── Grupo C (Moral baja)        │
  │ Fuerza combinada: 150           │
  │ Riesgo: 85%                     │
  └─────────────────────────────────┘
```

---

## 🏗️ Arquitectura de Coaliciones

### Clase Coalicion (include/Coalicion.h)

```cpp
class Coalicion {
private:
    vector<Grupo*> miembros;        // Los grupos que la forman
    string objetivo;                 // "sabotaje", "poder", "sobrevivencia"
    int fuerzaTotal;                 // Suma de poder combinado
    int unidadGrupal;                // 0-100: qué tan unidos están
    bool esActiva;                   // ¿Está operativa?

public:
    // Gestionar miembros
    void agregarGrupo(Grupo* grupo);
    
    // Información
    int obtenerFuerzaTotal();
    int calcularRiesgoConjunto();    // Riesgo AMPLIFICADO
    
    // Acciones
    string ejecutarAccion();
    bool intentaraGolpe();
    
    // Dinámica interna
    void procesarDia();              // La unidad cambia diariamente
    bool seDisolvera();              // ¿Se cae la coalición?
};
```

### Integración en Bunker

```cpp
class Bunker {
private:
    vector<Coalicion> coaliciones;   // Todas las coaliciones activas

private:
    void formarCoaliciones();        // Crear coaliciones cuando es necesario
    void procesarCoaliciones();      // Actualizar estado diario
    
public:
    void listarCoaliciones();        // Ver coaliciones activas
};
```

---

## 🎮 Cómo Funcionan en el Juego

### 1. Formación Automática

Cada día, el sistema verifica si hay condiciones para formar coaliciones:

```cpp
// Condición 1: Grupos Rechazados
if (grupo1.esRechazado() && grupo2.esRechazado() && grupo3.esRechazado()) {
    // Se forman: COALICIÓN DE SABOTAJE
    coalicion.objetivo = "sabotaje";
    coalicion.riesgo = 85%;  // MUY PELIGROSO
}

// Condición 2: Saqueadores Descontentos
if (saqueador.moral < 60 && saqueador2.moral < 50) {
    // Se forman: COALICIÓN DE PODER
    coalicion.objetivo = "poder";
    coalicion.riesgo = 95%;  // CRÍTICO
}
```

### 2. Amplificación de Poder

Una coalición no es solo la suma de sus miembros. **El poder se multiplica**:

```
Grupo A (Fuerza: 20) + Grupo B (Fuerza: 25) = ?

SIN Coalición:     20 + 25 = 45
CON Coalición:     (20 + 25) × 1.5 = 67.5  (Sabotaje)
                   (20 + 25) × 1.8 = 72    (Poder/Golpe)
```

### 3. Dinámicas Internas

La **unidad grupal** cambia cada día:

```cpp
// La unidad sube si:
- Todos comparten el mismo objetivo
- Moral promedio es alta

// La unidad baja si:
- Algún miembro tiene moral muy baja
- Hay conflicto entre objetivos

// Se disuelve si:
- Unidad < 10%
- Moral promedio < 20%
```

### 4. Golpes de Estado

Una coalición de **poder** puede intentar golpe:

```cpp
// Probabilidad: (Fuerza/2) + (Unidad/2)
// Si probabilidad > 70% y rol aleatorio < 40:
//   → ¡GOLPE DE ESTADO!
//   → Operador pierde 30 de salud
//   → Pierdes 20 de moral
```

---

## 📊 Tipos de Coaliciones

### 1. Coalición de SABOTAJE
**Objetivo:** Dañar el búnker  
**Miembros:** Grupos rechazados  
**Riesgo:** 85%  
**Acciones:**
- Sabotean sistemas
- Dañan infraestructura
- Roban recursos

```
Ejemplo:
  [Ingeniero rechazado] + [Civil rechazado] + [Saqueador rechazado]
  = Coalición de Sabotaje (Fuerza: 90)
```

### 2. Coalición de PODER
**Objetivo:** Controlar el búnker  
**Miembros:** Saqueadores, grupos descontentos  
**Riesgo:** 95% (¡CRÍTICO!)  
**Acciones:**
- Intenta golpe de estado
- Reclama control de recursos
- Exige autoridad

```
Ejemplo:
  [Saqueador] + [Saqueador]
  = Coalición de Poder (Fuerza: 120, ¡AMENAZA!)
```

### 3. Coalición de SOBREVIVENCIA
**Objetivo:** Colaboración mutua  
**Miembros:** Civiles, Médicos, Ingenieros acceptados  
**Riesgo:** 10-20% (bajo)  
**Acciones:**
- Trabajo cooperativo
- Compartir recursos
- Apoyo mutuo

```
Ejemplo:
  [Ingeniero] + [Médico] + [Civil]
  = Coalición de Sobrevivencia (Fuerza: 100, beneficiosa)
```

---

## 🎯 Estrategia del Jugador

### ¿Cómo Evitar Coaliciones Peligrosas?

1. **No rechaces muchos grupos**
   - Cada rechazo aumenta riesgo de sabotaje
   - Grupos rechazados se alían automáticamente

2. **Mantén el moral alto**
   - Aceptando grupos → Unidad mejora
   - Rechazando grupos → Unidad se cae

3. **Equilibra las aceptaciones**
   - No aceptes SOLO Saqueadores (buscará poder)
   - Mezcla diferentes tipos (cobran importancia)

### ¿Cómo Aprovechar Coaliciones?

1. **Coaliciones de Sobrevivencia**
   - Son beneficiosas
   - Aumentan producción
   - Bajan riesgo

2. **Diplomacia**
   - Mantén coaliciones desunidas
   - Satisface parte de la coalición
   - Reduce riesgo

---

## 💻 Implementación Técnica

### Forward Declaration

```cpp
// Coalicion.h necesita conocer Grupo (pero no su definición)
class Grupo;  // Forward declaration

// Luego incluir el header completo
#include "Grupo.h"
```

### Composición vs Herencia

```cpp
// ❌ MAL: Herencia (inflexible)
class CoalicionSabotaje : public Coalicion { /* ... */ };
class CoalicionPoder : public Coalicion { /* ... */ };
// Tenemos que crear subclases para cada tipo

// ✅ BIEN: Composición (flexible)
class Coalicion {
private:
    string objetivo;  // "sabotaje", "poder", "sobrevivencia"
};
// Podemos crear coaliciones de cualquier tipo dinámicamente
```

### Gestión de Vector Dinámico

```cpp
vector<Coalicion> coaliciones;  // No es de punteros (RAII)

// Agregar coalición
coaliciones.push_back(nuevaCoalicion);

// Actualizar
for (Coalicion& c : coaliciones) {
    c.procesarDia();
}
```

---

## 📈 Impacto en la Presentación

**Sin Coaliciones:**
```
Profesor ve: "Juego básico con grupos independientes"
```

**Con Coaliciones:**
```
Profesor ve: "Sistema dinámico con emergencia de comportamiento colectivo.
            Demuestra comprensión de composición, dinámicas de sistemas,
            y arquitectura escalable."
```

---

## 🔍 Dinámicas Emergentes

Una **dinámica emergente** es un comportamiento que surge de la interacción de múltiples partes, sin estar explícitamente programado.

### Ejemplo de Emergencia

```
Programado:
  • Los grupos se alían si están rechazados
  • La unidad sube/baja según moral
  • Las coaliciones pueden hacer golpes

EMERGENTE (no programado explícitamente):
  • Operador debe equilibrar aceptaciones
  • Si rechazas 3 grupos → Golpe de estado
  • Saqueadores + Ingenieros descontentos = amenaza crítica
  • Aceptar Civiles contrarresta Saqueadores
  
Estrategia que surge del jugador:
  "Necesito aceptar grupos 'buenos' para evitar que 
   se formen coaliciones de 'malos'"
```

---

## 🎓 Conceptos de Arquitectura

### 1. Sistema de Eventos
Las coaliciones son un **sistema de eventos**:
```
Día X: [Condición] → [Evento: Coalición formada]
Día X+1: [Acción: Golpe] → [Consecuencia: Daño]
```

### 2. Feedback Loops
**Loop Positivo (Peligroso):**
```
Rechazas grupo → Moral baja → Se forman coaliciones
→ Intentan golpe → Pierdes salud → Fallas
```

**Loop Negativo (Controlador):**
```
Aceptas grupo → Moral sube → Coaliciones se disuelven
→ Sistema se estabiliza
```

### 3. Complejidad Emergente
```
Complejidad sin coaliciones:    O(n)      (lineal)
Complejidad con coaliciones:    O(n²)     (cuadrática)
```
Con coaliciones, las interacciones son mucho más ricas.

---

## 🚀 Cómo Extenderlo Más

### Idea 1: Negociación de Coaliciones
```cpp
bool Coalicion::intentarNegoциacion() {
    // La coalición puede negociar mejor trato
    // Si gets medicina → reduce riesgo
}
```

### Idea 2: Coaliciones Rivales
```cpp
// Dos coaliciones pueden enfrentarse entre sí
class ConflictoInterno {
    Coalicion* lado1;
    Coalicion* lado2;
    void batalla();
};
```

### Idea 3: Expansión de Coalición
```cpp
// Una coalición puede reclutar nuevos miembros
void Coalicion::expandir() {
    // "Hey, Grupo X, únete a nosotros"
}
```

---

## 🎯 Conclusión

El **Sistema de Coaliciones** demuestra:

✅ **Composición** sobre herencia  
✅ **Dinámicas complejas** emergentes  
✅ **Sistemas de estado** avanzados  
✅ **Realismo** en simulación  
✅ **Arquitectura profesional** escalable  

Es lo que diferencia a un juego "educativo" de una **simulación real**.
