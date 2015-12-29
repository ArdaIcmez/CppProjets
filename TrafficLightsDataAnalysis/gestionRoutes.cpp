/*************************************************************************
                           gestionRoutes  - Main du TP 2 C++
                             -------------------
    début                : 22 octobre 2014
    copyright            : (C) 2014 par Arda Içmez & Nicolas Nadisic
*************************************************************************/


//--- Réalisation du module <gestionRoutes> (fichier gestionRoutes.cpp) --

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <ctime>
#include <string.h>
//------------------------------------------------------ Include personnel
#include "gestionRoutes.h"
#include "capteur.h"
#include "mesure.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
tm derniereEvenement;
Capteur listeCapteur[1500];
Mesure listeHeures[7][24];
Mesure listeJours[7];
bool capteurExiste[1500] = {0};
tm pireMoment;
double pireBouchons=0;
double totalBouchons=0;
//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom
void AjouterEvenement(tm evenement);
int DiffTemps(tm premiere,tm deuxieme);
int Separation(tm &evenementSepare);
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// Algorithme :
//
int main()
{
    derniereEvenement.tm_year = 2014;
	derniereEvenement.tm_mon = 1;
	derniereEvenement.tm_mday = 1;
	derniereEvenement.tm_hour = 1;
	derniereEvenement.tm_min = 0;
	derniereEvenement.tm_sec = 0;
	derniereEvenement.tm_wday=1;
	pireMoment=derniereEvenement;
	int valCapt;
	int valYear;
	int valMonth;
	int valDay;
	int valHour;
	int valMin;
	int valSec;
	int valWeekDay;
	char valTraf;
	string commande; 
	do{
		cin >> commande;
		if(!commande.compare("ADD"))
		{
			cin >> valCapt;
			cin >> valYear;
			cin >> valMonth;
			cin >> valDay;
			cin >> valHour;
			cin >> valMin;
			cin >> valSec;
			cin >> valWeekDay;
			cin >> valTraf;
			valWeekDay %= 7;
			tm addition;
			addition.tm_year=valYear;
			addition.tm_mon=valMonth;
			addition.tm_mday=valDay;
			addition.tm_hour=valHour;
			addition.tm_min=valMin;
			addition.tm_sec=valSec;
			addition.tm_wday=valWeekDay;
			AjouterEvenement(addition);
			listeCapteur[valCapt].setEvenementPrecedent(addition);
			listeCapteur[valCapt].setTrafficPrecedent(valTraf);
			capteurExiste[valCapt]=true;
		}
		else if(!commande.compare("STATS_C"))
		{
			cin >> valCapt;
			listeCapteur[valCapt].GetStats();
		}
		else if(!commande.compare("STATS_D7"))
		{
			cin >> valDay;
			valDay %=7;
			listeJours[valDay].GetStats();		
		}
		else if(!commande.compare("STATS_D7_H24"))
		{
			cin >> valDay;
			valDay %=7;
			cin >> valHour;
			listeHeures[valDay][valHour].GetStats();		
		}
		else if(!commande.compare("MAX_TS"))
		{
			if(totalBouchons)
			{
				cout << pireMoment.tm_year<<" "<< pireMoment.tm_mon<<" "<< pireMoment.tm_mday<<" ";
				cout << pireMoment.tm_hour<<" "<<pireMoment.tm_min<<" "<< pireMoment.tm_sec<<" ";
				cout << (int)((pireBouchons/totalBouchons)*100) << "%\r\n";
			}
			else
			{
				cout <<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<"%\r\n";
			}
		}
	}
	while(commande.compare("EXIT"));
	

	return 0;
}
int DiffTemps(tm premiere,tm deuxieme) // Pour voir le difference entre 2 structs
{
	time_t t1,t2;
	tm temp = premiere;
	t1 = mktime(&temp);
	temp = deuxieme;
	t2 = mktime(&(temp));
	double deltaTemps = difftime(t1,t2);
	return deltaTemps;
}
int Separation(tm &evenementSepare) // Pour calculer combien de temps il reste
{
	tm temps = evenementSepare;
	time_t t1 ;
	t1 = mktime(&temps);
	int i;
	for(i=0;i<=300;i++)
	{
		tm *t2 = localtime(&t1);
		if(temps.tm_hour != t2->tm_hour)
		{
			return i;
		}
		t1++;
	}
	return 0;
}
void AjouterEvenement(tm evenement) // Pour ajouter une evenement et l'updater
{
        int bouchonRougeNoire=0;
        int bouchonTotale=0;
        double tempsDiff1=0,tempsDiff2=0;
        int tempsReste=0;
        char etatExiste;
        for(int i=0; i<1500; i++)
        {
			if(capteurExiste[i])// pour voir si le capteur existe
			{
				etatExiste = listeCapteur[i].getTrafficPrecedent();
				tm captEvent = listeCapteur[i].getEvenementPrecedent();
				tempsDiff1 = DiffTemps(derniereEvenement,captEvent);
				//tempsReste = Separation(derniereEvenement); Le calcul ci-dessus est plus vite donc je vais l'utiliser.			
				tempsReste = 60*60 - (derniereEvenement.tm_hour*60 + derniereEvenement.tm_min);
				if(tempsDiff1>300)// Pour voir si l'effet d'evenement est fini.
					{
						listeCapteur[i].setTrafficPrecedent('x');
						etatExiste = 'x';
					}
				if(etatExiste!='x')
				{
					tm tempAjout = listeCapteur[i].getEvenementPrecedent();
					tempsDiff2=DiffTemps(evenement,tempAjout);
					tempsDiff2-=tempsDiff1;
					bouchonRougeNoire+=listeCapteur[i].getEtat();
					bouchonTotale++;
					if(derniereEvenement.tm_min<55)
						{
						listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour].AjouterDonne(etatExiste,tempsDiff2);
						listeJours[derniereEvenement.tm_wday].AjouterDonne(etatExiste,tempsDiff2);
						}
					else if(derniereEvenement.tm_hour!=23)
						{
						if (tempsDiff2>tempsReste)
							{
							listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour].AjouterDonne(etatExiste,tempsReste);
							listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour+1].AjouterDonne(etatExiste,tempsDiff2-tempsReste);
							}
						else
							{
							listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour].AjouterDonne(etatExiste,tempsDiff2);
							}
						listeJours[derniereEvenement.tm_wday].AjouterDonne(etatExiste,tempsDiff2);
						}
					else
						{
						if(tempsDiff2>tempsReste)
							{
							listeJours[derniereEvenement.tm_wday].AjouterDonne(etatExiste,tempsReste);
							listeJours[(derniereEvenement.tm_wday+1)%7].AjouterDonne(etatExiste,tempsDiff2-tempsReste);
							listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour].AjouterDonne(etatExiste,tempsReste);
							listeHeures[derniereEvenement.tm_wday][(derniereEvenement.tm_hour+1)%24].AjouterDonne(etatExiste,tempsDiff2-tempsReste);
							}
						else
							{
							listeHeures[derniereEvenement.tm_wday][derniereEvenement.tm_hour].AjouterDonne(etatExiste,tempsDiff2);
							listeJours[derniereEvenement.tm_wday].AjouterDonne(etatExiste,tempsDiff2);
							}
						}
					listeCapteur[i].AjouterDonne(etatExiste,tempsDiff2);
				}
			}
		}
        if(bouchonRougeNoire>pireBouchons) // pour comparer la nombre de R ou N bouchons
        {
            pireBouchons=bouchonRougeNoire;
			pireMoment=evenement;
            totalBouchons=bouchonTotale;
        }
		derniereEvenement=evenement;
}
