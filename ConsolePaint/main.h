/*************************************************************************
                           main  -  Module principal de l'application
                           * analyse de logs Apache 
                             -------------------
    début                : Novembre 2014
    copyright            : (C) 2014 par Arda Icmez & Cedric Boscher
    e-mail               : arda.icmez@insa-lyon.fr & cedric.boscher@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <main> (fichier main.h) ---------
#if ! defined ( MAIN_H )
#define MAIN_H

#include <deque>
#include <map>
#include <string>
#include <fstream>
#include "Forme.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "PolyLigne.h"
using namespace std;



int main (int argc, char** argv);
// Mode d'emploi :
//
// Contrat :
//

vector < string > Parse (string input);
void InputRead (vector < string > input, bool inputByLoad);

void Delete(string toDelete);

void DeleteRecovery(string toDelete);

void Undo();

void Redo();

void List();

void Clear();

void Move(string toMove, int dX, int dY);

void Save(ofstream & fileName);

void Load(ifstream & fileName);

void MakeSelection(string name, int X1, int Y1, int X2, int Y2);

bool AlreadyExists(string name);

Forme* Clone(const Forme* original);

typedef deque<vector<string> > deqCommandes;
typedef map<string,Forme*> mapForme;
typedef multimap<string,Forme*> mapRecover;
typedef map<string,vector< string > > mapSelect;
typedef map<string,Forme*> innerMap;
typedef multimap<string,innerMap > mapSelecRecover;

mapForme listeObjets;
mapForme::iterator iterObjet;

mapRecover listeRecovery;
mapSelecRecover listeRecSel;

mapSelect listeSelection;
mapSelect::iterator iterSelect;
mapSelect::iterator iterSelect2;

deqCommandes commandesStockes;
deqCommandes undoStockes;
deqCommandes::iterator iterStockage;

#endif // MAIN_H

