/*************************************************************************
                           main  -  Module principal de l'application
                           * analyse de logs Apache 
                             -------------------
    début                : Novembre 2014
    copyright            : (C) 2014 par Arda Icmez & Nicolas Nadisic
    e-mail               : arda.icmez@insa-lyon.fr & nicolas.nadisic@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <main> (fichier main.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <sstream>
//------------------------------------------------------ Include personnel


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
string input;
bool xEnable=false,tEnable=false,gEnable=false,stockageEnable=false;
bool stockEnableX=false;
string heureVoulue;
typedef map<string,int> innerMap;
typedef map<string,innerMap > mapGraphe;
typedef map<string,string> listeUrl;
typedef multimap<int,string> sortUrls;
//------------------------------------------------------ Fonctions privées
int main (int argc, char** argv)
// Mode d'emploi :
//
// Contrat :
// Les paramètres d'éxécution du programme peuvent être :
// -x
// -t suivi d'un entier entre 0 et 23
// -g suivi du nom du fichier .dot à générer
// Ces 3 paramètres peuvent être combinés, dans un ordre quelconque.
// On peut n'utiliser aucun de ses paramètres.
// Le dernier paramètre doit toujours être le nom du fichier .log
// contenant les logs à analyser. ce paramètre est obligatoire.
//
// Algorithme :
//
{
	mapGraphe lesUrlsGraphe; // Pour les fleches entre les noeuds
    listeUrl laListeUrls; // Pour les noeuds sur grapheviz

    string nomFichier;

    innerMap stockageHits; // Pour mode normale <map>
    sortUrls sortStockage; // Pour mode normale, triage <multimap>


    ////////////////////////////////////////////////// TEST PARAMS
    if(argc==1)
    {
		cout << "Erreur : aucun fichier indiqué." << endl;
	}
	else
	{
		if(argc==2)
		{
			//A EFFACERcout << "Mode sans option." << endl;
			input = argv[1];
			// A EFFACER cout << "Fichier à analyser : " << input <<endl;
		}
		else
		{
			//On parcoure les arguments pour savoir quelles options appliquer
			for (int i=1; i<argc; i=i+1)
			{
				if( strcmp(argv[i],"-t") == 0 )
				{
					// A EFFACER cout << "Mode temps : " << argv[i+1] << "h" << endl;
					tEnable = true;
					heureVoulue = argv[i+1];
				}
				if( strcmp(argv[i],"-x") == 0 )
				{
					//A EFFACER cout << "Mode limité" << endl;
					xEnable = true;
				}
				if( strcmp(argv[i],"-g") == 0 )
				{
				// A EFFACER	cout << "Mode dot : " << argv[i+1] << endl;
					nomFichier = argv[i+1];
					gEnable = true;
				}
			}//fin de la boucle for
			input = argv[argc-1];
			//A EFFACER cout << "Fichier à analyser : " << input <<endl;
		}
	}
    ////////////////////////////////////////////////// TEST PARAMS
    
    
	//Création du flux correspondant à l'input
	ifstream source(input.c_str(), ios::in);

	//Test sur le fichier source
	if(source) //Si ouverture réussie
    {
     //A EFFACER cout << "Fichier ouvert avec succès." << endl;
    }
	else 
    {
		//A EFFACER cout << "Erreur à l'ouverture du fichier. Vérifiez le nom et l'emplacement." << endl;
		return (-1);
    }
    
    
	//Pour rester générique, on lit tous les éléments de chaque ligne
	
	//string permettant d'éliminer les caractères indésirables (guillemets ...)
	string tampon;
	
	string ip;
	string userLogName;
	string authUser;
	string date;
	string gmt;
	string typeAction;
	string url;
	string protocole;
	string codeRetour;
	string tailleReponse;
	string referer;
	string idNavigateur;
	
	while(source)
	{
		getline(source,ip,' ');
		if (ip =="\n"){break;} //Détecter la derniere ligne de fichier
		getline(source,userLogName,' ');
		getline(source,authUser,' ');
		getline(source,tampon,'[');
		getline(source,date,' ');
		getline(source,gmt,']');
		getline(source,tampon,'"');
		getline(source,typeAction,' ');
		getline(source,url,' ');
		getline(source,protocole,'"');
		getline(source,tampon,' ');
		getline(source,codeRetour,' ');
		getline(source,tailleReponse,' ');
		getline(source,tampon,'"');
		getline(source,referer,'"');
		getline(source,tampon,'"');
		getline(source,idNavigateur,'"');
	
		if(xEnable)
		{
			string curString = url; 
			int position = 0;
			position = curString.rfind(".");
			curString = curString.substr(position+1);
			if( !curString.compare("html") || !curString.compare("php") ) // Juste prendre html ou php
			{
				if(tEnable)
				{
					stockEnableX = true;
				}
				else
				{	
					stockageEnable = true;
				}
			}
		}
		if(tEnable)
		{
			string curString = date; 
			int position = 0;
			position = curString.find(":");
			curString = curString.substr(position+1,2);
			if(!curString.compare(heureVoulue))
			{
				if(xEnable)
				{
					if(stockEnableX)
					{
						stockageEnable=true;
					}
				}
				else
				{	
					stockageEnable = true;
				}
			}
		}
		if((stockageEnable || !(tEnable||xEnable)) && !codeRetour.compare("200"))
		{
			if(gEnable)
			{
				laListeUrls.insert(make_pair(url,url)); // Pour cree les noeuds
				laListeUrls.insert(make_pair(referer,referer)); // Pour cree les noeuds

				if ( lesUrlsGraphe.find(url) == lesUrlsGraphe.end()) // l'url existe pas
				{
					lesUrlsGraphe.insert (make_pair (url, innerMap ()));//creation de noeud
					lesUrlsGraphe[url].insert(make_pair (referer,1)); // insertion de innermap
				} 
				else // l'url deja existe
				{
					if ( lesUrlsGraphe[url].find(referer) == lesUrlsGraphe[url].end()) // innerMap existe pas
					{
						lesUrlsGraphe[url].insert(make_pair (referer,1));
					} 
					else //innerMap existe, augmentation de valeur
					{
						lesUrlsGraphe[url][referer]++;					
					}					
				}
			}
			// Stockage normale pour les hits

			if ( stockageHits.find(url) == stockageHits.end()) // l'url existe pas
			{
				stockageHits.insert(make_pair(url,1));
			}
			else // l'url deja existe, augmentation de valeur
			{
				stockageHits[url]++;
			}
		}
		stockageEnable = false;
		stockEnableX = false;
	}

	// Copy map vers multimap pour la trier.

    map<string, int>::iterator iter;
    for (iter = stockageHits.begin(); iter!=stockageHits.end(); ++iter)
        sortStockage.insert(make_pair(iter->second, iter->first)); // values ont devenus cles et vice versa


	if(gEnable)
	{

	  //Création du flux de sortie
		ofstream fichierDot(nomFichier.c_str(), ios::out | ios::trunc);
		fichierDot<<"digraph {"<<endl;

		//Creation des noeuds sur .dot
		listeUrl::iterator iterNoeud;
		for (iterNoeud = laListeUrls.begin(); iterNoeud!=laListeUrls.end(); ++iterNoeud)
		{
			fichierDot<<"\""<<iterNoeud->first<<"\";"<<endl;
		}

		for (mapGraphe::iterator i = lesUrlsGraphe.begin(), iend = lesUrlsGraphe.end(); i != iend; ++i)
		{
		    innerMap &innerListe = i->second;
		    for (innerMap::iterator j = innerListe.begin(), jend = innerListe.end(); j != jend; ++j)
		    {
		    	fichierDot<<"\""<<j->first<<"\""<<" -> "<<"\""<<i->first<<"\" [label=\""<<j->second<<"\"];"<<endl;
		    }
		}
		fichierDot<<"}";
		cout<<"Dot-file "<< nomFichier <<" generated"<<endl;
	}
	if(tEnable)
	{
		stringstream convert(heureVoulue);
		int afficHeur;
		if (!(convert >> afficHeur)){afficHeur = 0; } // Convert string vers integer

		cout << "Warning : only hits between "<<afficHeur<<"h and "<< afficHeur+1<<"h have been taken into account"<<endl;
	}
	int controle=1; // Pour controller top dix

    multimap<int, string>::reverse_iterator iter2; // reverse iterator car multimap est ordre croissant
    for (iter2 = sortStockage.rbegin(); iter2!=sortStockage.rend(); ++iter2)
    {
    	if(controle>10)
    	{
    		break;
    	}
        cout<< iter2->second << " (" << iter2->first <<" hits)"<< endl;
        controle++;
    }

    
} //----- fin de main





//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

