# 📚 PROTOCOLO GUARDIÁN - Documentación Técnica POO

Documentación de conceptos de Programación 2 implementados en este proyecto.

## 🎓 Requisitos Cumplidos

### 1. CLASES Y OBJETOS ✅

#### Definición
Una clase es un molde para crear objetos. Define atributos (datos) y métodos (comportamiento).

#### Implementación en el Proyecto
```cpp
// include/Bunker.h
class Bunker {
private:
    int oxigeno;        // Atributo
    int energia;
    vector<Grupo*> habitantes;
    
public:
    Bunker();           // Constructor
    ~Bunker();          // Destructor
    void procesarDia(); // Método
};
```

**Instanciación en main.cpp:**
```cpp
Bunker bunker;  // Se crea un objeto de clase Bunker
```

---

### 2. HERENCIA ✅

#### Definición
La herencia permite que una clase herede atributos y métodos de otra clase (clase base).

#### Implementación
```
Grupo (Clase Base)
  ├── Ingeniero : public Grupo
  ├── Medico : public Grupo
  ├── Civil : public Grupo
  └── Saqueador : public Grupo
```

#### Ejemplo de Código
**Clase Base (include/Grupo.h):**
```cpp
class Grupo {              // Clase base
protected:
    string nombre;         // Heredable
    int miembros;
public:
    virtual ~Grupo();      // Destructor virtual
    virtual void reaccionarAEvento(string evento) = 0;  // Virtual puro
};
```

**Clase Derivada (include/Ingeniero.h):**
```cpp
class Ingeniero : public Grupo {  // HERENCIA
private:
    int habilidad;                 // Atributo adicional
public:
    Ingeniero(string n, int m);    // Ctor específico
    void reaccionarAEvento(string evento) override;  // Sobrescribe método
};
```

**Implementación (src/Ingeniero.cpp):**
```cpp
Ingeniero::Ingeniero(string n, int m) 
    : Grupo(n, m), habilidad(75 + rand() % 25) {  // Llama ctor de base
    nombre = "Grupo de " + n;
}

void Ingeniero::reaccionarAEvento(string evento) {  // Polimorfismo
    if (evento == "aceptado") {
        moral += 15;  // Usa atributo heredado
    }
}
```

---

### 3. ENCAPSULAMIENTO ✅

#### Definición
Control de acceso a atributos mediante modificadores: `private`, `protected`, `public`.

#### Implementación en Grupo.h
```cpp
class Grupo {
private:                           // Solo accesible internamente
    string nombre;
    int miembros;
    
protected:                         // Accesible por subclases
    int hambre;
    int moral;
    
public:                            // Accesible desde cualquier lugar
    int obtenerMoral() const {     // Getter - acceso de lectura
        return moral;
    }
    
    void afectarMoral(int cantidad) {  // Setter - acceso controlado
        moral += cantidad;
        if (moral > 100) moral = 100;
    }
};
```

#### Ventajas Aplicadas
- ✅ Los atributos no se pueden cambiar arbitrariamente
- ✅ La lógica se valida en los setters (ej: moral no > 100)
- ✅ Las subclases pueden acceder a `protected` pero no a `private`

---

### 4. POLIMORFISMO ✅

#### Definición
La capacidad de que objetos de diferentes tipos respondan diferente al mismo método.

#### Ejemplo: Métodos Virtuales
```cpp
// Clase base define interfaz
class Grupo {
public:
    virtual string darBeneficio() = 0;  // Método virtual puro
};

// Diferentes implementaciones
class Ingeniero : public Grupo {
public:
    string darBeneficio() override {
        return "Restaurando energía (+15 Energía/día)";
    }
};

class Medico : public Grupo {
public:
    string darBeneficio() override {
        return "Atención médica (+Salud, -Medicina)";
    }
};

class Civil : public Grupo {
public:
    string darBeneficio() override {
        return "Futura generación (+Moral, Consumo muy alto)";
    }
};
```

