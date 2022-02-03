/*
* @fichier: PolyLand.h
* @auteurs:
* @date:
* @description: Polyland est la map de jeu que l'on va explorer, elle contient les differents elements de jeu
*/

#include "PolyLand.h"

// TODO: constructeur
PolyLand::PolyLand() :dresseurs_(nullptr), nombreDresseurs_(0), creatures_(nullptr), nombreCreatures_(0) {

	dresseurs_ = new Dresseur * [MAX_DRESSEURS];//****************MAXDRESSEURES???
	for (int i = 0; i < MAX_DRESSEURS; i++) {
		dresseurs_[i] = new Dresseur;
	}
	creatures_ = new Creature * [MAX_CREATURES];//********************MAX_CREATAURE
	for (int i = 0; i < MAX_CREATURES; i++) {
		creatures_[i] = new Creature;
	}
}

// TODO: destructeur
PolyLand::~PolyLand() {
	// code
	for (int i = 0; i < MAX_DRESSEURS; i++) {
		dresseurs_[i] = nullptr;
		delete dresseurs_[i];
	}
	for (int i = 0; i < MAX_CREATURES; i++) {
		creatures_[i] = nullptr;
		delete creatures_[i];
	}
}

// TODO: ajouter dresseur dans dresseurs_
// *verifier que nb dresseur < MAX_DRESSEURS
// *verifier que le dresseur n'est pas deja dans dresseurs_
// *si ajoute,  return true sion false
//	ex: Leon a bien �t� ajout� !
bool PolyLand::ajouterDresseur(Dresseur* dresseur) {
	bool Ajoute = true;
	if (nombreDresseurs_ < MAX_DRESSEURS) {
		for (int i = 0; i < nombreDresseurs_; i++) {
			if (dresseurs_[i] == dresseur) {
				return false;
			}
		}
	}
	dresseurs_[nombreDresseurs_] = dresseur;
	nombreDresseurs_++;
	cout << dresseur->obtenirNom();
	cout << " a bien ete ajoute !" << endl;

	return Ajoute;
}

// TODO: ajouter creature dans creatures_
// *verifier que nb creature < MAX_CREATURES
// *si ajoute, return true sinon false
//	ex: Pikachu a bien �t� ajout� !
bool PolyLand::ajouterCreature(const Creature& creature) {           //reference constante

	bool Ajoute = true;
	if (nombreCreatures_ < MAX_CREATURES) {
		for (int i = 0; i < nombreDresseurs_; i++) {
			if (creatures_[i] == &creature) {
				Ajoute = false;
			}
		}

		if (Ajoute == true) {
			*creatures_[nombreCreatures_] = creature;   //*********************
			nombreCreatures_++;
			cout << creature.obtenirNom() << " a bien ete ajoute !" << endl;
		}
	}
	return Ajoute;
}

// TODO: retire dresseur dans dresseurs_
bool PolyLand::retirerDresseur(const std::string& nom) {
	bool relache = false;
	for (int i = 0; i < nombreDresseurs_; i++) {
		if (dresseurs_[i]->obtenirNom() == nom) {
			relache = true;
			dresseurs_[i] = dresseurs_[i + 1];
		}
	}
	if (relache == true) {
		dresseurs_[nombreDresseurs_] = nullptr;
		nombreDresseurs_--;
	}
	return relache;
}

// TODO: retire creature dans creatures_
bool PolyLand::retirerCreature(const std::string& nom) {
	bool relache = false;
	for (int i = 0; i < nombreCreatures_; i++) {
		if (creatures_[i]->obtenirNom() == nom) {
			relache = true;
			creatures_[i] = creatures_[i + 1];
		}
	}
	if (relache == true) {
		creatures_[nombreCreatures_] = nullptr;
		nombreCreatures_--;
	}
	return relache;
}

// TODO: generer un indice aleatoire et
// retourner le dresseur a cet indice
// *verifier le nb de dresseur
Dresseur* PolyLand::choisirDresseurAleatoire() {
	srand(time(NULL));
	int indice = rand() % nombreDresseurs_;
	return dresseurs_[indice];
}

// TODO: generer un indice aleatoire et
// retourner la creature a cet indice
// *verifier le nb de creature
Creature* PolyLand::choisirCreatureAleatoire() {
	srand(time(NULL));
	int indice = rand() % nombreCreatures_;
	return creatures_[indice];
}

//Rechercher un dresseur par nom
Dresseur* PolyLand::choisirDresseur(const string& nom) {

	for (unsigned int i = 0; i < nombreDresseurs_; i++) {
		if (dresseurs_[i]->obtenirNom() == nom) {
			return dresseurs_[i];
		}
	}
	return nullptr;
}

// TODO: rechercher une creature par nom
Creature* PolyLand::choisirCreature(const string& nom) { 
	
	Creature* ptrCreature = new Creature;/*******************************************/
	ptrCreature = nullptr;

	for (unsigned int i = 0; i < nombreCreatures_; i++) {
		if (creatures_[i]->obtenirNom() == nom) {			
			ptrCreature = creatures_[i];
		}
	}
	return ptrCreature;
}
// TODO: ajouter une creature a un dresseur
bool PolyLand::attraperCreature(Dresseur* dresseur, const Creature& creature) {
	bool attrape = true;
	for (int i = 0; i < (*dresseur).obtenirNombreCreatures(); i++) {
		if (dresseur->obtenirCreatures()[i] == &creature) {
			attrape = false;
		}
	}
	if (attrape == true) {
		(*dresseur).ajouterCreature(creature);
	}

	return attrape;
}

// TODO: retirer une creature a un dresseur
bool PolyLand::relacherCreature(Dresseur* dresseur, const Creature& creature) {
	bool relache = true;
	for (int i = 0; i < (*dresseur).obtenirNombreCreatures(); i++) {
		if (dresseur->obtenirCreatures()[i] == &creature) {
			relache = false;
		}
	}
	if (relache == false) {
		dresseur->retirerCreature(creature.obtenirNom());
	}
	return relache;
}

// TODO: completer le code d'affichage
void PolyLand::infoDresseur(const std::string& nom) const {
	// effectuer une recherche par nom du dresseur passe en parametre
	Dresseur* dresseur = nullptr;
	for (int i = 0; i < nombreDresseurs_; i++) {
		if (dresseurs_[i]->obtenirNom() == nom) {
			dresseur = dresseurs_[i];
		}
	}

	if (dresseur != nullptr) {
		cout << "\u001b[32;1mInformations sur le dresseur: \033[0m" << std::endl;
		// afficher le dresseur
		dresseur->affichage();
	}
	else {
		// afficher que le dresseur est introuvable
		cout << nom << " est introuvable !" << endl;
	}
}