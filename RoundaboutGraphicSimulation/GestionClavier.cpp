/*************************************************************************
                           GestionClavier  -  description
                             -------------------
    début                : 16 Mars 2015
    copyright            : (C) GestionClavier par cboscher
    e-mail               : cedric.boscher@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <GestionClavier> (fichier GestionClavier.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//------------------------------------------------------ Include personnel
#include "stdio.h"
#include "GestionClavier.h"
#include "Outils.h"
#include "Menu.h"
#include "Voiture.h"
#include "Mere.h"

//------------------------------------------------------------------ Types

//---------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques
// PID du générateur automatique.
static pid_t pidGenerateurClavier;

// Identifiant de la mémoire partagée DuréeFeu associée.
static int shmDFId=0;

// Identifiant du sémaphore associé à la mémoire partagée DuréeFeu.
static int mutexDureeFeuId=0;

// Identifiant de la Fifo associée.
static int fifoVoieId;

// Pointeur vers la zone mémoire partagée (Durée Feu).
static int * zone_DFeux;

// Compteur de voitures générées manuellement
static long compteurManuel=numeroMinManuel;

// Etat du générateur (Inactif par défaut).
static bool generateurActif;

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GestionClavier (pid_t pidGen,  int mutexDFeuId, int shmDureeFeuId, int fifoId )
{
	// Initialisation du PID et des identifiants
	pidGenerateurClavier=pidGen;
	shmDFId=shmDureeFeuId;
	fifoVoieId=fifoId;
	mutexDureeFeuId=mutexDFeuId;
	
	// Initialisation de l'état du Générateur.
	generateurActif=false;
	
	// Attachement à la zone mémoire partagée DuréeFeu.
	zone_DFeux = (int *) shmat(shmDFId, 0, 0);
	
	// Entrée de l'utilisateur dans le Menu.
	Menu();
}
	
void Commande (char code)
{
	if ((code =='Q') or (code == 'q'))
	{
		//Détachement de la zone mémoire partagée.
		shmdt (zone_DFeux);
		exit(EXIT_SUCCESS);
	}
	
	else if ((code = 'G') or (code =='g'))
	{
			if (generateurActif)
			{
				Afficher(ETAT_GENERATEUR,"OFF");
				kill(pidGenerateurClavier, SIGSTOP);
			}
			
			else
			{	
				Effacer(ETAT_GENERATEUR);
				Afficher(ETAT_GENERATEUR,"ON ");
				kill(pidGenerateurClavier, SIGCONT);
			}
	}
	
	// Changement d'état pour le prochain appel fonction.
	generateurActif=!generateurActif;
}


void Commande (TypeVoie entree, TypeVoie sortie)
{
	
	if (compteurManuel<numeroMaxManuel)
	
	{	
		// Création d'une voiture.
		struct Voiture voitureMan;
		
		voitureMan.numero=compteurManuel;
		voitureMan.entree=entree;
		voitureMan.sortie=sortie;
		
		//Création du Message correspondant.
		struct MsgVoiture * MessageVoiture = (MsgVoiture *) malloc (sizeof(MsgVoiture)) ;
		
		MessageVoiture->uneVoiture=voitureMan;
		MessageVoiture->type=compteurManuel;
		
		//Envoi du Message 
		msgsnd(fifoVoieId, MessageVoiture, sizeof(MsgVoiture),0); 
		
		
		
		Afficher(NUMERO,compteurManuel,GRAS);
		Afficher(ENTREE,entree,GRAS);
		Afficher(SORTIE,sortie,GRAS);
		OperationVoie (PLUS, entree);
		compteurManuel++;
	}
	
	else
	{
		Afficher(MESSAGE, "Maximum d'ajouts manuels atteint !");
		
	}
}

void Commande(TypeVoie voie, unsigned int duree)
// Ecriture en mémoire partagée du changement de durée.
{
	
	if ( (voie == NORD) or (voie == SUD))
	{
	// Réservation de la mémoire partagée Duree Feu
	semop(mutexDureeFeuId, &reserverSHMDuree, 1);
	
	//Ecriture de la durée du feu NS.
	* zone_DFeux=duree;
	
	//Libération de la mémoire partagée Duree Feu.
	semop (mutexDureeFeuId, &libererSHMDuree, 1);
	
	Afficher (DUREE_AXE_NS,duree);
	}
	
	else
	{
		
	Afficher (DUREE_AXE_EO,duree);
	
	// Réservation de la mémoire partagée Duree Feu
	semop(mutexDureeFeuId, &reserverSHMDuree, 1);
	
	//Ecriture de la durée du feu EO
	* (zone_DFeux+1)=duree;
	
	//Libération de la mémoire partagée Duree Feu
	semop (mutexDureeFeuId, &libererSHMDuree, 1);
	}

}
