
/*************************************************************************
                    Forme.cpp - Definition de la classe Forme
                             -------------------
    début                : 14 Janvier 2015
    copyright            : (C) 2014 Arda Içmez et Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr
                           cedric.boscher@insa-lyon.fr
*************************************************************************/

//-------- Réalisation de la classe	Circle (Circle.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Circle.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Circle::IsSelected(int x1,int y1,int x2,int y2)
{
	if ( SelectedPoint(this->coorX+this->rayon, this-> coorY, x1, y1, x2, y2)== true
	&& SelectedPoint(this->coorX-this->rayon, this-> coorY, x1, y1, x2, y2)== true
	&& SelectedPoint(this->coorX, this-> coorY + this->rayon, x1, y1, x2, y2)==true
	&& SelectedPoint(this->coorX, this-> coorY - this->rayon, x1, y1, x2, y2)==true
	)
	{
		return true;
	}
	
	else
	{	
		return false;
	}
}


string Circle::GetName()
{
	return name;
}

void Circle::Afficher()
{
	cout << "C " << this-> name << " " <<  this->coorX << " "<< this->coorY << " " << this->rayon<< endl;
}

string Circle::Sauvegarder()
{
	
	stringstream ss;
	
	ss << this->coorX;
	string scoorX=ss.str();
	ss.str("");
	ss.clear();
	
	ss << this->coorY;
	string scoorY=ss.str();
	ss.str("");
	ss.clear();
	
	ss << this->rayon;
	string srayon=ss.str();
	ss.str("");
	ss.clear();
	
	string saveLog ="C " + this->name + " " + scoorX + " " + scoorY + " " + srayon;
	
	return saveLog;
}
void Circle::Deplacer (int dX, int dY)
{
		coorX+=dX;
		coorY+=dY;
}
Forme* Circle::Clone()
{
	Circle* tempCircle = new Circle(this->name,this->coorX,this->coorY,this->rayon);
	return tempCircle;
}
//-------------------------------------------- Constructeurs - destructeur

Circle::Circle(string name,int coorX,int coorY, int rayon) : Forme(name)
{
	cout << "Constructor C"<<endl;
	this->coorX = coorX;
	this->coorY = coorY;
	this->rayon = rayon;
}

Circle::Circle(const Circle &unCircle) : Forme(unCircle)
{
	cout << "Cpy C"<<endl;
	this->coorX = unCircle.coorX;
	this->coorY = unCircle.coorY;
	this->rayon = unCircle.rayon;
}

 Circle::~Circle()
 {
	 cout<<"Dest C"<<endl;
 }
 
//------------------------------------------------------------------ PRIVE

	

//----------------------------------------------------- Méthodes protégées
