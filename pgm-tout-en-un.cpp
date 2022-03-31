#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include "image.h"
using namespace std;
/** Structure de donnee pour representer une image en teintes de gris **/
//typedef vector<vector<double> > ImageGris;

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
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



/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
 // Niveau *
 // Auteur Julien
//Degré de confiance 80% : Ecrit forcement un taux de nuance à 255
void ecrirePGM(ImageGris img, string cible) {
	ofstream imageC;
	imageC.open(cible);
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	imageC << "P2" << endl;
	imageC << nbLignes << " " << nbColonnes << endl;
	imageC << 255 << endl;
	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			imageC << ((int)img[i][y]) << " ";
		}
	}
	imageC.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
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
			//imgGrisInverse[i][y] = 255 - img[i][y];
		}
		cout << endl;
	}

	return imgGrisInverse;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();

	//lirePGM("images/brain.pgm");
	//ecrirePGM(lirePGM("images/brain.pgm"), "pgm/brain.pgm");
    return 0;
}
