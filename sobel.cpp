#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.h"

 // Niveau *
 // Auteur Julien
//Degré de confiance 80% : La gestion des bords peut surement être réduite
ImageGris intensiteH(ImageGris img) {    
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	//Ititialisation du tableau à retourner
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
	//gestion des bords de l'image

	//le haut de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgIntensiteH[0][j] = 0;
	}

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

	return imgIntensiteH;
}

// Niveau *
// Auteur Julien
//Degré de confiance 80% : La gestion des bords peut surement être réduite
ImageGris intensiteV(ImageGris img) {
    int nbColonnes = img.size();
	int nbLignes = img[0].size();

	//Ititialisation du tableau à retourner
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

// Niveau *
// Auteur Julien
//Degré de confiance 100% : Peut être plus rapide avec une optimisation de intensiteH et intensiteV
ImageGris intensite(ImageGris img) {
    ImageGris imgIntensiteH = intensiteH(img);
	ImageGris imgIntensiteV = intensiteV(img);

	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	//Ititialisation du tableau à retourner
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
}
