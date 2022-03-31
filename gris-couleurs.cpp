#include <stdexcept>
#include <vector>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.h"
using namespace std;

// Niveau **
// Auteur Baptiste
//Degré de confiance 100% : Pas de limitations connus
ImageGris CouleurAuGris( Image img ) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	//Initialisation du tableau imgGris
	ImageGris imgGris(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgGris[ini] = vector<double>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			imgGris[i][y] = 0.2126 * img[i][y].r + 0.7152 * img[i][y].g + 0.0722 * img[i][y].b;
		}
	}

	return imgGris;
}

// Niveau **
// Auteur Baptiste
//Degré de confiance 100% : Pas de limitations connus
Image GrisACouleur( ImageGris img ) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	//Initialisation du tableau imgCouleur
	Image imgCouleur(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgCouleur[ini] = vector<Couleur>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			imgCouleur[i][y].r = 'c';
			imgCouleur[i][y].g = 'c';
			imgCouleur[i][y].b = 'c';
		}
	}

	return imgCouleur;
}
