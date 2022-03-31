#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include "image.h"
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
//typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
	{0, 255, 54.213, 236.589},
	{18.411, 182.376, 200.787, 120},
	{139.583, 172.841, 94.0878, 88.4974},
	{158.278, 172.841, 89.0236, 80.0384}
};



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
	//cout << skip << endl;

	//Initialisation du tableau imgBinaire
	ImageGris imgGris(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgGris[ini] = vector<double>(nbLignes);
	}

	//int couleur;
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








/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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




/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
 // Niveau *
 // Auteur Julien
//Degré de confiance 80% : La gestion des bords peut surement être réduite
ImageGris intensiteH(ImageGris img) {
	//ImageGris imgIntensiteH;

	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgIntensiteH(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgIntensiteH[ini] = vector<double>(nbLignes);
	}

	for (int i = 1; i < nbColonnes - 1; i++)
	{
		for (int j = 1; j < nbLignes - 1; j++)
		{
			imgIntensiteH[i][j] = img[i - 1][j - 1] + 2 * img[i][j - 1] + img[i + 1][j - 1] - img[i - 1][j + 1] - 2 * img[i][j + 1] - img[i + 1][j + 1];
		}
	}
	/*
	for (int i = 1; i < nbColonnes - 1; i++)
	{
		for (int j = 1; j < nbLignes - 1; j++)
		{
			imgIntensiteH[i][j] = img[i - 1][j - 1] + 2 * img[i][j - 1] + img[i + 1][j - 1] - img[i - 1][j + 1] - 2 * img[i][j + 1] - img[i + 1][j + 1];
		}
	}*/
	//faire les bords
	//imgIntensiteH[0][j] = 0

	//le haut de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgIntensiteH[0][j] = 0;
	}
	//nbLignes = haut vers le bas
	//nbcolonnes = gauche vers la doite

	//le bas de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgIntensiteH[nbLignes - 1][j] = 0;
	}

	//la gauche de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgIntensiteH[i][0] = 0;
	}

	//la droite de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgIntensiteH[i][nbColonnes - 1] = 0;
	}


	/*
	for (int i = 0; i < nbColonnes; i++)
	{
		for (int j = 0; j < nbLignes; j++)
		{
			imgIntensiteH[i][j] = 0;
		}
		i = nbColonnes - 1;
	}*/
	//test pour la barre du haut et du bas
	/*for (int i = 1; i < nbColonnes-1; i++)
	{
		for (int j = 1; j < nbLignes-1; j++)
		{
			imgIntensiteH[i][j] = 2 * img[i][j + 1] - img[i + 1][j + 1];
		}
	}*/
	return imgIntensiteH;
}



/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
 // Niveau *
 // Auteur Julien
//Degré de confiance 80% : La gestion des bords peut surement être réduite
ImageGris intensiteV(ImageGris img) {
	//ImageGris imgIntensiteV;

	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgIntensiteV(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgIntensiteV[ini] = vector<double>(nbLignes);
	}

	for (int i = 1; i < nbColonnes - 1; i++)
	{
		for (int j = 1; j < nbLignes - 1; j++)
		{
			imgIntensiteV[i][j] = img[i - 1][j - 1] + 2 * img[i - 1][j] + img[i - 1][j + 1] - img[i + 1][j - 1] - 2 * img[i + 1][j] - img[i + 1][j + 1];
		}
	}
	//le haut de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgIntensiteV[0][j] = 0;
	}
	//nbLignes = haut vers le bas
	//nbcolonnes = gauche vers la doite

	//le bas de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgIntensiteV[nbLignes - 1][j] = 0;
	}

	//la gauche de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgIntensiteV[i][0] = 0;
	}

	//la droite de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgIntensiteV[i][nbColonnes - 1] = 0;
	}

	return imgIntensiteV;
}




/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
 // Niveau *
 // Auteur Julien
//Degré de confiance 100% : Peut être plus rapide avec une optimisation de intensiteH et intensiteV
ImageGris intensite(ImageGris img) {
	ImageGris imgIntensiteH = intensiteH(img);
	ImageGris imgIntensiteV = intensiteV(img);

	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgIntensite(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgIntensite[ini] = vector<double>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++)
	{
		for (int j = 0; j < nbLignes; j++)
		{
			imgIntensite[i][j] = sqrt((imgIntensiteH[i][j] * imgIntensiteH[i][j]) + (imgIntensiteV[i][j] * imgIntensiteV[i][j]));
		}
	}
	return imgIntensite;
	//imgIntensite = sqrt((imgIntensiteH * imgIntensiteH) + (imgIntensiteV * imgIntensiteV));
}


void testSobel() {
	ASSERT(ImageGrisEgal(intensiteH(imgGrisTest),
		ImageGris({
			{0, 0, 0, 0},
			{0, -373.47, 227.507, 0},
			{0, -22.1312, 323.866, 0},
			{0, 0, 0, 0}
			}),
		0.001));
	ASSERT(ImageGrisEgal(intensiteV(imgGrisTest),
		ImageGris({
			{0, 0, 0, 0},
			{0, -15.1398, 150.501, 0},
			{0, -9.0336, 273.023, 0},
			{0, 0, 0, 0}
			}),
		0.001));
	ASSERT(ImageGrisEgal(intensite(imgGrisTest),
		ImageGris({
			{0, 0, 0, 0},
			{0, 373.777, 272.782, 0},
			{0, 23.9039, 423.593, 0},
			{0, 0, 0, 0}
			}),
		0.001));

	cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
	ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm")), "sobel/Baboon.512.pgm");
	ecrirePGM(intensite(lirePGM("images/Billes.256.pgm")), "sobel/Billes.256.pgm");
	ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
	ecrirePGM(intensite(lirePGM("images/House.256.pgm")), "sobel/House.256.pgm");
	ecrirePGM(intensite(lirePGM("images/Lena.512.pgm")), "sobel/Lena.512.pgm");
}



int main() {

	testSobel();


	//ecrirePGM(intensiteV(lirePGM("images/House.256.pgm")), "sobel/House.256.pgm");

	return 0;
}
