/*
* @fichier: Pouvoir.h
* @auteurs:
* @date:
* @description: La classe Pouvoir correspond aux differents attaques
*/

#ifndef POUVOIR_H
#define POUVOIR_H

#include <string>
#include <iostream>

using namespace std;

class Pouvoir {
public:
	Pouvoir();
	Pouvoir(const string& nom, unsigned int nombreDeDegat, unsigned int manaNecessaire);
	~Pouvoir();

	unsigned int obtenirNombreDeDegat() const;
	unsigned int obtenirManaNecessaire() const;
	string obtenirNom() const;

	void modifierNombreDeDegat(unsigned int nombreDegat);
	void modifierManaNecessarie(unsigned int manaNecessaire);
	void modifierNom(const string& nom);

	void description() const;

private:
	string nom_;
	unsigned int nombreDeDegat_;
	unsigned int manaNecessaire_;
};

#endif