/*
* @fichier: Dresseur.cpp
* @auteurs:
* @date:
* @description: les dresseurs sont les etres capables d'attraper des creatures
*/

#include "Dresseur.h"

Dresseur::Dresseur() : nom_(""), creatures_(nullptr), nombreCreatures_(0), nombreCreaturesMax_(MAX_NOMBRE_CREATURES) {
	creatures_ = new Creature * [MAX_NOMBRE_CREATURES];
	for (int i = 0; i < MAX_NOMBRE_CREATURES; i++) {
		creatures_[i] = new Creature;
	}
}

Dresseur::Dresseur(const std::string& nom) : Dresseur() {
	nom_ = nom;
}

// destructeur
Dresseur::~Dresseur() {
	for (int i = 0; i < nombreCreatures_; i++) {
		delete creatures_[i];
		creatures_[i] = nullptr;
	}
}

// TODO: Getters
std::string Dresseur::obtenirNom() const {
	return nom_;
}

unsigned int Dresseur::obtenirNombreCreatures() const {
	return nombreCreatures_;
}

Creature** Dresseur::obtenirCreatures() const { //*****A revoir******
	
	//Creature* c = new Creature();
	//Creature** p = &c;
	//return p;
	return creatures_;
}

// TODO: Setters
void Dresseur::modifierNom(const std::string& nom) {
	nom_ = nom;
}

void Dresseur::modifierCreature(Creature** creatures) {
	creatures_ = creatures;
}



/*void Dresseur::modifierNombreCreaturesMax(unsigned int nombreCreaturesMax) { //**************AJOUT DE FONCTION************
	nombreCreaturesMax_ = nombreCreaturesMax;
}

void Dresseur::modifierNombreCreatures(unsigned int nombreCreatures) { //**************AJOUT DE FONCTION************
	nombreCreatures_ = nombreCreatures;
}*/

// TODO: ajouter creature dans creatures_
// *verifier que la creature n'est pas deja presente
// *verifier que nb creature < nombreCreaturesMax_
//	->	sinon doubler la taille de creatures_
bool Dresseur::ajouterCreature(const Creature& creature) { //**********************************
	
	bool Ajoute = true;
	for (unsigned int i = 0; i < nombreCreatures_; i++) {
		if (creatures_[i]->obtenirNom() == creature.obtenirNom()) {
			Ajoute = false;
		}
	}
	if (Ajoute == true) {
		if (nombreCreatures_ == nombreCreaturesMax_) {
			//modifierNombreCreaturesMax(nombreCreaturesMax_ * 2);
			nombreCreaturesMax_ = nombreCreaturesMax_ * 2;//**************************modification sam,
			Creature** tableauCreature = new Creature * [nombreCreaturesMax_];
			for (unsigned int i = 0; i < nombreCreaturesMax_; i++) {
				tableauCreature[i] = new Creature;
			}
			for (unsigned int i = 0; i < nombreCreatures_; i++) {
				tableauCreature[i] = creatures_[i];
			}
			delete[] creatures_;
			modifierCreature(tableauCreature);
		}
	*creatures_[nombreCreatures_] = creature;
	nombreCreatures_++;
	}
	
	nombreCreatures_;//********************?????
	return Ajoute;
	
	//return false;
}
// TODO: retire creature dans creatures_
bool Dresseur::retirerCreature(const std::string& nom) {
	bool present = false;
	for (unsigned int i = 0; i < nombreCreatures_; i++) {
		if (creatures_[i]->obtenirNom() == nom) {
			present = true;
		}
		if (present == true) {
			creatures_[i] = creatures_[i + 1];
		}
	}
	/*if (present == true) {****************************modification sam roule quand meme si cette partie est retiree
		[nombreCreatures_] = nullptr;
		nombreCreatures_--;
	}*/
	return present;
}
// TODO: fonction d'affichage
void Dresseur::affichage() const {

	// afficher le nom et le nombre de creature
	cout << obtenirNom() << " possede " << nombreCreatures_ << " creature(s)" << endl;
	// ex: Leon possede 1 creature(s)
	for (int i = 0; i < nombreCreatures_; i++) {
		cout << "- " << i + 1 << " - \t";
		cout << "\t";							//On dois set l'allignement auto****************
		creatures_[i]->information();
		cout << endl;
	}
	// boucler sur chaque creature et afficher ses informations
}
