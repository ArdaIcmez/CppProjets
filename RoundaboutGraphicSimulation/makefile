
# 

PHONY=clean

COMP=g++
CFLAGS= -c -Wall 
INCPATH = #Path to libs here
LINK=g++
LDFLAGS=
EXE= Carrefour
HEADER= Mere.h GestionClavier.h GestionFeux.h Voie.h
SRC= $(HEADER:.h=.cpp)
OBJ= $(HEADER:.h=.o)
LIBPATH= -L/home/cedric/Documents/TP-Multitâche/libs
LIBS= -ltp -lncurses -ltcl 
CLEAN=clean
BACKUP=backup

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	@echo "Edition des liens de <$(EXE)>"
	$(LINK) $(LDFLAGS) $(OBJ) $(LIBPATH) $(LIBS) -o $@


%.o:%.cpp
	@echo "Compilation de <$<>"
	$(COMP) $(CFLAGS) $(INCPATH) $< -DMAP -o $@
	@echo ""

$(CLEAN):
	@echo "Nettoyage : on vire les .o et les executables"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) 


