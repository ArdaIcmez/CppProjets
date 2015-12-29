# makefile du TP C++ n° - Analyse de logs Apache
# Arda et Nicolas
# 

PHONY=$(CLEAN)

COMP=g++
CFLAGS= -Wall -c -DMAP
LINK=g++
LDFLAGS=
RM=rm
RMFLAGS=
EXE= analyseLog
HEADER= main.h 
SRC= $(HEADER:.h=.cpp)
OBJ= $(HEADER:.h=.o)
LIBS=
CLEAN=efface

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	@echo "Edition des liens de <$(EXE)>"
	$(LINK) $(LDFLAGS) $(OBJ) -o $@


gestionRoutes.o: gestionRoutes.cpp gestionRoutes.h
mesure.o: mesure.cpp mesure.h
capteur.o: capteur.cpp capteur.h



%.o:%.cpp
	@echo "Compilation de <$<>"
	$(COMP) $(CFLAGS) $< -o $@

$(CLEAN):
	@echo "Nettoyage : on vire les .o et les executables"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE)
