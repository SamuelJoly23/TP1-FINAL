/*
* @fichier: main.cpp
* @auteurs:
* @date:
* @description: Tests
*/

#include <iostream>
#include <sstream>
#include <time.h>
#include <clocale>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>
#include "Creature.h"
#include "Dresseur.h"
#include "PolyLand.h"
#include "Pouvoir.h"
#include "AsciiArt.h"

using namespace std;

const int DRESSEUR = 0, CREATURE = 1;
const int NB_DRESSEUR = 3, NB_CREATURE = 5;
const inline string ROUGE = "\033[1;91m", MAUVE = "\033[1;95m", BLEU = "\033[1;96m", VERT ="\u001b[32;1m", FIN = "\033[0m";
const string LIGNE = "-------------------------------------------------------------------";

void initialisationPolyland(PolyLand& polyland, ifstream &fichier) {
	
	// Verification
	if (!fichier.is_open()) {
		cout << "Error opening file";
		exit(1);
	}

	// Dresseur
	string nomDresseur;

	// Creature
	string nomCreature;
	string attaque;
	string defense;
	string pointDeVie;
	string energie;

	// Pouvoir
	string nomPouvoir;
	string nombreDeDegat;
	string manaNecessaire;

	string type;
	while (!fichier.eof()) {
		
		getline(fichier, type, '\t');
		
		switch (stoi(type)) {
		case DRESSEUR:
			getline(fichier, nomDresseur);
			//   if est pour lire le fichier sous Mac
			//  et retire le \r à la fin de la ligne
			if (nomDresseur[nomDresseur.size() - 1] == '\r')
    			nomDresseur.resize(nomDresseur.size() - 1);
			if (polyland.ajouterDresseur(new Dresseur(nomDresseur)))
			     cout << "ajout dresseur"<< endl;
			break;

		case CREATURE:
			getline(fichier, nomCreature, '\t');
			getline(fichier, attaque, '\t');
			getline(fichier, defense, '\t');
			getline(fichier, pointDeVie, '\t');
			getline(fichier, energie, '\t');
			getline(fichier, nomPouvoir, '\t');
			getline(fichier, nombreDeDegat, '\t');
			getline(fichier, manaNecessaire);
			//   if est pour lire le fichier sous Mac
			//  et retire le \r à la fin de la ligne
			if (manaNecessaire[manaNecessaire.size() - 1] == '\r')
    			manaNecessaire.resize(manaNecessaire.size() - 1);
				
			if(polyland.ajouterCreature(Creature(nomCreature, stoi(attaque), stoi(defense), stoi(pointDeVie), stoi(energie), 
				Pouvoir(nomPouvoir, stoi(nombreDeDegat), stoi(manaNecessaire)))))
				  cout << "ajout Creature"<< endl;
			break;

		default:
			break;
		}
	}
}

