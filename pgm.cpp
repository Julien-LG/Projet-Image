#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include <string>
#include "image.h"
#include "pgm.h"

using namespace std;

// Niveau *
// Auteur Julien
//Degré de confiance 50% : pas de gestion de commentaires d'image
ImageGris lirePGM(string source) {
	ifstream PGM(source);
	if (not PGM)
		throw runtime_error("Fichier non trouve: " + source);

	ifstream image;
	image.open(source);

	//Variable de stockage qui sert à passer une ligne ou un nombre
	string skip;
	getline(image, skip);

	int nbLignes;
	int nbColonnes;

	image >> nbLignes;
	image >> nbColonnes;

	image >> skip;

	//Initialisation du tableau imgGris
	ImageGris imgGris(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgGris[ini] = vector<double>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			image >> imgGris[i][y];
		}
	}

	image.close();
	return imgGris;
}

// Niveau *
// Auteur Julien
//Degré de confiance 80% : Ecrit forcement un taux de nuance à 255
void ecrirePGM(ImageGris img, string cible) {
	ofstream imageC;
	imageC.open(cible);
	int nbColonnes = img.size();
	int nblignes = img[0].size();

	imageC << "P2" << endl;
	imageC << nblignes << " " << nbColonnes << endl;
	imageC << 255 << endl;
	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nblignes; y++) {
			imageC << ((int)img[i][y]) << " ";
		}
	}
	imageC.close();
}

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size()) {
		cout << "Nombre de lignes différent" << endl;
		return false;
	}
	for (int i = 0; i < a[0].size(); i++)
		if (a[0].size() != b[i].size()) {
			cout << "Nombre de colonnes différent" << endl;
			return false;
		}
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a[0].size(); j++)
			if (abs(a[i][j] - b[i][j]) > precision) {
				cout << "Valeur differentes en position " << i << "," << j
					<< ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
				return false;
			}
	return true;
}

// Niveau *
// Auteur Julien
//Degré de confiance 100% : Pas de limitations connus
ImageGris inversePGM(ImageGris img) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgGrisInverse(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgGrisInverse[ini] = vector<double>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			double couleur = img[i][y];
			imgGrisInverse[i][y] = 255 - couleur;			
		}
		cout << endl;
	}

	return imgGrisInverse;
}
