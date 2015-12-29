/*************************************************************************
                           Rectangle.h  -  Declaration des méthodes et
                           attributs de la classe Rectangle
                             -------------------
    début
    *      : 22 octobre 2014
    copyright            : (C) 2014 Cédric Boscher et Romain Bourrier
    e-mail               : cedric.boscher@insa-lyon.fr
                           romain.bourrier@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <Rectangle> (fichier Rectangle.h) ------

//--------------------------------------------------- Interfaces utilisées
#if ! defined ( Rectangle_H )
#define Rectangle_H
using namespace std;
#include <string>
#include "Forme.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Rectangle>
// 
//
//------------------------------------------------------------------------

class Rectangle : public Forme
{
//----------------------------------------------------------------- PUBLIC


//------------------------------------------- Constructeurs - Destructeurs
	public:
	Rectangle(string ,int ,int , int,int );
	// Mode d'emploi: Appeler la fonction pour créer une instance de
	// classe
	// Rectangle avec paramètres par défaut (voir "Rectangle.cpp").

	Rectangle(const Rectangle &unRectangle);
    virtual ~Rectangle ();
    // Mode d'emploi : Destructeur.
    // Methode appelée de façon automatique lorsque le
    // programme principala fini d'utiliser une instance de classe
    // Rectangle.


//-------------------------------------------- Méthodes publiques

	public:
	
    bool IsSelected(int,int,int,int);
	void Deplacer (int,int);
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


//--------------------------------------- Types dépendants de <Rectangle>
};
#endif // Rectangle_H


