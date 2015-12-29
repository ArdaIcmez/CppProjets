/*************************************************************************
                           GestionFeux  -  Gestion du fonctionnement des feux.
                             -------------------
    début                : Mars 2015
    copyright            : (C) 2015 par cboscher	
    e-mail               : cedric.boscher@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <GestionFeux> (fichier GestionFeu.h) -------
#if ! defined ( GestionFeux_H )
#define GestionFeux_H

//------------------------------------------------------------------------
// Rôle de la tâche <GestionFeux>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
#include <string>

//------------------------------------------------------------- Constantes

//Définition des durées initiales des voies NS et SE.
#define dureeInitNS 12
#define dureeInitEO 12

//Définition du temps passé dans l'état Orange
#define dureeOrange 3

//Définition du temps pendant lequel les feux NS et EO sont simultanément rouges
#define dureeRougeSimultane 2

static char * charCouleur[3]={(char *)"Vert",(char *)"Orange",(char *)"Rouge"};



//------------------------------------------------------------------ Types




//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

//Création de la tache avec les paramètres de durée par défaut
// si appel de la méthode sans paramètre
void CreationGestionFeux(int muteuxFeuId,int SHMDureeFeuId, int SHMEtatFeuId);

#endif // GestionFeux_H
