/*
* @fichier: PolyLand.h
* @auteurs:
* @date:
* @description: Polyland est la map de jeu que l'on va explorer, elle contient les differents elements de jeu
*/

#ifndef POLYLAND_H
#define POLYLAND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Dresseur.h"
#include "Creature.h"

#define MAX_DRESSEURS 100
#define MAX_CREATURES 1000
#define MAX_POUVOIRS 10

using namespace std;

class PolyLand
{
public:
	PolyLand();
	~PolyLand();

	bool ajouterDresseur(Dresseur* dresseur);
	bool ajouterCreature(const Creature& creature);

	bool retirerDresseur(const string& nom);
	bool retirerCreature(const string& nom);

	Dresseur* choisirDresseurAleatoire();
	Creature* choisirCreatureAleatoire();

	Dresseur* choisirDresseur(const string& nom);
	Creature* choisirCreature(const string& nom);

	bool attraperCreature(Dresseur* dresseur, const Creature& creature);
	bool relacherCreature(Dresseur* dresseur, const Creature& creature);

	void infoDresseur(const string& nom) const;

private:
	Dresseur** dresseurs_;
	unsigned int nombreDresseurs_;
	Creature** creatures_;
	unsigned int nombreCreatures_;

};
#endif