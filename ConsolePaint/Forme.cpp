/*************************************************************************
                    Forme.cpp - Definition de la classe Forme
                             -------------------
    début                : 14 Janvier 2015
    copyright            : (C) 2014 Arda Içmez et Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr
                           cedric.boscher@insa-lyon.fr
*************************************************************************/

//-------- Réalisation de la classe Forme (Forme.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Forme.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Forme::IsSelected(int x1,int x2,int y1,int y2)
{
	
	return 0;
}

void Forme::Afficher()
{
}

string Forme::Sauvegarder()
{
	string toSave;
	
	return toSave;
}

string Forme::GetName()
{
	return this->name;
}

bool Forme :: SelectedPoint(int X, int Y, int X1, int Y1, int X2, int Y2)
{
	if ( ( ( X<=X1 && X>=X2) && ( Y<=Y1 && Y>=Y2) )
		||  ((X>=X1 && X<=X2) && ( Y>=Y1 && Y<=Y2) ) )
		
	{
		return true;
	}
	
	else
	{
		return false;
	}
	
}

void Forme::Deplacer(int dx,int dy)
{
	cout << "DEPLACER 	Ancetre MARCHE "<<endl;
	
}
Forme* Forme::Clone(){
Forme* tempForme = new Forme;
return tempForme;
}
//-------------------------------------------- Constructeurs - destructeur
Forme::Forme(){cout << "bos const"<<endl;};
Forme::Forme(string name){
	cout << "Constructor F"<<endl;
	this->name = name;
}
Forme::Forme(const Forme &unForme)
{
	cout<<"Cpy F"<<endl;
	this->name=unForme.name;
}

 Forme::~Forme()
 {
	 cout<<"Dest F"<<endl;
 }

//------------------------------------------------------------------ PRIVE

	

//----------------------------------------------------- Méthodes protégées
