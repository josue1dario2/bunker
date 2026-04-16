CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCLUDE_DIR)
TARGET = bunker_game
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Bunker.cpp \
          $(SRC_DIR)/Grupo.cpp \
          $(SRC_DIR)/Estrategia.cpp \
          $(SRC_DIR)/Coalicion.cpp \
          $(SRC_DIR)/Ingeniero.cpp \
          $(SRC_DIR)/Medico.cpp \
          $(SRC_DIR)/Civil.cpp \
          $(SRC_DIR)/Saqueador.cpp

# Archivos objeto
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regla por defecto
all: $(TARGET)

# Crear ejecutable
$(TARGET): $(OBJECTS) | data
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Compilación exitosa: $(TARGET)"

# Compilar archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

data:
	mkdir -p data

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "✓ Archivos compilados eliminados"

# Limpiar todo incluyendo logs
clean_all: clean
	rm -f data/log_experimento.txt
	@echo "✓ Logs eliminados"

# Mostrar logs
logs:
	@if [ -f data/log_experimento.txt ]; then cat data/log_experimento.txt; else echo "No hay logs aún."; fi

.PHONY: all run clean clean_all logs
