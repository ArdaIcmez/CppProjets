/*************************************************************************
 main.cpp - Programme Principal
 -------------------
 d�but                : 14 Janvier 2015
 copyright            : (C) 2014 Arda ICMEZs
 e-mail               : arda.icmez@insa-lyon.fr
 *************************************************************************/

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#include "main.h"
#include "Forme.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "PolyLigne.h"

int main(int argc, char** argv)

{

	string input;

	// Lecture de la chaine d'entr�e fournie par l'utilisateur

	//Boucle de fonctionnement du programme
	do {

		getline(cin, input);
		vector<string> parsedInput = Parse(input);

		InputRead(parsedInput, false);

		cout << "Size listeObjets : "<< listeObjets.size()<<endl;
		cout << "Size commandeStockes : "<< commandesStockes.size()<<endl;
		cout << "Size de listeRecovery : "<<listeRecovery.size()<<endl;


		if (commandesStockes.size() > 20 ) {
			if(commandesStockes.front()[0] == "DELETE")
			{
				for (unsigned int i = 1; i < commandesStockes.front().size(); i++) {
					Delete((commandesStockes.front())[i]);
				}
				/*if(commandesStockes.front().size()<=2)
				{
					string cle = (commandesStockes.front())[1];
					mapRecover::iterator iter = listeRecovery.find(cle);
					mapSelecRecover::iterator iterSel = listeRecSel.find(cle);
					if(iter != listeRecovery.end())
					{
						delete iter->second;
						listeRecovery.erase(iter);
					}
					else if(iterSel != listeRecSel.end())
					{
						// a faire
					}
				}
				else
				{

				}*/
			}
			commandesStockes.pop_front();
		}

	} while (input != "EXIT");
}

