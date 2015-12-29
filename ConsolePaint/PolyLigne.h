/*************************************************************************
                           PolyLigne.h  -  Declaration des méthodes et
                           attributs de la classe PolyLigne
                             -------------------
    début
    *      : 22 octobre 2014
    copyright            : (C) 2014 Cédric Boscher et Romain Bourrier
    e-mail               : cedric.boscher@insa-lyon.fr
                           romain.bourrier@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <PolyLigne> (fichier PolyLigne.h) ------

//--------------------------------------------------- Interfaces utilisées
#if ! defined ( PolyLigne_H )
#define PolyLigne_H
using namespace std;
#include <string>
#include "Forme.h"
#include <vector>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PolyLigne>
// 
//
//------------------------------------------------------------------------

class PolyLigne : public Forme
{
//----------------------------------------------------------------- PUBLIC


//------------------------------------------- Constructeurs - Destructeurs
	public:
	PolyLigne(string name,vector<pair<int,int> > points);
	// Mode d'emploi: Appeler la fonction pour créer une instance de
	// classe
	// PolyLigne avec paramètres par défaut (voir "PolyLigne.cpp").

	PolyLigne(const PolyLigne &unPolyLigne);
    virtual ~PolyLigne ();
    // Mode d'emploi : Destructeur.
    // Methode appelée de façon automatique lorsque le
    // programme principala fini d'utiliser une instance de classe
    // PolyLigne.


//-------------------------------------------- Méthodes publiques

	public:
	
	
    bool IsSelected(int,int,int,int);
	void Deplacer (int, int);
	void Afficher();
	string Sauvegarder();
	string GetName();
	Forme* Clone();
//------------------------------------------------------ Attributs publics

//------------------------------------------------------------------ PRIVE

	protected:
//----------------------------------------------------- Méthodes protégées

	private:


//------------------------------------------------------- Méthodes privées

	
	
	 

	protected:
//----------------------------------------------------- Attributs protégés

	private:

//------------------------------------------------------- Attributs privés

	vector <pair <int,int> > points;
    
    

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés


//--------------------------------------- Types dépendants de <PolyLigne>
};
#endif // PolyLigne_H

