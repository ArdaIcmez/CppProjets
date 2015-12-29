/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 16 Mars 2015
    copyright            : (C) Mere par aicmez
    e-mail               : arda.icmez@insa-lyon.fr
*************************************************************************/
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
using namespace std;
#include "Mere.h"
#include "Outils.h"
#include "Generateur.h"
#include "GestionFeux.h"
#include "Voie.h"
#include "GestionClavier.h"
#include "Heure.h"

static void balCreation(int& laFile)
{
    laFile = msgget(IPC_PRIVATE, IPC_CREAT| 0666);
}

static void memoryCreation(int& etatFeuxId, int& dureeId)
{
        // Création de zone de mémoire pour etat
	etatFeuxId = shmget(IPC_PRIVATE, 2*sizeof(EtatFeux), IPC_CREAT | 0666);

	// Création de zone de mémoire pour duree
	dureeId = shmget(IPC_PRIVATE, 2*sizeof(DureeFeux), IPC_CREAT | 0666);
	
	// Initialisation de DureeFeuId
	int * maZone = (int *)shmat(dureeId, 0, 0);
	*maZone=12;
	*(maZone+1)=12;
	Afficher(DUREE_AXE_NS,12);
	Afficher(DUREE_AXE_EO,12);
	shmdt(maZone);
	
	// Initilisation de EtatFeuId
	maZone = (int *)shmat(etatFeuxId, 0, 0);
	*maZone=ROUGE;
	*(maZone+1)=ROUGE;
	shmdt(maZone);
	/*
	// Initialisation
	EtatFeux* memoryEtat = (EtatFeux*) shmat(etatFeux, NULL, 0);
	memoryEtat->couleurNS = VERT;
	memoryEtat->couleurEO = ROUGE;
	memoryEtat->tempsEO=17;
	memoryEtat->tempsNS=12;
	shmdt(memoryEtat); //Detachement 

	// Initialisation
	DureeFeux* memoryDuree = (DureeFeux*) shmat(duree, NULL, 0);
	memoryDuree->dureeNS = 12;
	memoryDuree->dureeEO = 12;
	shmdt(memoryDuree);//Detachement */

}
static void memoryDestruction(int duree, int etatFeux)
{
    shmctl(etatFeux, IPC_RMID, 0);
    shmctl(duree, IPC_RMID, 0);
}
static void balDestruction(int fileVoitures)
{
    msgctl(fileVoitures, IPC_RMID, 0);
}

int main()
// Algorithm: 
// Creation de Semaphore, Memoire Partage et Boite aux Lettres
// Creation et manipulation des Handlers
// Creation des taches : Generateur, Heure, Voie x 4, Feux, Interface
// Attendre la signal de Interface pour commencer la phase destruction
// Destruction des taches : Feux, Voie x 4, Generateur, Heure
// Destruction des Boites aux lettres, Memoires Partagees, Semaphore
// Appel la methode de destruction de Interface
{
	// Debut Phase Initialisaton

    pid_t pidVoie[4];
    pid_t pidFeux;
    pid_t pidInterface;
	pid_t pidGenerateur;
	pid_t pidHeure;
	int idSemop;
	int idEtatFeux;
    int idDure;
    int idFile;
    	
    struct sigaction maskUSR2;
	struct sigaction maskCHLD;
	// Mask pour SIGUSR2
	maskUSR2.sa_handler = SIG_IGN;
	sigemptyset(&maskUSR2.sa_mask);
	maskUSR2.sa_flags = 0;
	sigaction(SIGUSR2,&maskUSR2, NULL);
	// Mask pour SIGCHLD
	maskCHLD.sa_handler = SIG_IGN;
	sigemptyset(&maskCHLD.sa_mask);
	maskCHLD.sa_flags = 0;
	sigaction(SIGCHLD,&maskCHLD, NULL);
	
	// Creation Semaphore
	idSemop = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
	semctl(idSemop, 0, SETVAL, 1);
	semctl(idSemop, 1, SETVAL, 1);

	// Creation Memoire Partagee
   	memoryCreation(idEtatFeux, idDure);

   	 // Création BAL
   	balCreation(idFile);

	

	InitialiserApplication(VT220);

	pidGenerateur = CreerEtActiverGenerateur(0, idFile);
	pidHeure = CreerEtActiverHeure();
	
	
	if((pidVoie[0] = fork()) == 0)
	{
		// Activation Voie Nord
		Voie(NORD,idFile,idEtatFeux,idSemop);// NORD EST OUEST SUD definie dans Outils.h
		}
	else
	{
		if((pidVoie[1] = fork()) == 0)
			{
				// Activation Voie Sud
				Voie(SUD,idFile,idEtatFeux,idSemop);
			}
			else
			{
				if((pidVoie[2] = fork()) == 0)
				{
					// Activation Voie Est
					Voie(EST,idFile,idEtatFeux,idSemop);
				}
				else
				{
					if((pidVoie[3] = fork()) == 0)
					{
						// Activation Voie Ouest ;
						Voie(OUEST,idFile,idEtatFeux,idSemop);
					}
					else
					{
						if((pidFeux = fork()) == 0)
							{
							CreationGestionFeux(idSemop,idDure,idEtatFeux);
									// Activation Feux a implementer
							}
						else
						{
							if((pidInterface = fork()) == 0)
							{
								GestionClavier(pidGenerateur,idFile,idDure,idSemop);
							}
							// Fin Phase Initialisation
							else
							{
								// Debut Phase Destruction

								// Synchronisation de fin
								waitpid(pidInterface, NULL, 0);

								// Destruction de Feux
								kill(pidFeux, SIGUSR2);
								waitpid(pidFeux, NULL, 0);

								// Destruction Voie
								for(int i = 0 ; i < 4 ; i++)
								{
									kill(pidVoie[i], SIGKILL);
									waitpid(pidVoie[i], NULL, 0);
								}

								// Destruction Generateur
								kill(pidGenerateur, SIGCONT);
								kill(pidGenerateur, SIGUSR2);
								waitpid(pidGenerateur, NULL, 0);

								// Destruction Heure
								kill(pidHeure, SIGUSR2);
								waitpid(pidHeure, NULL, 0);


								// Destruction BAL, Semop et MP
								balDestruction(idFile);
								semctl(idSemop, 0, IPC_RMID, 0);
								memoryDestruction(idEtatFeux, idDure);


								TerminerApplication(true);// fonction de Outils
								
								// Fin Phase Destruction
								exit(0);
						}
					}
	}}}}
	return 0;
} 
