
/*************************************************************************
                    Forme.cpp - Definition de la classe Forme
                             -------------------
    début                : 14 Janvier 2015
    copyright            : (C) 2014 Arda Içmez et Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr
                           cedric.boscher@insa-lyon.fr
*************************************************************************/

//-------- Réalisation de la classe	Rectangle (Rectangle.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Rectangle.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Rectangle::IsSelected(int x1,int y1,int x2,int y2)
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

string Rectangle::GetName()
{
	return this->name;
}

void Rectangle::Afficher()
{
	cout << "R " << name << " " << coorX1 << " " << coorY1 << " " 
	<< coorX2 << " "<< coorY2 << endl;	
}

string Rectangle::Sauvegarder()
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
	
	string saveLog= "R " + this->name + " " + scoorX1 + " " + scoorY1 + " "
	+ scoorX2 + " " + scoorY2;
	
	return saveLog;
}

void Rectangle::Deplacer (int dX, int dY)
{
	this->coorX1+=dX;
	this->coorX2+=dX;
	
	this->coorY1+=dY;
	this->coorY2+=dY;
}
Forme* Rectangle::Clone()
{
	Rectangle* tempRec = new Rectangle(this->name,this->coorX1,this->coorY1,this->coorX2,this->coorY2);
	return tempRec;
}
//-------------------------------------------- Constructeurs - destructeur

Rectangle::Rectangle(string name,int coorX1,int coorY1,int coorX2 ,int coorY2) : Forme(name)
{
	cout << "Constructor R"<<endl;
	this->coorX1 = coorX1;
	this->coorY1 = coorY1;
	this->coorX2 = coorX2;
	this->coorY2 = coorY2;
}
Rectangle::Rectangle(const Rectangle &unRectangle) : Forme(unRectangle)
{
	cout << "Cpy R"<<endl;
	this->coorX1 = unRectangle.coorX1;
	this->coorY1 = unRectangle.coorY1;
	this->coorX2 = unRectangle.coorX2;
	this->coorY2 = unRectangle.coorY2;
}
Rectangle::~Rectangle(){ cout<<"Dest R"<<endl;}
 
//------------------------------------------------------------------ PRIVE

	

//----------------------------------------------------- Méthodes protégées

