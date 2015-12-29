
/*************************************************************************
                    Forme.cpp - Definition de la classe Forme
                             -------------------
    début                : 14 Janvier 2015
    copyright            : (C) 2014 Arda Içmez et Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr
                           cedric.boscher@insa-lyon.fr
*************************************************************************/

//-------- Réalisation de la classe	Ligne (Ligne.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Ligne.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Ligne::IsSelected(int x1,int y1,int x2,int y2)
{
	if ( (SelectedPoint(this->coorX1,this->coorY1, x1, y1, x2, y2)==true)
	&& (SelectedPoint(this->coorX2, this-> coorY2, x1, y1, x2, y2)==true)

	)
	{
		
		return true;
	}
	
	else
	{
		return false;
	}
}

string Ligne::GetName()
{
	return name;
}

void Ligne::Afficher()
{
	cout << "L " << name << " " << coorX1 << " " << coorY1 << " " 
		 << coorX2 << " " << coorY2 << " " << endl;
}

string Ligne::Sauvegarder()
{
	
	stringstream ss;
	
	ss << this->coorX1;
	string scoorX1=ss.str();
	ss.str("");
	ss.clear();
	
	ss << this->coorY1;
	string scoorY1=ss.str();
	ss.str("");
	ss.clear();
	
	ss << this->coorX2;
	string scoorX2=ss.str();
	ss.str("");
	ss.clear();
	
	ss << this->coorY2;
	string scoorY2=ss.str();
	ss.str("");
	ss.clear();
	
	string saveLog= "L " + this->name +" " + scoorX1 + " " + scoorY1 + " "
	+scoorX2 + " " + scoorY2;
	
	return saveLog;
}

void Ligne::Deplacer (int dX, int dY)
{
	coorX1+=dX;
	coorX2+=dX;
	
	coorY1+=dY;
	coorY2+=dY;
}
Forme* Ligne::Clone()
{
	Ligne* tempLigne = new Ligne(this->name,this->coorX1,this->coorY1,this->coorX2,this->coorY2);
	return tempLigne;
}
//-------------------------------------------- Constructeurs - destructeur
Ligne::Ligne(string name,int coorX1,int coorY1, int coorX2, int coorY2) : Forme(name)
{
	cout << "Constructor L"<<endl;
	this->coorX1 = coorX1;
	this->coorY1 = coorY1;
	this->coorX2 = coorX2;
	this->coorY2 = coorY2;
	
}

Ligne::Ligne(const Ligne &unLigne) : Forme(unLigne)
{
	cout << "Cpy L"<<endl;
	this->coorX1 = unLigne.coorX1;
	this->coorY1 = unLigne.coorY1;
	this->coorX2 = unLigne.coorX2;
	this->coorY2 = unLigne.coorY2;
}

 Ligne::~Ligne()
 {
	 cout<<"Dest L"<<endl;
 }
 
//------------------------------------------------------------------ PRIVE

	

//----------------------------------------------------- Méthodes protégées

