/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 21 Mars 2015
    copyright            : (C) Voie par aicmez
    e-mail               : arda.icmez@insa-lyon.fr
*************************************************************************/
#include <vector>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <Voiture.h>
#include <Outils.h>
using namespace std;
#include "stdio.h"
#include "Outils.h"
#include "Voie.h"
#include "Mere.h"
#include "GestionFeux.h"


static std::vector<pid_t> mouvementVector;
static TypeVoie laVoie;
int laBAL;
static CouleurFeu * laFeux;
static struct EtatFeux lEtat;

static void handlerMouvement (int typeSignal)
// Algorithm :
// Recherche du pid qui a  envoyé le signal, et suppression
{
  if (typeSignal == SIGCHLD)
  {
    // Supression des voiture qui sont fini
    int situation;
    pid_t pidFils = wait(&situation);
    std::vector<pid_t> ::iterator it;
    it=mouvementVector.begin();
    while ((*it)!=pidFils)
    {
      it++;
    }
    mouvementVector.erase(it);
  }
}
static void  handlerTache (int laSignal) // 
// Algorithm :
// On tue toutes les taches qui sont stockees dans le vecteur pour la fin de la tâche
{
  if (laSignal == SIGUSR2)
  {
    // Suppression
    std::vector<pid_t> ::iterator it;
    for(it=mouvementVector.begin();it!=mouvementVector.end();it++)
	{
     		kill((*it),SIGUSR2);
      		waitpid((*it),NULL,0);
    }
    // Détachement de la mémoire
    shmdt (laFeux);
    exit(0);
  }
}

void Voie(TypeVoie numerVoie, int idFile, int idFeux, int semId )
// Algorithm :
// Activation des signales
// Ajout de la voiture a la vector qui stock les voitures qui bouge.
// Attend que le feux est vert pour qu'on puisse bouge la voiture 
{

  // Debut Phase Initialisation 

  // MASK de SIGUSR2
  
  struct sigaction actionFinTache;
  actionFinTache.sa_handler = handlerTache;
  actionFinTache.sa_flags = 0;
  sigaction (SIGUSR2, &actionFinTache, NULL);

  // MASK de SIGCHLD

  struct sigaction actionFinMouvement;
  actionFinMouvement.sa_handler = handlerMouvement;
  actionFinMouvement.sa_flags = 0;
  sigaction (SIGCHLD, &actionFinMouvement, NULL);

  // Réception d'un message dans la boite aux lettres (Outils.h)
  struct MsgVoiture laMessage;
  // Attachement de la mémoire partagée
  laFeux = (CouleurFeu *) shmat(idFeux, NULL, SHM_RDONLY);

  laBAL = idFile ;
  laVoie = numerVoie;

// Debut Phase Motor
  for (;;)
  {
    // Attente de la voiture
    if(msgrcv(laBAL, &laMessage, TAILLE_MSG_VOITURE, laVoie, 1)!=-1)//TAILLE_MSG_VOITURE definie en Voiture.h
    {
      // Notre display  
      DessinerVoitureFeu(laMessage.uneVoiture.numero, laMessage.uneVoiture.entree, laMessage.uneVoiture.sortie); // definie en Outils.h
      OperationVoie (MOINS, laVoie);//Definie en Outils.h
      
	 semop(semId,&reserverSHMEtat,1);
	 lEtat.couleurNS=*laFeux;
	 lEtat.couleurEO=*(laFeux+1);
	 semop(semId,&libererSHMEtat,1);
	 
      if (laVoie == EST || laVoie == OUEST)// NORD EST OUEST SUD definie dans Outils.h
      {        
	// On attend la feux vert
        while (lEtat.couleurEO!=VERT)
        {
		semop(semId,&reserverSHMEtat,1);
	    lEtat.couleurEO=*(laFeux+1);
	    semop(semId,&libererSHMEtat,1);
          sleep(1);
        }

        // Création de la tache pour bouger la voiture et addition de a la liste des taches
        pid_t voitureBouge =DeplacerVoiture(laMessage.uneVoiture.numero, laMessage.uneVoiture.entree, laMessage.uneVoiture.sortie);
        mouvementVector.push_back(voitureBouge);
 
      }
      else if (laVoie == NORD || laVoie == SUD)
      {
       // On attend la feux vert
        while (lEtat.couleurNS!=VERT)
        {
		semop(semId,&reserverSHMEtat,1);
	    lEtat.couleurNS=*(laFeux);
	    semop(semId,&libererSHMEtat,1);
         sleep(1);
        }
        
        // Création de la tache pour bouger la voiture et addition de a la liste des taches
        pid_t voitureBouge =DeplacerVoiture(laMessage.uneVoiture.numero, laMessage.uneVoiture.entree, laMessage.uneVoiture.sortie);
        mouvementVector.push_back(voitureBouge);
      }
      else{ }//TypeVoie est AUCUNE qui est impossible en generale, il faut implementer(?) une contre-action pour ça
      
    }
  }
} //----- fin de Voie