void InputRead(vector<string> parsedInput, bool inputByLoad) {

	string command = parsedInput[0];

	if (command == "C") {
		undoStockes.clear();
		if (parsedInput.size() == 5) {
			string name = parsedInput[1];

			if (AlreadyExists(name) == true) {
				cout << "ERR" << endl;
			}

			else {

				string X1string = parsedInput[2];
				int X1;
				istringstream(X1string) >> X1;

				string Y1string = parsedInput[3];
				int Y1;
				istringstream(Y1string) >> Y1;

				string rayonstring = parsedInput[4];
				int rayon;
				istringstream(rayonstring) >> rayon;

				listeObjets.insert(
						make_pair(name, new Circle(name, X1, Y1, rayon)));

				if (!inputByLoad) {
					cout << "OK" << endl;
					commandesStockes.push_back(parsedInput);
				}
			}
		}

		else {
			cout << "ERR" << endl;
		}
	}

	else if (command == "R") // RECTANGLE

			{
		undoStockes.clear();
		if (parsedInput.size() == 6) {
			string name = parsedInput[1];

			if (AlreadyExists(name) == true) {
				cout << "ERR" << endl;
			}

			else {
				string X1string = parsedInput[2];
				int X1;
				istringstream(X1string) >> X1;

				string Y1string = parsedInput[3];
				int Y1;
				istringstream(Y1string) >> Y1;

				string X2string = parsedInput[4];
				int X2;
				istringstream(X2string) >> X2;

				string Y2string = parsedInput[5];
				int Y2;
				istringstream(Y2string) >> Y2;

				listeObjets.insert(
						make_pair(name, new Rectangle(name, X1, Y1, X2, Y2)));

				if (!inputByLoad) {
					cout << "OK" << endl;
					commandesStockes.push_back(parsedInput);
				}
			}
		}

		else {
			cout << "ERR" << endl;

		}
	}

	else if (command == "L") // LIGNE
			{
		undoStockes.clear();
		if (parsedInput.size() == 6) {

			string name = parsedInput[1];

			if (AlreadyExists(name) == true) {
				cout << "ERR" << endl;
			}

			else {

				string X1string = parsedInput[2];
				int X1;
				istringstream(X1string) >> X1;

				string Y1string = parsedInput[3];
				int Y1;
				istringstream(Y1string) >> Y1;

				string X2string = parsedInput[4];
				int X2;
				istringstream(X2string) >> X2;

				string Y2string = parsedInput[5];
				int Y2;
				istringstream(Y2string) >> Y2;

				listeObjets.insert(
						make_pair(name, new Ligne(name, X1, Y1, X2, Y2)));

				if (!inputByLoad) {
					cout << "OK" << endl;
					commandesStockes.push_back(parsedInput);
				}
			}
		} else {
			cout << "ERR" << endl;
		}
	}

	else if (command == "PL") // POLY-LIGNE
			{
		undoStockes.clear();
		if (parsedInput.size() % 2 == 0 && parsedInput.size() > 5) {
			string name = parsedInput[1];

			if (AlreadyExists(name) == true) {
				cout << "ERR" << endl;
			}

			else {

				vector<pair<int, int> > points;

				for (unsigned int i = 2; i < parsedInput.size(); i += 2) {
					string Xstring = parsedInput[i];
					int X;
					istringstream(Xstring) >> X;

					string Y1string = parsedInput[i + 1];
					int Y;
					istringstream(Y1string) >> Y;

					pair<int, int> point(X, Y);
					points.push_back(point);

				}

				listeObjets.insert(
						make_pair(name, new PolyLigne(name, points)));

				if (!inputByLoad) {
					cout << "OK" << endl;
					commandesStockes.push_back(parsedInput);

				}

			}
		} else {
			cout << "ERR" << endl;

		}

	}

	else if (command == "S") // SELECTION
			{
		undoStockes.clear();
		if (parsedInput.size() == 6)

		{

			string name = parsedInput[1];
			if (AlreadyExists(name) == true) {
				cout << "ERR" << endl;
			}

			else {
				string X1string = parsedInput[2];
				int X1;
				istringstream(X1string) >> X1;

				string Y1string = parsedInput[3];
				int Y1;
				istringstream(Y1string) >> Y1;

				string X2string = parsedInput[4];
				int X2;
				istringstream(X2string) >> X2;

				string Y2string = parsedInput[5];
				int Y2;
				istringstream(Y2string) >> Y2;

				MakeSelection(name, X1, Y1, X2, Y2);

				cout << "OK" << endl;
			}
		} else {
			cout << "ERR" << endl;
		}

	}

	else if (command == "DELETE") // SUPPRESSION
			{
		undoStockes.clear();
		bool allExist = true;
		for (unsigned int i = 1; i < parsedInput.size(); i++) {

			if (AlreadyExists(parsedInput[i]) == false) {
				cout << "ERR" << endl;
				allExist = false;
				break;
			}
		}
		if (allExist == true) { // DELETE dedans la LOAD d'un objet qui n', �a marche ou pas?
			cout << "OK" << endl;
			if(!inputByLoad)
			{
			commandesStockes.push_back(parsedInput);
			}
			for (unsigned int i = 1; i < parsedInput.size(); i++) {
				Delete(parsedInput[i]);
			}
		}

	}

	else if (command == "MOVE") // DEPLACEMENT
			{
		undoStockes.clear();
		if (parsedInput.size() == 4) {
			string name = parsedInput[1];
			int dX,dY;
			string dXstring = parsedInput[2];
			string dYstring = parsedInput[3];
			istringstream(dXstring) >> dX;
			istringstream(dYstring) >> dY;

			Move(name, dX, dY);
			if(!inputByLoad)
			{
			commandesStockes.push_back(parsedInput);
			}
		}

		else {
			cout << "ERR" << endl;
		}
	}

	else if (command == "LIST") // ENUMERATION
			{
		undoStockes.clear();
		List();
	}

	else if (command == "UNDO")
	{
		if(!commandesStockes.empty())
		{
		Undo();
		}
		}

	else if (command == "REDO") {
		if(!undoStockes.empty())
		{
			Redo();
		}
	}

	else if (command == "LOAD") {
		undoStockes.clear();
		string sfileName = parsedInput[1];
		ifstream fileName(sfileName.c_str());

		Load(fileName);
		commandesStockes.push_back(parsedInput);
	}

	else if (command == "SAVE") {
		undoStockes.clear();
		string sfileName = parsedInput[1];
		ofstream fileName(sfileName.c_str());
		Save(fileName);

		fileName.close();
	}

	else if (command == "CLEAR") {
		commandesStockes.push_back(parsedInput);
		undoStockes.clear();
		Clear();
	}

	else if (command == "EXIT")

	{

	}

	else {
		cout << "ERR" << endl;
	}
}
vector<string> Parse(string input) {
	vector<string> parsedInput;
	istringstream iss(input);

	while (iss.good()) {
		string mot;
		iss >> mot;
		parsedInput.push_back(mot);
	}

	return parsedInput;
}

