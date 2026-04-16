# 🎮 PROTOCOLO GUARDIÁN - Simulador de Gestión de Crisis

Simulador de texto basado en POO (C++) donde eres un operador en un búnker post-apocalíptico que debe gestionar recursos críticos y decidir el destino de grupos de sobrevivientes.

## 📋 Características

- **POO Avanzada**: Herencia, polimorfismo, encapsulamiento
- **Gestión de Recursos**: Oxígeno, Energía, Medicina
- **Dilemas Morales**: Las decisiones afectan tu puntuación final
- **Múltiples Finales**: Según tu estilo de juego (pragmático, equilibrado, empático)
- **Sistema de Logs**: El juego registra tus decisiones en un archivo secreto
- **4 Tipos de Grupos**: Ingenieros, Médicos, Civiles, Saqueadores

## 🏗️ Arquitectura del Código

```
Grupo (Clase Base Abstracta)
├── Ingeniero
├── Medico
├── Civil
└── Saqueador

Bunker (Gestor Principal)
└── Maneja vector<Grupo*>
```

### Conceptos POO Aplicados

- ✅ **Herencia**: Todas las subclases heredan de `Grupo`
- ✅ **Polimorfismo**: Cada grupo reacciona diferente a eventos
- ✅ **Encapsulamiento**: Atributos privados con getters/setters
- ✅ **Métodos Virtuales**: `reaccionarAEvento()`, `calcularConsumo*()`
- ✅ **Destructores**: Limpieza automática de memoria
- ✅ **Agregación**: `vector<Grupo*>` en Bunker

## 🚀 Compilación

### Con Makefile (Recomendado)
```bash
make              # Compilar
make run          # Compilar y ejecutar
make clean        # Limpiar compilados
make clean_all    # Limpiar todo incluyendo logs
make logs         # Ver registro de decisiones
```

### Compilación manual
```bash
g++ -std=c++17 -o bunker_game src/*.cpp -Iinclude
./bunker_game
```

## 📊 Estructura de Archivos

```
bunker/
├── include/
│   ├── Grupo.h          (clase base abstracta)
│   ├── Ingeniero.h
│   ├── Medico.h
│   ├── Civil.h
│   └── Saqueador.h
├── src/
│   ├── main.cpp         (punto de entrada y loop de juego)
│   ├── Bunker.cpp       (gestor principal)
│   ├── Grupo.cpp
│   ├── Ingeniero.cpp
│   ├── Medico.cpp
│   ├── Civil.cpp
│   └── Saqueador.cpp
├── data/
│   └── log_experimento.txt  (generado automáticamente)
├── Makefile
└── README.md
```

## 🎯 Cómo Jugar

1. **Compila el programa**: `make`
2. **Ejecuta**: `./bunker_game`
3. **Gestiona recursos** durante 30 días
4. **Toma decisiones** sobre qué grupos aceptar
5. **Descubre el giro final** en la narrativa

### Recursos Críticos
- **Oxígeno**: El más importante. Todo lo consume constantemente
- **Energía**: Necesaria para sistemas del búnker
- **Medicina**: Cura heridas y enfermedades

### Tipos de Grupos

| Grupo | Consumo | Beneficio | Riesgo |
|-------|---------|-----------|--------|
| **Ingeniero** | Alto | Repara energía | Alto si descontento |
| **Médico** | Bajo-Medio | Cura heridas | Muy bajo |
| **Civil** | Muy alto | Moral + Productividad | Muy bajo |
| **Saqueador** | Medio | Defensa militar | CRÍTICO |

## 🧠 Mecánicas

### Índice Moral (Moralidad)
- Acepta grupos: +10 moral
- Rechaza grupos: -15 moral
- Afecta el final que ves

### Riesgo de Sabotaje
- Grupos descontentos pueden sabotear sistemas
- Mayor riesgo = mayor daño potencial

### Consumo Diario
- Se resta automáticamente cada día
- Si algún recurso llega a 0, pierdes
- Puedes ver consumo estimado por grupo

## 📝 Archivos de Salida

El juego genera `data/log_experimento.txt` que registra:
- Todas tus decisiones
- Cambios de recursos
- Eventos de sabotaje
- Mensaje final (victoria/derrota)

Ver logs: `make logs`

## 🎬 Finales Disponibles

El juego tiene múltiples finales según tu índice moral:

1. **Empatía** (70%+ moral): Enfoque humanista
2. **Equilibrio** (40-69% moral): Balance lógica-emoción
3. **Pragmático** (<40% moral): Máxima eficiencia

Y un **giro narrativo especial** al final... 👁️

## 📚 Requisitos de Programación 2

Este proyecto demuestra:
- ✅ Uso de clases y objetos
- ✅ Herencia de clases
- ✅ Métodos virtuales y polimorfismo
- ✅ Encapsulamiento (private/public/protected)
- ✅ Constructores y destructores
- ✅ Manejo dinámico de memoria (new/delete)
- ✅ Archivos (fstream)
- ✅ Estructuras de datos (vector)
- ✅ Bucles y condicionales complejos

## 💡 Consejos para Jugar

1. **No aceptes todos los grupos**: Los recursos son finitos
2. **Cuidado con los Saqueadores**: Son muy peligrosos
3. **Los Niños son una inversión**: Alto consumo ahora, futuro después
4. **Los Médicos son valiosos**: Bajo riesgo, buen beneficio
5. **Monitorea tu moral**: Afecta el final que ves
6. **Lee los logs**: Revelan secretos sobre la simulación

## 🔧 Opciones de Personalización

Para agregar más características:
- Más tipos de grupos (heredando de `Grupo`)
- Sistema de combate (contra Saqueadores)
- Más recursos (agua, alimentos)
- Eventos aleatorios más complejos
- Gráficos (con ncurses)
- Audio (con SDL2)

## 📄 Licencia

Proyecto educativo para Programación 2. Uso libre para fines académicos.

---

**"Felicidades, Sujeto 01. Has completado el entrenamiento. Apagando simulación..."**