int main() {
	srand(unsigned(time(nullptr)));
	setlocale(LC_ALL, "");

	vector<bool> tests;

	ifstream fichier("fichier.txt");
	AsciiArt art;

	PolyLand polyland;
	Dresseur vous("Vous");
	if (polyland.ajouterDresseur(&vous))
	       cout << "ajout dresseur"<< endl;

	cout << BLEU << art.polyland() << FIN << endl;

	cout << MAUVE << LIGNE << "\n > Initialisation de Polyland\n" << LIGNE << FIN << endl;
	initialisationPolyland(polyland, fichier);

	/*---------------------------------------------------------------------------------------
	* Debut des TESTS
	----------------------------------------------------------------------------------------*/
	cout << endl << MAUVE << LIGNE << "\n > Debut des tests\n" << LIGNE << FIN << endl;

	// TEST 1
	if (true) {
		bool success = true;

		// Assignation de votre creature
		cout << MAUVE << "\n > Assignation de votre creature\n" << LIGNE << FIN << endl;
		cout << "Choix de la premiere creature" << endl;
		vous.ajouterCreature(*polyland.choisirCreature("Pikachu"));
		cout << "Vous etes chanceux voici un Pikachu rien que pour vous" << endl;

		// Assignation des creatures aux autres dresseurs
		if (polyland.choisirDresseur("Leon")->ajouterCreature(*polyland.choisirCreature("Charizard")))
		       cout << "ajout Creature"<<endl;
		if (polyland.choisirDresseur("Brock")->ajouterCreature(*polyland.choisirCreatureAleatoire()))
		 	cout << "ajout Creature"<<endl;
		if (polyland.choisirDresseur("May")->ajouterCreature(*polyland.choisirCreatureAleatoire()))
		      cout << "ajout Creature"<<endl;

		success &= (polyland.choisirDresseur("Leon")->obtenirCreatures()[0]->obtenirNom() == "Charizard") &&
			polyland.choisirDresseur("Brock")->obtenirNombreCreatures() == 1 &&
			polyland.choisirDresseur("Brock")->obtenirNombreCreatures() == 1;

		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}

	// TEST 2
	if (true) {
		bool success = true;

		// Affichage des infos
		cout << MAUVE << "\n > Affichage des infos de tous les dresseurs\n" << LIGNE << FIN << endl;
		polyland.infoDresseur("Leon");
		polyland.infoDresseur("Brock");
		polyland.infoDresseur("May");
		polyland.infoDresseur("Vous");

		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}

	// TEST 3
	if (true) {
		bool success = true;
		// Duel 1
		cout << MAUVE << " > 1er duel\n" << LIGNE << FIN << endl;
		cout << ROUGE << "Un Bulbasaur surgit" << FIN << endl;

		polyland.choisirCreature("Bulbasaur")->attaquer(*polyland.choisirCreature("Pikachu"));
		do {
			vous.obtenirCreatures()[0]->attaquer(*polyland.choisirCreature("Bulbasaur")); //************
		} while (polyland.choisirCreature("Bulbasaur")->obtenirPointDeVie() > 0);

		cout << "Vous avez battu un Bulbasaur, vous pouvez maintenant le capturer" << endl;

		if (polyland.attraperCreature(&vous, *polyland.choisirCreature("Bulbasaur"))) {
			cout << "Felicitation vous avez attrapé un Bulbasaur !" << endl;
			cout << VERT << endl << art.bulbasaur() << FIN << endl;
		}
		else {
			// Ne devrait pas s'afficher
			cout << "Bulbasaur s'est échappé" << endl;
			success = false;
		}
		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}
	
	// TEST 4
	if (true) {
		bool success = true;
		// Duel 2
		cout << MAUVE << "\n > 2nd duel\n" << LIGNE << FIN << endl;
		cout << ROUGE << "Leon vous defie a un combat!!" << endl;
		cout << "Un duel entre Pikachu et " << polyland.choisirDresseur("Leon")->obtenirCreatures()[0]->obtenirNom() << " est engagé" << FIN << endl;
		polyland.choisirDresseur("Leon")->obtenirCreatures()[0]->attaquer(*polyland.choisirCreature("Pikachu"));
		do {
			vous.obtenirCreatures()[0]->attaquer(*polyland.choisirDresseur("Leon")->obtenirCreatures()[0]);
		} while (polyland.choisirDresseur("Leon")->obtenirCreatures()[0]->obtenirPointDeVie() > 0);

		cout << "Vous avez battu un Charizard, vous pouvez maintenant le capturer" << endl;

		if (polyland.attraperCreature(&vous, *polyland.choisirCreature("Charizard"))) {
			cout << "Felicitation vous avez attrapé un Charizard !" << endl;
			cout << VERT << endl << art.charizard() << FIN << endl;
		}
		else {
			// Ne devrait pas s'afficher
			cout << "Charizard s'est échappé" << endl;
			success = false;
		}
		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}

	// TEST 5
	if (true) {
		bool success = true;
		cout << MAUVE << "\n > Leon quitte PolyLand\n" << LIGNE << FIN << endl;
		cout << ROUGE << "face a cette defaite, Leon decide de quitter PolyLand" << FIN << endl;
		success &= polyland.choisirDresseur("Leon") != nullptr;
		polyland.retirerDresseur("Leon");
		polyland.infoDresseur("Leon");
		success &= polyland.choisirDresseur("Leon") == nullptr;
		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}

	// TEST 6
	if (true) {
		bool success = true;

		// Affichage de vos infos
		cout << MAUVE << "\n > Affichage de vos infos\n" << LIGNE << FIN << endl;
		polyland.infoDresseur("Vous");

		tests.push_back(success);
	}
	else {
		tests.push_back(false);
	}
	
	cout << endl << MAUVE << LIGNE << "\n > Fin des tests\n" << LIGNE << FIN << endl;

	/*---------------------------------------------------------------------------------------
	* Fin des TESTS
	----------------------------------------------------------------------------------------*/
	std::vector<float> ponderationTests = { 2, 1, 2, 1, 1, 1};

	cout << "\033[1;91mLes tests 2 et 6 ne sont pas reellement testes par le programme!" << endl;
	cout << "Veuillez vous fier a l'affichage fournit dans l'enonce du tp \033[0m" << endl;
	cout << endl;

	// Affichage
	float totalPoints = 0;
	for (size_t i = 0; i < tests.size(); i++) {
		string output = "Test " + to_string(i + 1) + ": ";
		if (tests[i] == true) {
			output += "OK!";
			stringstream stream;
			stream << ponderationTests[i] << '/' << ponderationTests[i];
			cout << left << setw(15) << std::left << output
				<< stream.str() << endl;
			totalPoints += ponderationTests[i];
		}
		else {
			output += "ECHEC!";
			stringstream stream;
			stream << '0' << '/' << ponderationTests[i];
			std::cerr << std::left << std::setw(15) << output << "0/"
				<< ponderationTests[i] << endl;
		}
	}
	std::stringstream stream;
	stream << totalPoints << "/"
		<< accumulate(ponderationTests.begin(), ponderationTests.end(),
			0.0f);
	cout << VERT << left << setw(15) << "TOTAL: " << stream.str() << FIN << endl;
	
	return 0;
}