void Delete(string toDelete)
// Algorithme : Supprime un �l�ment � partir d'un nom.
		{
	iterObjet = listeObjets.find(toDelete);

	iterSelect = listeSelection.find(toDelete);

	if (iterObjet != listeObjets.end()) {
		for(iterSelect=listeSelection.begin() ; iterSelect!=listeSelection.end() ; ++iterSelect)
			 {
					 for (unsigned i=0;i<iterSelect->second.size();i++)
						{
						 if(iterSelect->second[i]==iterObjet->first)
						 {
							(iterSelect->second).erase((iterSelect->second).begin() + i);
							break;
						 }
						}
			}
		Forme* recoveryClone = (iterObjet->second)->Clone();// CEST PAS COMPLET
		string nameClone = iterObjet->first;
		listeRecovery.insert(make_pair(nameClone,recoveryClone));

		delete iterObjet->second;
		listeObjets.erase(iterObjet);
	}

	else if (iterSelect != listeSelection.end()) {
		innerMap tempMap;
		for (unsigned int j=0; j<iterSelect->second.size(); j++)
		{
			iterObjet=listeObjets.find(iterSelect->second[j]);
			if (iterObjet!=listeObjets.end())
			{
				for(iterSelect2=listeSelection.begin() ; iterSelect2!=listeSelection.end() ; ++iterSelect2)
				{
					for (unsigned i=0;i<iterSelect2->second.size();i++)
					{
						if(iterSelect2->second[i]==iterObjet->first)
						{
							(iterSelect2->second).erase((iterSelect2->second).begin() + i);
							break;
						}
					}
				}
				Forme* recoveryClone = (iterObjet->second)->Clone();// CEST PAS COMPLET
				string nameClone = iterObjet->first;
				tempMap.insert(make_pair(nameClone,recoveryClone));
				delete iterObjet->second;
				listeObjets.erase(iterObjet);
				j--;
			}
		}
		listeRecSel.insert(make_pair(toDelete,tempMap));
		listeSelection.erase(iterSelect);
	}
}
void DeleteRecovery(string toDelete)
		{
	iterObjet = listeObjets.find(toDelete);

	iterSelect = listeSelection.find(toDelete);

	if (iterObjet != listeObjets.end()) {
		for(iterSelect=listeSelection.begin() ; iterSelect!=listeSelection.end() ; ++iterSelect)
			 {
					 for (unsigned i=0;i<iterSelect->second.size();i++)
						{
						 if(iterSelect->second[i]==iterObjet->first)
						 {
							(iterSelect->second).erase((iterSelect->second).begin() + i);
							break;
						 }
						}
			}
		Forme* recoveryClone = (iterObjet->second)->Clone();// CEST PAS COMPLET
		string nameClone = iterObjet->first;
		listeRecovery.insert(make_pair(nameClone,recoveryClone));

		delete iterObjet->second;
		listeObjets.erase(iterObjet);
	}

	else if (iterSelect != listeSelection.end()) {
		innerMap tempMap;
		for (unsigned int j=0; j<iterSelect->second.size(); j++)
		{
			iterObjet=listeObjets.find(iterSelect->second[j]);
			if (iterObjet!=listeObjets.end())
			{
				for(iterSelect2=listeSelection.begin() ; iterSelect2!=listeSelection.end() ; ++iterSelect2)
				{
					for (unsigned i=0;i<iterSelect2->second.size();i++)
					{
						if(iterSelect2->second[i]==iterObjet->first)
						{
							(iterSelect2->second).erase((iterSelect2->second).begin() + i);
							break;
						}
					}
				}
				Forme* recoveryClone = (iterObjet->second)->Clone();// CEST PAS COMPLET
				string nameClone = iterObjet->first;
				tempMap.insert(make_pair(nameClone,recoveryClone));
				delete iterObjet->second;
				listeObjets.erase(iterObjet);
				j--;
			}
		}
		listeRecSel.insert(make_pair(toDelete,tempMap));
		listeSelection.erase(iterSelect);
	}
}
void Undo() {
	cout << "Undo marche"<<endl;
	vector<string> parsedCommande =commandesStockes.back();
	undoStockes.push_back(parsedCommande);
	string derniereCommande = parsedCommande[0];
	if(derniereCommande == "MOVE")
	{
		int dX,dY;
		string dXstring = parsedCommande[2];
		string dYstring = parsedCommande[3];
		istringstream(dXstring) >> dX;
		istringstream(dYstring) >> dY;
		dX=-dX;dY=-dY;
		Move(parsedCommande[1],dX,dY);
	}
	if(derniereCommande == "DELETE")
			{
		mapForme::iterator iterRec = listeRecovery.find(parsedCommande[1]);
		mapSelecRecover::iterator iterRecSel = listeRecSel.find(parsedCommande[1]);
		if(iterRec != listeRecovery.end())
		{
			mapForme::iterator iterRec = listeRecovery.upper_bound(parsedCommande[1]);
			iterRec--;
			cout << "Undo de Delete: ";
			iterRec->second->Afficher();
			listeObjets.insert(make_pair(iterRec->first,iterRec->second));
			listeRecovery.erase(iterRec);
		}
		else if(iterRecSel != listeRecSel.end())
		{

		}
			}
	if(derniereCommande == "LOAD")
			{
		//a faire c'est comme delete de selection de undo
			}
	if(derniereCommande == "CLEAR")
			{
		//a faire
			}
	if(derniereCommande == "C")
			{
		Delete(parsedCommande[1]);// recovery deki son eleman� bulup sil
		mapRecover::iterator it = listeRecovery.upper_bound(parsedCommande[1]);
		it--;
		delete it->second;
		listeRecovery.erase(it);
			}
	if(derniereCommande == "L")
			{
		Delete(parsedCommande[1]);
		mapRecover::iterator it = listeRecovery.upper_bound(parsedCommande[1]);
		it--;
		delete it->second;
		listeRecovery.erase(it);
			}
	if(derniereCommande == "R")
			{
		Delete(parsedCommande[1]);
		mapRecover::iterator it = listeRecovery.upper_bound(parsedCommande[1]);
		it--;
		delete it->second;
		listeRecovery.erase(it);
			}
	if(derniereCommande == "PL")
			{
		Delete(parsedCommande[1]);
		mapRecover::iterator it = listeRecovery.upper_bound(parsedCommande[1]);
		it--;
		delete it->second;
		listeRecovery.erase(it);
			}
	commandesStockes.pop_back();
}

