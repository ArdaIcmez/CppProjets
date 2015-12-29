/*************************************************************************
                           capteur.cpp
                             -------------------
    début                : 22 octobre 2014
    copyright            : (C) 2014 par Arda Içmez & Nicolas Nadisic
*************************************************************************/

/**
 * Mesure *mesureTout
 **/

//---------- Réalisation de la classe <capteur> (fichier capteur.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <ctime>
//------------------------------------------------------ Include personnel
#include "capteur.h"
//------------------------------------------------------------- Constantes


//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type capteur::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


void Capteur::setEvenementPrecedent(tm instant)
{
	evenementPrecedent.tm_year=instant.tm_year;
	evenementPrecedent.tm_mon=instant.tm_mon;
	evenementPrecedent.tm_mday=instant.tm_mday;
	evenementPrecedent.tm_hour=instant.tm_hour;
	evenementPrecedent.tm_min=instant.tm_min;
	evenementPrecedent.tm_sec=instant.tm_sec;
	evenementPrecedent.tm_wday=instant.tm_wday;
}
tm Capteur::getEvenementPrecedent()
{
	return evenementPrecedent;
}
void Capteur::setTrafficPrecedent(char etat)
{
	trafficPrecedent = etat;
}
char Capteur::getTrafficPrecedent()
{
	return trafficPrecedent;
}
void Capteur::AjouterDonne(char traf,double duree)
{
	switch(traf)
	{
		case 'V':
		tempsVert += duree;
		break;
		
		case 'J':
		tempsJaune += duree;
		break;
		
		case 'N':
		tempsNoir += duree;
		break;
		
		case 'R':
		tempsRouge += duree;
		break;
		
		default:
		cout<<"ERREUR"<<endl;
		break;
	}
}
void Capteur::GetStats()
{
	double totalTemps = tempsVert + tempsRouge + tempsJaune + tempsNoir;
	if(totalTemps)
	{
	cout << "V " << (int)(tempsVert*100/totalTemps) << "%" << "\r\n";
	cout << "J " << (int)(tempsJaune*100/totalTemps)  << "%" << "\r\n";
	cout << "R " << (int)(tempsRouge*100/totalTemps)  << "%" << "\r\n";
	cout << "N " << (int)(tempsNoir*100/totalTemps)  << "%" << "\r\n";
	}
	else
	{
	cout << "V " << 0<< "%" << "\r\n";
	cout << "J " << 0<< "%" << "\r\n";
	cout << "R " << 0<< "%" << "\r\n";
	cout << "N " << 0<< "%" << "\r\n";
	}
}
bool Capteur::getEtat()
{
	return ((trafficPrecedent == 'R' || trafficPrecedent == 'N') ? true : false);
}
//------------------------------------------------- Surcharge d'opérateurs
//Capteur & Capteur::operator = ( const Capteur &unCapteur )
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Capteur::Capteur ( const Capteur &unCapteur )
// Algorithme :
//
{
#ifdef MAP
   // cout << "Appel au constructeur de copie de <capteur>" << endl;
#endif 
} //----- Fin de capteur (constructeur de copie)


Capteur::Capteur ( )
// Algorithme :
//
{	
	trafficPrecedent='x';
	tempsRouge=0;
	tempsNoir=0;
	tempsVert=0;
	tempsJaune=0;
#ifdef MAP
   // cout << "Appel au constructeur de <capteur>" << endl;
#endif
} //----- Fin de capteur


Capteur::~Capteur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <capteur>" << endl;
#endif
} //----- Fin de ~capteur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

