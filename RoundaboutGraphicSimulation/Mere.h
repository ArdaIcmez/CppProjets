/*************************************************************************
                           Mere  -  interface
                             -------------------
    début                : 16 Mars 2015
    copyright            : (C) Mere par aicmez
    e-mail               : arda.icmez@insa-lyon.fr
*************************************************************************/
#if ! defined ( MERE_H )
#define MERE_H

static struct sembuf reserverSHMDuree {0,-1,0};
static struct sembuf libererSHMDuree {0,1,0};

static struct sembuf reserverSHMEtat {1,-1,0};
static struct sembuf libererSHMEtat {1,1,0};

enum CouleurFeu{VERT,ORANGE,ROUGE};

struct EtatFeux
{
	
	int tempsNS;
	int tempsEO;
	
	CouleurFeu couleurNS;
	CouleurFeu couleurEO;
	
	
};

struct DureeFeux
{
	int dureeNS;
	int dureeEO;
};

int main();

#endif // MERE_H