void Redo() {
	vector<string> parsedCommande =undoStockes.back();
	string derniereCommande = parsedCommande[0];
	InputRead(parsedCommande,true); // Mieux que le reste, on evite de re-stocker les commandes dans commandesStockes
	/*if(derniereCommande == "MOVE")
	{
		int dX,dY;
		string dXstring = parsedCommande[2];
		string dYstring = parsedCommande[3];
		istringstream(dXstring) >> dX;
		istringstream(dYstring) >> dY;
		Move(parsedCommande[1],dX,dY);
	}
	if(derniereCommande == "DELETE")
			{
		Delete(parsedCommande[1]);
			}
	if(derniereCommande == "LOAD")
			{
		string sfileName = parsedCommande[1];
		ifstream fileName(sfileName.c_str());
		Load(fileName);
			}
	if(derniereCommande == "C")
			{
		string X1string = parsedCommande[2];
		int X1;
		istringstream(X1string) >> X1;

		string Y1string = parsedCommande[3];
		int Y1;
		istringstream(Y1string) >> Y1;

		string rayonstring = parsedCommande[4];
		int rayon;
		istringstream(rayonstring) >> rayon;

		listeObjets.insert(
				make_pair(parsedCommande[1], new Circle(parsedCommande[1], X1, Y1, rayon)));
			}
	if(derniereCommande == "L")
			{
		string X1string = parsedCommande[2];
		int X1;
		istringstream(X1string) >> X1;

		string Y1string = parsedCommande[3];
		int Y1;
		istringstream(Y1string) >> Y1;

		string X2string = parsedCommande[4];
		int X2;
		istringstream(X2string) >> X2;

		string Y2string = parsedCommande[5];
		int Y2;
		istringstream(Y2string) >> Y2;

		listeObjets.insert(
				make_pair(parsedCommande[1], new Ligne(parsedCommande[1], X1, Y1, X2, Y2)));
			}
	if(derniereCommande == "R")
			{
		string X1string = parsedCommande[2];
		int X1;
		istringstream(X1string) >> X1;

		string Y1string = parsedCommande[3];
		int Y1;
		istringstream(Y1string) >> Y1;

		string X2string = parsedCommande[4];
		int X2;
		istringstream(X2string) >> X2;

		string Y2string = parsedCommande[5];
		int Y2;
		istringstream(Y2string) >> Y2;

		listeObjets.insert(
				make_pair(parsedCommande[1], new Rectangle(parsedCommande[1], X1, Y1, X2, Y2)));
			}
	if(derniereCommande == "PL")
			{
		vector<pair<int, int> > points;

		for (unsigned int i = 2; i < parsedCommande.size(); i += 2) {
			string Xstring = parsedCommande[i];
			int X;
			istringstream(Xstring) >> X;

			string Y1string = parsedCommande[i + 1];
			int Y;
			istringstream(Y1string) >> Y;

			pair<int, int> point(X, Y);
			points.push_back(point);
			}
		listeObjets.insert(
								make_pair(parsedCommande[1], new PolyLigne(parsedCommande[1], points)));
		} */
	commandesStockes.push_back(parsedCommande);
	undoStockes.pop_back();
}
void List() {
	for (iterObjet = listeObjets.begin(); iterObjet != listeObjets.end();
			++iterObjet) {
		(iterObjet->second)->Afficher();
	}
}