#### Polimorfismo en Acción (src/Bunker.cpp)
```cpp
void Bunker::procesarConsumos() {
    for (Grupo* g : habitantes) {  // Puntero a Grupo (clase base)
        g->envejecer();            // Método concreto
        
        // Cada subclase calcula su propio consumo
        int consumoO2 = g->calcularConsumoOxigeno();  // POLIMORFISMO
        int consumoE = g->calcularConsumoEnergia();   // cada tipo implementa diferente
    }
}
```

Este bucle funciona igual con Ingenieros, Médicos, Civiles o Saqueadores, pero cada uno **se comporta diferente** 🎯

---

### 5. MÉTODOS VIRTUALES Y ABSTRACTOS ✅

#### Métodos Virtuales Puros (Clases Abstractas)
```cpp
class Grupo {  // Clase abstracta (no se puede instanciar)
public:
    virtual void reaccionarAEvento(string evento) = 0;  // Puro
    virtual int calcularConsumoOxigeno() = 0;           // Puro
    virtual string darBeneficio() = 0;                   // Puro
};

// ESTO FALLA:
// Grupo g;  // ERROR: Clase abstracta

// Correcto:
Ingeniero ing("Ingenieros", 5);  // OK: Subclase concreta
```

#### Override (Sobrescritura)
```cpp
class Ingeniero : public Grupo {
public:
    void reaccionarAEvento(string evento) override {  // C++11 override keyword
        cout << "Los ingenieros reaccionan..." << endl;
    }
};
```

---

### 6. CONSTRUCTORES Y DESTRUCTORES ✅

#### Constructores
Inicializan los objetos cuando se crean.

```cpp
// include/Ingeniero.h
Ingeniero::Ingeniero(string n, int m)
    : Grupo(n, m),  // Llama constructor de la clase base
      habilidad(75 + rand() % 25), 
      reparando(false) {
    nombre = "Grupo de " + n;
}
```

#### Destructores Virtuales
Limpian memoria cuando se destruyen objetos.

```cpp
class Grupo {
public:
    virtual ~Grupo() {}  // Destructor virtual (IMPORTANTE)
};

// En Bunker.cpp
Bunker::~Bunker() {
    for (Grupo* g : habitantes) {
        delete g;  // Destruye cada grupo correctamente
    }
    habitantes.clear();
}
```

**¿Por qué virtual?** Si usas `delete` en un puntero a clase base, necesita saber qué tipo derivado destruir.

---

### 7. AGREGACIÓN Y COMPOSICIÓN ✅

#### Agregación: Objeto contiene referencias a otros objetos
```cpp
class Bunker {
private:
    vector<Grupo*> habitantes;  // AGREGACIÓN polimórfica
    
public:
    void añadirGrupo(Grupo* grupo) {
        habitantes.push_back(grupo);
    }
};
```

El Bunker agrega (contiene) múltiples Grupos de diferentes tipos.

**Uso en main.cpp:**
```cpp
Bunker bunker;
bunker.añadirGrupo(new Ingeniero("Ingenieros", 8));
bunker.añadirGrupo(new Medico("Médicos", 5));
bunker.añadirGrupo(new Civil("Civiles", 15, true));
```

---

### 8. MANEJO DE MEMORIA DINÁMICA ✅

#### Asignación Dinámica
```cpp
// new: asigna en heap
Grupo* ingeniero = new Ingeniero("Ingenieros", 8);
inhabitants.push_back(ingeniero);
```

#### Desasignación
```cpp
// delete: libera memoria
for (Grupo* g : habitantes) {
    delete g;  // Necesario para evitar memory leak
}
```

#### Alternativa Moderna (Bonus)
C++11 ofrece punteros inteligentes que limpian automáticamente:
```cpp
vector<unique_ptr<Grupo>> habitantes;
habitantes.push_back(make_unique<Ingeniero>("Ing", 8));
// Se auto-destruye cuando sale del scope
```

---

