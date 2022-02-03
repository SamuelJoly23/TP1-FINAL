/*
* @fichier: Dresseur.h
* @auteurs:
* @date:
* @description: les dresseurs sont les etres capables d'attraper des creatures
*/

#ifndef DRESSEUR_H
#define DRESSEUR_H

#include <iostream>
#include <string>
#include "Creature.h"

#define MAX_NOMBRE_CREATURES 2

using namespace std;

class Dresseur {
public:
	Dresseur();
	Dresseur(const string& nom);
	~Dresseur();

	string obtenirNom() const;
	unsigned int obtenirNombreCreatures() const;
	Creature** obtenirCreatures() const;

	void modifierNom(const string& nom);
	void modifierCreature(Creature** creatures);

	void modifierNombreCreaturesMax(unsigned int nombreCreaturesMax); //**************AJOUT DE FONCTION************
	void modifierNombreCreatures(unsigned int nombreCreatures); //**************AJOUT DE FONCTION************

	bool ajouterCreature(const Creature& creature);
	bool retirerCreature(const string& nom);

	void affichage() const;

private:
	std::string nom_;
	Creature** creatures_;
	unsigned int nombreCreatures_;
	unsigned int nombreCreaturesMax_;
};

#endif