void Clear() {
	for (iterObjet = listeObjets.begin(); iterObjet != listeObjets.end();
			++iterObjet) {
		listeObjets.erase(iterObjet);
	}
	cout << "OK" << endl;
}

void Move(string toMove, int dX, int dY) {
	undoStockes.clear();
	iterObjet = listeObjets.find(toMove);
	iterSelect = listeSelection.find(toMove);

	if (iterObjet != listeObjets.end()) {

		(iterObjet->second)->Deplacer(dX, dY);
		cout << "OK" << endl;
	}

	else {
		if (iterSelect != listeSelection.end()) {
			for (unsigned int i = 0; i < iterSelect->second.size(); i++) {
				iterObjet = listeObjets.find(iterSelect->second[i]);
				if (iterObjet != listeObjets.end()) {
					(iterObjet->second)->Deplacer(dX, dY);
				}
			}
			cout << "OK" << endl;
		} else {
			cout << "ERR" << endl;
		}
	}
}

void Save(ofstream & fileName) {
	if (fileName) {
		for (iterObjet = listeObjets.begin(); iterObjet != listeObjets.end();
				++iterObjet) {
			fileName << ((iterObjet->second)->Sauvegarder()) << endl;
			cout << "OK" << endl;
		}
	}

	else {
		cout << "ERR" << endl;
	}
}

void Load(ifstream & fileName) {

	if (fileName) {
		string line;

		while (getline(fileName, line)) // tant qu'on a pas tout lu, on lit la ligne suivante
		{
			vector<string> parsedLine = Parse(line);
			InputRead(parsedLine, true);

		}

		cout << "OK" << endl;
	}

	else {
		cout << "ERR" << endl;

	}

}

void MakeSelection(string name, int X1, int Y1, int X2, int Y2) {

	vector<string> selectedShapes;
	string shape;

	for (iterObjet = listeObjets.begin(); iterObjet != listeObjets.end();
			++iterObjet) {
		if ((iterObjet->second)->IsSelected(X1, Y1, X2, Y2) == true) {
			selectedShapes.push_back((iterObjet->second)->GetName());
		}
	}
	listeSelection.insert(make_pair(name, selectedShapes));
}

bool AlreadyExists(string name) {
	iterObjet = listeObjets.find(name);
	iterSelect = listeSelection.find(name);

	if (iterObjet != listeObjets.end() || iterSelect != listeSelection.end()) {
		return true;
	} else {
		return false;
	}
}

