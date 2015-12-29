/*************************************************************************
                           mesure.h
                             -------------------
    début                : 22 octobre 2014
    copyright            : (C) 2014 par Arda Içmez & Nicolas Nadisic
*************************************************************************/

//---------- Interface de la classe <mesure> (fichier mesure.h) ------
#if ! defined ( MESURE_H )
#define MESURE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <mesure>
//
//
//------------------------------------------------------------------------

class Mesure 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
void AjouterDonne(char traf,double duree);
void GetStats();
//------------------------------------------------- Surcharge d'opérateurs
	Mesure & operator = ( const Mesure &unMesure );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Mesure ( const Mesure &unMesure );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Mesure ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    virtual ~Mesure ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
private:
//------------------------------------------------------- Attributs privés
double tempsRouge;
double tempsNoir;
double tempsVert;
double tempsJaune;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <mesure>

#endif // MESURE_H

