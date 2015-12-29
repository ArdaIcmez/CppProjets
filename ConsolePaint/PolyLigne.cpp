
/*************************************************************************
                    Forme.cpp - Definition de la classe Forme
                             -------------------
    début                : 14 Janvier 2015
    copyright            : (C) 2014 Arda Içmez et Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr
                           cedric.boscher@insa-lyon.fr
*************************************************************************/

//-------- Réalisation de la classe	PolyLigne (PolyLigne.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "PolyLigne.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PolyLigne::IsSelected(int x1,int y1,int x2,int y2)
{
	bool selected=true;
	
	for (unsigned int i=0; i< this->points.size(); i++)
	{	
		int X=points[i].first;
		int Y=points[i].second;
		if (SelectedPoint(X,Y,x1,y1,x2,y2)==false)
		{
			selected=false;
			break;
			
		}
		
	}
	
	
	return selected;
}

string PolyLigne::GetName()
{
	return name;
}

void PolyLigne::Afficher()

{	cout << "PL " << name << " ";
	 
	for (unsigned int i=0; i< this->points.size(); i++)
	{	
		cout << points[i].first<< " ";
		cout << points[i].second << " ";
	}
	
	cout << endl;		
}

string PolyLigne::Sauvegarder()

{	
	string saveLog = "PL " + this->name + " ";
	 
	for (unsigned int i=0; i< this->points.size(); i++)
	{	
		stringstream ss;
		
		cout << points[i].first<< " ";
		cout << points[i].second << " ";
		
		ss <<  points[i].first;
		string scoorX=ss.str();
		ss.str("");
		ss.clear();
	
		ss << points[i].second;
		string scoorY=ss.str();
		ss.str("");
		ss.clear();
		
		saveLog=saveLog + scoorX + " " + scoorY + " ";
	}
	
	return saveLog;
}


void PolyLigne::Deplacer(int dX, int dY)
{
	
for (unsigned int i=0; i< this->points.size(); i++)
	{
		points[i].first+=dX;
		points[i].second+=dY;
	}		
}
Forme* PolyLigne::Clone()
{
	PolyLigne* tempPl = new PolyLigne(this->name,this->points);
	cout <<"element cree : ";
	tempPl->Afficher();
	return tempPl;
}
//-------------------------------------------- Constructeurs - destructeur

PolyLigne::PolyLigne(string name,vector<pair<int,int> > points) : Forme(name)
{
	cout << "Constructor PL"<<endl;
	this->points=points;
}
PolyLigne::PolyLigne(const PolyLigne &unPolyLigne) : Forme(unPolyLigne)
{
	this->points=unPolyLigne.points;
	cout << "Cpy PL"<<endl;
}
PolyLigne::~PolyLigne()
{
	cout<<"Dest PL"<<endl;
}
 
//------------------------------------------------------------------ PRIVE

	

//----------------------------------------------------- Méthodes protégées
