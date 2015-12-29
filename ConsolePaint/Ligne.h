/*************************************************************************
                           Ligne.h  -  Declaration des méthodes et
                           attributs de la classe Ligne
                             -------------------
    début
    *      : 22 octobre 2014
    copyright            : (C) 2014 Cédric Boscher et Romain Bourrier
    e-mail               : cedric.boscher@insa-lyon.fr
                           romain.bourrier@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <Ligne> (fichier Ligne.h) ------

//--------------------------------------------------- Interfaces utilisées
#if ! defined ( Ligne_H )
#define Ligne_H
using namespace std;
#include <string>
#include "Forme.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Ligne>
// 
//
//------------------------------------------------------------------------

class Ligne : public Forme
{
//----------------------------------------------------------------- PUBLIC


//------------------------------------------- Constructeurs - Destructeurs
	public:
	Ligne(string ,int ,int , int ,int);
	// Mode d'emploi: Appeler la fonction pour créer une instance de
	// classe
	// Ligne avec paramètres par défaut (voir "Ligne.cpp").

	Ligne(const Ligne &unLigne);
    virtual ~Ligne ();
    // Mode d'emploi : Destructeur.
    // Methode appelée de façon automatique lorsque le
    // programme principala fini d'utiliser une instance de classe
    // Ligne.


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

	int coorX1;
	int coorY1;
	int coorX2;
	int coorY2;
    
    

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés


//--------------------------------------- Types dépendants de <Ligne>
};
#endif // Ligne_H


