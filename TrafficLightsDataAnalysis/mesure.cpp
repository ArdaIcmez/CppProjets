/*************************************************************************
                           mesure.cpp
                             -------------------
    début                : 22 octobre 2014
    copyright            : (C) 2014 par Arda Içmez & Nicolas Nadisic
*************************************************************************/

//---------- Réalisation de la classe <mesure> (fichier mesure.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <ctime>
//------------------------------------------------------ Include personnel
#include "mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type mesure::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Mesure::AjouterDonne(char traf,double duree)
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
void Mesure::GetStats()
{
	double totalTemps = tempsVert + tempsRouge + tempsJaune + tempsNoir;
	if(totalTemps)
	{
	cout << "V " << (int)((tempsVert/totalTemps)*100) << "%" <<"\r\n";
	cout << "J " << (int)((tempsJaune/totalTemps)*100) << "%" << "\r\n";
	cout << "R " << (int)((tempsRouge/totalTemps)*100)  << "%" << "\r\n";
	cout << "N " << (int)((tempsNoir/totalTemps)*100)  << "%" << "\r\n";
	}
	else
	{
	cout << "V " << 0<< "%" << "\r\n";
	cout << "J " << 0<< "%" << "\r\n";
	cout << "R " << 0<< "%" << "\r\n";
	cout << "N " << 0<< "%" << "\r\n";
	}
}
//------------------------------------------------- Surcharge d'opérateurs
//Mesure & Mesure::operator = ( const Mesure & unMesure )
// Algorithme :
//
//{
	
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Mesure::Mesure ( const Mesure & unMesure )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <mesure>" << endl;
#endif
} //----- Fin de mesure (constructeur de copie)


Mesure::Mesure ()
// Algorithme :
//
{
	tempsRouge=0;
	tempsNoir=0;
	tempsVert=0;
	tempsJaune=0;
#ifdef MAP
    //cout << "Appel au constructeur de <mesure>" << endl;
#endif
} //----- Fin de mesure


Mesure::~Mesure ( )
// Algorithme :
//
{
#ifdef MAP
    //cout << "Appel au destructeur de <mesure>" << endl;
#endif
} //----- Fin de ~mesure


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


