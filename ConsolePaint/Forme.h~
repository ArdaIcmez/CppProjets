/*************************************************************************
                           Forme.h  -  Declaration des méthodes et
                           attributs de la classe Forme
                             -------------------
    début
    *      : 22 octobre 2014
    copyright            : (C) 2014 Cédric Boscher et Romain Bourrier
    e-mail               : cedric.boscher@insa-lyon.fr
                           romain.bourrier@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <Forme> (fichier Forme.h) ------

//--------------------------------------------------- Interfaces utilisées
#if ! defined ( FORME_H )
#define FORME_H
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Forme>
// 
//
//------------------------------------------------------------------------

class Forme
{
//----------------------------------------------------------------- PUBLIC


//------------------------------------------- Constructeurs - Destructeurs
	public:
	Forme();
	// Mode d'emploi: Appeler la fonction pour créer une instance de
	// classe
	// Forme avec paramètres par défaut (voir "Forme.cpp").
	Forme(string name);
	Forme(const Forme &unForme);
    virtual ~Forme ();
    // Mode d'emploi : Destructeur.
    // Methode appelée de façon automatique lorsque le
    // programme principala fini d'utiliser une instance de classe
    // Forme.


//-------------------------------------------- Méthodes publiques

	public:
	
	virtual bool IsSelected(int,int,int,int); 
	virtual void Deplacer(int,int);
	virtual void Afficher();
	virtual string Sauvegarder();
	bool SelectedPoint(int X, int Y, int X1, int Y1, int X2, int Y2);
	virtual Forme* Clone();
	virtual string GetName();
   
//------------------------------------------------------ Attributs publics

//------------------------------------------------------------------ PRIVE

	protected:
//----------------------------------------------------- Méthodes protégées

	private:


//------------------------------------------------------- Méthodes privées

	

	protected:
//----------------------------------------------------- Attributs protégés
	string name;
	private:

//------------------------------------------------------- Attributs privés



    

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés


//--------------------------------------- Types dépendants de <Forme>
};
#endif // FORME_H
