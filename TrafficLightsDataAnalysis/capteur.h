/*************************************************************************
                           capteur.h
                             -------------------
    début                : 22 octobre 2014
    copyright            : (C) 2014 par Arda Içmez & Nicolas Nadisic
*************************************************************************/

//---------- Interface de la classe <capteur> (fichier capteur.h) ------
#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

//--------------------------------------------------- Interfaces utilisées
class Mesure;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <capteur>
//
//
//------------------------------------------------------------------------

class Capteur 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setEvenementPrecedent(tm instant);
    tm getEvenementPrecedent();
    void setTrafficPrecedent(char etat);
    char getTrafficPrecedent();
	void AjouterDonne(char traf,double duree);
	void GetStats();
	bool getEtat();
//------------------------------------------------- Surcharge d'opérateurs
    Capteur & operator = ( const Capteur & unCapteur );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Capteur ( const Capteur & unCapteur );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Capteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    virtual ~Capteur ( );
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
tm evenementPrecedent;
char trafficPrecedent;
double tempsRouge;
double tempsNoir;
double tempsVert;
double tempsJaune;
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <capteur>

#endif // CAPTEUR_H

