/*************************************************************************
                           GestionFeux  -  Gestion du fonctionnement des feux
                             -------------------
    début                : Mars 2015
    copyright            : (C) GestionFeux par cboscher
    e-mail               : cedric.boscher@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <GestionFeux> (fichier GestionFeux.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
//------------------------------------------------------ Include personnel
#include "stdio.h"
#include "GestionFeux.h"
#include "Outils.h"
#include "Menu.h"
#include "Voiture.h"
#include "Mere.h"

//------------------------------------------------------------------ Types

//---------------------------------------------------- Constantes



//---------------------------------------------------- Variables statiques


// Pointeur vers la zone mémoire partagée (Etat Feu).
static int * zone_EFeux;
// Pointeur vers la zone mémoire partagée (Durée Feu).
static int * zone_DFeux;

// Structure de durée des feux, initialisée par la tâche puis actualisée par lecture de la mémoire partagée Duree Feux.
static struct DureeFeux duree_Feux;

// Structure d'etat des feux, initialisée et manipulée par la tâche, puis écrite dans la mémoire partagée Etat Feux.
static struct EtatFeux etat_Feux;

//------------------------------------------------------ Fonctions privées


static void SwitchFeuNS()
// Changement de couleur et du temps du feu NS. 
{
	if (etat_Feux.couleurNS==VERT)
	{
		etat_Feux.tempsNS=dureeOrange;
		etat_Feux.couleurNS=ORANGE;
	}
	
	else if(etat_Feux.couleurNS==ORANGE)
	{	
		etat_Feux.tempsNS=2*dureeRougeSimultane+dureeOrange+duree_Feux.dureeEO;
		etat_Feux.couleurNS=ROUGE;
	}
	
	else
	{
		etat_Feux.tempsNS=duree_Feux.dureeNS;
		etat_Feux.couleurNS=VERT;
	}
}

static void SwitchFeuEO()
// Changement de couleur et du temps du feu EO. 
{
	if (etat_Feux.couleurEO==VERT)
	{
		etat_Feux.tempsEO=dureeOrange;
		etat_Feux.couleurEO=ORANGE;
	}
	
	else if(etat_Feux.couleurEO==ORANGE)
	{	
		etat_Feux.tempsEO=2*dureeRougeSimultane+dureeOrange+duree_Feux.dureeNS;
		etat_Feux.couleurEO=ROUGE;
	}
	
	else
	{
		etat_Feux.tempsEO=duree_Feux.dureeEO;
		etat_Feux.couleurEO=VERT;
	}
}

static void AfficherFeux(EtatFeux etat)
// Affichage des couleurs des feux des axes de circulation et des temps respectifs.
{	Effacer(COULEUR_AXE_NS);
	Afficher(COULEUR_AXE_NS,charCouleur[etat.couleurNS]);
	Afficher(TEMPS_AXE_NS,etat.tempsNS);
	
	Effacer(COULEUR_AXE_EO);
	Afficher(COULEUR_AXE_EO,charCouleur[etat.couleurEO]);
	Afficher(TEMPS_AXE_EO,etat.tempsEO);
	
}

static void FinTache(int sig, siginfo_t *si, void *inutile)
// Procédure du Handler de fin de tâche, appelée sur récéption de SIGUSR2.
{
	// On détache les mémoires partagées.
	shmdt(zone_EFeux);
	
	shmdt(zone_DFeux);
	
	exit (0);
}



// Création de la tache GestionFeux.
void CreationGestionFeux(int mutexFeuId,int shmDureeFeuId, int shmEtatFeuId)
{
		
	
		// Créer liens avec les mémoires partagées.
		zone_DFeux=(int *) (shmat(shmDureeFeuId,0,SHM_RDONLY));
		zone_EFeux=(int*) (shmat(shmEtatFeuId,0,0));
		
		// Création du handler de fin de tâche.
		struct sigaction endTasksa;
		endTasksa.sa_flags=SA_SIGINFO;
		sigemptyset(&endTasksa.sa_mask);
		endTasksa.sa_sigaction=FinTache;
		sigaction(SIGUSR2,&endTasksa,NULL);
		
		// Initialisation couleur et temps feux.
		
		duree_Feux.dureeEO=dureeInitEO;
		duree_Feux.dureeNS=dureeInitNS;
		
		etat_Feux.couleurEO=ROUGE;
		etat_Feux.couleurNS=VERT;
		etat_Feux.tempsEO=dureeInitNS + dureeOrange + dureeRougeSimultane;
		etat_Feux.tempsNS=dureeInitNS;
		
		Afficher (DUREE_AXE_EO,dureeInitEO);
		Afficher (DUREE_AXE_NS,dureeInitNS);
		
		
		while(true)
		// Mise à jour des feux sur l'espace d'une seconde.
		{
			AfficherFeux(etat_Feux);
			/* Mise à jour des durées (en cas de changement)*/
			
			// On réserve la ressource critique Durée Feux
			semop(mutexFeuId, &reserverSHMDuree, -1); 
			
			// On lit dureeNS et dureeEO dans la mémoire partagée.
			duree_Feux.dureeNS=*zone_DFeux;
			duree_Feux.dureeEO=*(zone_DFeux+1);
			
			// On libere la ressource critique Durée Feux.
			semop(mutexFeuId, &libererSHMDuree, 1); 
			
			
			// Mise à jour des temps des feux
			
			etat_Feux.tempsNS--;
			etat_Feux.tempsEO--;
			
			// On change l'état des feux lorsqu'on arrive à l'expiration du temps passé dans un état.
			if (etat_Feux.tempsNS==0)
			{
				SwitchFeuNS();
			}
			
			if (etat_Feux.tempsEO==0)
			{
				SwitchFeuEO();
			}
			
			// On réserve la ressource critique Etat Feux.
			semop(mutexFeuId,&reserverSHMEtat,-1);
			
			// On actualise l'état des feux dans la mémoire partagée.
			*zone_EFeux=etat_Feux.couleurNS;
			*(zone_EFeux+1)=etat_Feux.couleurEO;
			
			// On libère la ressource critique Etat Feux.
			semop(mutexFeuId,&libererSHMEtat,1);
			
			//Tempo 1 seconde.
			sleep(1);
			
		}

}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

	