### 9. ARCHIVOS (PERSISTENCIA) ✅

#### Lectura/Escritura (fstream)
```cpp
#include <fstream>

class Bunker {
private:
    ofstream logExperimento;  // Output file stream
    
public:
    void iniciarLog() {
        logExperimento.open("data/log_experimento.txt", ios::app);
    }
    
    void escribirLog(string mensaje) {
        if (logExperimento.is_open()) {
            logExperimento << "[Día " << diaActual << "] " << mensaje << endl;
        }
    }
};
```

#### En el Juego
Cada decisión del jugador se registra:
```
[Día 1] ACEPTADO: Grupo de Ingenieros - Recursos gastados.
[Día 2] RECHAZADO: Equipo Médico - Moral afectada.
[Día 5] SABOTAJE DETECTADO: Ingeniero
```

---

### 10. ESTRUCTURAS DE DATOS ✅

#### Vector (std::vector)
Contenedor dinámico que almacena elementos.

```cpp
#include <vector>

vector<Grupo*> habitantes;  // Vector de punteros
habitantes.push_back(new Ingeniero("Ing", 5));
habitantes[0]->reaccionarAEvento("aceptado");

// Iteración
for (Grupo* g : habitantes) {
    cout << g->obtenerTipo() << endl;
}
```

#### String (std::string)
Cadenas de texto más seguras que char*.

```cpp
#include <string>

string nombre = "Grupo de Ingenieros";
nombre += " (Modificado)";
cout << nombre << endl;
```

---

## 🔍 Patrones de Diseño Aplicados

### Pattern: Strategy (mediante Polimorfismo)
Cada grupo implementa una estrategia diferente de reacción:
```cpp
for (Grupo* g : habitantes) {
    g->reaccionarAEvento("rechazado");  // Cada uno reacciona distinto
}
```

### Pattern: Template Method
El ciclo del juego sigue un patrón:
```cpp
while (juegoActivo) {
    mostrarMenuo();
    procesarOpcion();
    actualizar();
}
```

---

## 📊 Diagrama de Clases

```
┌─────────────────┐
│     Bunker      │  Gestor del juego
│─────────────────│
│ -oxigeno: int   │
│ -energia: int   │
│ -medicina: int  │
│ +procesarDia()  │
│ +aceptarGrupo() │
└────────┬────────┘
         │ contiene
         │ vector<Grupo*>
         │
         ▼
    ┌─────────────────────┐
    │   Grupo (virtual)   │  Clase Base Abstracta
    │─────────────────────│
    │ #nombre: string     │
    │ #miembros: int      │
    │ #moral: int         │
    │ +reaccionarAEvento()│ = 0 (puro)
    │ +calcularConsumoO2()│ = 0 (puro)
    │ +darBeneficio()     │ = 0 (puro)
    └─────────┬───────────┘
              │
              ├──────────┬──────────┬──────────┐
              ▼          ▼          ▼          ▼
         ┌────────┐ ┌────────┐ ┌─────────┐ ┌──────────┐
         │Ingeniero│ │Médico  │ │Civil    │ │Saqueador │
         └────────┘ └────────┘ └─────────┘ └──────────┘
        (override) (override) (override)  (override)
         cada uno
         implementa
         diferente
```

---

## 🎯 Conclusión

Este proyecto demuestra un **conocimiento sólido de POO en C++**:

✅ **Herencia**: 4 subclases de 1 base  
✅ **Polimorfismo**: Métodos virtuales que funcionan diferente por tipo  
✅ **Encapsulamiento**: Private/protected/public bien aplicados  
✅ **Abstracción**: Métodos puros definen interfaz  
✅ **Memoria dinámica**: new/delete en destructor  
✅ **Archivos**: fstream para persistencia  
✅ **Estructuras**: vector y string  
✅ **Constructores**: Inicialización correcta incluyendo herencia  

**Resultado:** Un simulador educativo funcional que aplica todos los conceptos del curso.
