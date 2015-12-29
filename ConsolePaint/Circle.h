/*************************************************************************
                           Circle.h  -  Declaration des méthodes et
                           attributs de la classe Circle
                             -------------------
    début
    *      : 22 octobre 2014
    copyright            : (C) 2014 Cédric Boscher et Romain Bourrier
    e-mail               : cedric.boscher@insa-lyon.fr
                           romain.bourrier@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <Circle> (fichier Circle.h) ------

//--------------------------------------------------- Interfaces utilisées
#if ! defined ( CIRCLE_H )
#define CIRCLE_H
using namespace std;
#include <string>
#include "Forme.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Circle>
// 
//
//------------------------------------------------------------------------

class Circle : public Forme
{
//----------------------------------------------------------------- PUBLIC


//------------------------------------------- Constructeurs - Destructeurs
	public:
	Circle(string ,int ,int , int );
	// Mode d'emploi: Appeler la fonction pour créer une instance de
	// classe
	// Circle avec paramètres par défaut (voir "Circle.cpp").

	Circle(const Circle &unCircle);
    virtual ~Circle ();
    // Mode d'emploi : Destructeur.
    // Methode appelée de façon automatique lorsque le
    // programme principala fini d'utiliser une instance de classe
    // Circle.


//-------------------------------------------- Méthodes publiques

	public:
	bool IsSelected(int,int,int,int);
	void Deplacer(int,int);
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

	int coorX;
	int coorY;
	int rayon;
    

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés


//--------------------------------------- Types dépendants de <Circle>
};
#endif // CIRCLE_H

