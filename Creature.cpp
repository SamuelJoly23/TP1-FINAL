/*
* @fichier: Creature.cpp
* @auteurs:
* @date:
* @description: Les creatures sont des etres destines au combat
*/

#include "Creature.h"

// TODO: constructeur avec liste d'initialisation
Creature::Creature() {
	nom_ = "";
	attaque_ = 0;
	defense_ = 0;
	pointDeVie_ = 0;
	energie_ = 0;
	pointDeVieTotal_ = 0;
	energieTotal_ = 0;
	experience_ = 0;
	experienceNecessaire_ = 100;
	niveau_ = 1;
	pouvoir_ = Pouvoir();
}

// TODO: constructeur par parametre avec liste d'initialisation
Creature::Creature(const std::string& nom, unsigned int attaque,
	unsigned int defense, unsigned int pointDeVie, unsigned int energie, Pouvoir pouvoir) : Creature() {

	nom_ = nom;
	attaque_ = attaque;
	defense_ = defense;
	pointDeVie_ = pointDeVie;
	pointDeVieTotal_ = pointDeVie;
	energie_ = energie;
	energieTotal_ = energie;
	experience_ = 0;
	niveau_ = 1;
	experienceNecessaire_ = 100;
	pouvoir_ = pouvoir;

}

// TODO: destructeur
Creature::~Creature() {}

// TODO: Getters
std::string Creature::obtenirNom() const {
	return nom_;
}

unsigned int Creature::obtenirAttaque() const {
	return attaque_;
}

unsigned int Creature::obtenirDefense() const {
	return defense_;
}
unsigned int Creature::obtenirPointDeVie() const { 
	return pointDeVie_;
}

unsigned int Creature::obtenirPointDeVieTotal() const {
	return pointDeVieTotal_;
}


unsigned int Creature::obtenirEnergie() const {
	return energie_;
}

unsigned int Creature::obtenirEnergieTotale() const {
	return energieTotal_;
}

unsigned int Creature::obtenirExperience() const {
	return experience_;
}

unsigned int Creature::obtenirExperienceNecessaire() const {
	return experienceNecessaire_;
}

unsigned int Creature::obtenirNiveau() const {
	return niveau_;
}

Pouvoir Creature::obtenirPouvoir() const {
	return pouvoir_;
}

// TODO: Setters
void Creature::modifierAttaque(unsigned int attaque) {
	attaque_ = attaque;
}

void Creature::modifierDefense(unsigned int defense) {
	defense_ = defense;
}

void Creature::modifierPointDeVie(unsigned int pointDeVie) {
	pointDeVie_ = pointDeVie;
}

void Creature::modifierEnergie(unsigned int mana) {
	energie_ = mana;
}

void Creature::modifierExperience(unsigned int experience) {
	experience_ = experience;
}

void Creature::modifierNiveau(unsigned int niveau) {
	niveau_ = niveau;
}

void Creature::modifierPouvoir(Pouvoir pouvoir) {
	pouvoir_ = pouvoir;
}

void Creature::attaquer(Creature& creature) {
	
	if (energie_ >= pouvoir_.obtenirManaNecessaire()) {
		if (creature.obtenirPointDeVie() >= 0) {
			//Calcul du nombre de degat selon une formule
			unsigned int degat = (pouvoir_.obtenirNombreDeDegat()) * (attaque_ / 2 - creature.defense_);
			int tentative = rand() % 6;
			//l'attaque rate une fois sur 6
			if (tentative != 3) {
				std::cout << nom_ << " lance " << pouvoir_.obtenirNom() << " qui inflige " << degat << " degat a " << creature.obtenirNom() << endl;
				if (degat > creature.obtenirPointDeVie()) {
					creature.modifierPointDeVie(0);
					int xp = experienceGagnee(creature);
					cout << nom_ << " a gagné " << xp << " XP" << endl;
				}
				else
					creature.modifierPointDeVie(creature.obtenirPointDeVie() - degat);
				cout << creature.obtenirNom() << " a encore " << creature.obtenirPointDeVie() << " PV" << endl;
				energie_ -= pouvoir_.obtenirManaNecessaire();
			}
			else {
				std::cout << "Attaque " << pouvoir_.obtenirNom() << " a échouée" << endl;
			}
		}
		else
			std::cout << "Vous deja avez vaincu " << creature.obtenirNom() << endl;
	}
	
}

int Creature::experienceGagnee(const Creature& creature) {
	
	if (creature.obtenirPointDeVie() <= 0) {
		//Calcul de l'experience selon une formule mystérieuse
		int experience = (creature.obtenirNiveau() + 1 - niveau_) * ((creature.obtenirAttaque() + 5 - attaque_) * (creature.obtenirDefense() + 3 - defense_)) + (pointDeVie_ / 2);
		if (experience > (experienceNecessaire_ - experience_)) {
			//Cas ou la creature va monter d'un niveau
			int experienceRestante = experience - (experienceNecessaire_ - experience_);
			niveau_++;
			attaque_ += 1;
			defense_ += 1;
			pointDeVie_ += 5;
			energie_ += 5;
			energieTotal_ += 5;
			pointDeVieTotal_ += 5;
			experience_ = experienceRestante;
			experienceNecessaire_ = experienceNecessaire_ * 15 / 10;
		}
		else {
			//Sinon elle recupère juste de l'expérience
			experience_ += experience;
		}
		return experience;
	}
	
	return 0;
}

//Fonction d'affichage
void Creature::information() const {

	// afficher les attributs de la creature
	cout << nom_ << " a " << attaque_ << " en attaque et " << defense_ << " en defence," << endl;
	cout << "Il a " << pointDeVieTotal_ << "/" << pointDeVieTotal_ << " PV et " << energie_ << "/" << energieTotal_ << " Energie " << endl;
	cout << "Il est au niveau " << niveau_ << " avec " << experience_ << " d'XP" << endl;
	cout << "Il lui manque " << experienceNecessaire_ << " jusqu'au prochain niveau" << endl;

	// afficher le pouvoir
	pouvoir_.description();
}