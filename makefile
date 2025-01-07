CXX = g++
CXXFLAGS = -Os -Wall -std=c++20 `wx-config --cxxflags`
OPT = -pedantic
LDFLAGS = `wx-config --libs`

# Configuration pour suppression et extension sur Windows
effacer = rm
extension =

ifeq ($(OS), Windows_NT)
$(info ************  Windows ************)
effacer = del
extension = .exe
endif

# Cible par défaut
all: tp3A24$(extension)

# Compilation des fichiers .cpp en .o
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(OPT) -c $< -o $@

# Création de l'exécutable
tp3A24$(extension): tp3A24.o employe.o manager.o programmeur.o EmployeeController.o lecteurFichier.o stringManager.o gestionnaireInterface.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# Règle pour exécuter le programme
run: tp3A24$(extension)
	./tp3A24$(extension)

# Nettoyage des fichiers temporaires
clean:
	$(effacer) *.o tp3A24$(extension)
