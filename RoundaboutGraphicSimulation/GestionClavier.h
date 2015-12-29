/*************************************************************************
                           GestionClavier  -  Gestion des commandes clavier
                             -------------------
    début                : Mars 2015
    copyright            : (C) 2015 par cboscher	
    e-mail               : cedric.boscher@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <GestionClavier> (fichier GestionClavier.h) -------
#if ! defined ( GestionClavier_H )
#define GestionClavier_H

//------------------------------------------------------------------------
// Rôle de la tâche <GestionClavier>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
#include <string>

//------------------------------------------------------------- Constantes


//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void GestionClavier (pid_t pidGen, int fifoId, int shmDureeFeuId, int mutexDFeuId);
void Commande (char code);
void Commande (TypeVoie entree, TypeVoie sortie);
void Commande(TypeVoie voie, unsigned int duree);



#endif // GestionClavier_H
