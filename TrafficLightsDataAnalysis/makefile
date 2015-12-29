# makefile du TP C++ n°2 - Gestion de routes
# Arda et Nicolas
# 

PHONY=efface

COMP=g++
CFLAGS= -Wall -c
LINK=g++
LDFLAGS=
EXE= gestionRoutes
HEADER= gestionRoutes.h mesure.h capteur.h 
SRC= $(HEADER:.h=.cpp)
OBJ= $(HEADER:.h=.o)
LIBS=
CLEAN=efface

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	@echo "Edition des liens de <$(EXE)>"
	$(LINK) $(LDFLAGS) $(OBJ) -DMAP -o $@


gestionRoutes.o: gestionRoutes.cpp gestionRoutes.h
mesure.o: mesure.cpp mesure.h
capteur.o: capteur.cpp capteur.h



%.o:%.cpp
	@echo "Compilation de <$<>"
	$(COMP) $(CFLAGS) $< -DMAP -o $@

$(CLEAN):
	@echo "Nettoyage : on vire les .o et les executables"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) core
