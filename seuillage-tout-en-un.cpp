#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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

/////////////////////////////////////////////////////////////////////////////////
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

	for (int i = 1; i < nbColonnes - 1; i++)
	{
		for (int j = 1; j < nbLignes - 1; j++)
		{
			imgIntensiteH[i][j] = img[i - 1][j - 1] + 2 * img[i][j - 1] + img[i + 1][j - 1] - img[i - 1][j + 1] - 2 * img[i][j + 1] - img[i + 1][j + 1];
		}
	}
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
/////////////////////////////////////////////

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
	//faire le 4.3 (bonus)
}


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
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
 // Niveau *
 // Auteur Julien
//Degré de confiance 100% : Pas de limitations connus
ImageGris renormalise(ImageGris img) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgRenormalise(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgRenormalise[ini] = vector<double>(nbLignes);
	}

	double max = 0;
	for (int i = 0; i < nbColonnes; i++)
	{
		for (int j = 0; j < nbLignes; j++)
		{
			if (img[i][j] > max)
			{
				max = img[i][j];
			}
		}
	}

	for (int i = 0; i < nbColonnes; i++)
	{
		for (int j = 0; j < nbLignes; j++)
		{			
			imgRenormalise[i][j] = 255 * img[i][j] / max;			
		}
	}
	return imgRenormalise;
}


/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
 // Niveau **
 // Auteur Julien
//Degré de confiance 100% : Pas de limitations connus
ImageGris seuillage(ImageGris img, int seuil) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageGris imgSeuil(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgSeuil[ini] = vector<double>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++)
	{
		for (int j = 0; j < nbLignes; j++)
		{
			if (img[i][j] < seuil)
			{
				imgSeuil[i][j] = 255;
			}
			else
			{
				imgSeuil[i][j] = 0;
			}
		}
	}
	return imgSeuil;
}


/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
 // Niveau ***
 // Auteur Julien
//Degré de confiance 90% : Peut être plus rapide avec une optimisation de la gestion des bords
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
	//ImageGris imgSeuilFaible = seuillage(ImageGris img, 255);
	//ImageGris imgSeuilFort = seuillage(ImageGris img, 1);

	int nbColonnes = imgIntensite.size();
	int nbLignes = imgIntensite[0].size();

	ImageGris imgDoubleSeuillage = imgIntensite;
	for (int i = 1; i < nbColonnes-1; i++)
	{
		for (int j = 1; j < nbLignes-1; j++)
		{
			if ( imgIntensite[i][j] > seuil and (imgContour[i - 1][j - 1] == 0 or imgContour[i - 1][j] == 0 or imgContour[i - 1][j + 1] == 0 or imgContour[i][j - 1] == 0 or imgContour[i][j + 1] == 0 or imgContour[i + 1][j - 1] == 0 or imgContour[i + 1][j] == 0 or imgContour[i + 1][j + 1] == 0))
			{
				imgDoubleSeuillage[i][j] = 0;
			}
			else
			{
				imgDoubleSeuillage[i][j] = 255;
			}
		}
	}

	//le haut de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgDoubleSeuillage[0][j] = 0;
	}
	//nbLignes = haut vers le bas
	//nbcolonnes = gauche vers la doite

	//le bas de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgDoubleSeuillage[nbLignes - 1][j] = 0;
	}

	//la gauche de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgDoubleSeuillage[i][0] = 0;
	}

	//la droite de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgDoubleSeuillage[i][nbColonnes - 1] = 0;
	}

	return imgDoubleSeuillage;
	//contour de imgIntensite[i][j]
	//imgContour[i-1][j-1]
	//imgContour[i-1][j]///////////////////
	//imgContour[i-1][j+1]/
	//imgContour[i][j-1]///////////////////
	//imgContour[i][j+1]///////////////////
	//imgContour[i+1][j-1]/
	//imgContour[i+1][j]///////////////////
	//imgContour[i+1][j+1]
	// [i-1,j-1]	[i-1,j]		[i-1,j+1]
	// [i,j-1]		[i,j]		[i,j+1]
	// [i+1,j-1]	[i+1,j]		[i+1,j+1]
}



/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
 // Niveau **
 // Auteur Julien
//Degré de confiance 90% : Peut être plus rapide avec une optimisation de la gestion des bords
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
	ImageGris imgDoubleSeuillage = imgIntensite;

	int nbColonnes = imgIntensite.size();
	int nbLignes = imgIntensite[0].size();

	//le haut de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgDoubleSeuillage[0][j] = 255;
	}
	//nbLignes = haut vers le bas
	//nbcolonnes = gauche vers la doite

	//le bas de l'image
	for (int j = 0; j < nbColonnes; j++)
	{
		imgDoubleSeuillage[nbLignes - 1][j] = 255;
	}

	//la gauche de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgDoubleSeuillage[i][0] = 255;
	}

	//la droite de l'image
	for (int i = 0 + 1; i < nbLignes - 1; i++)
	{
		imgDoubleSeuillage[i][nbColonnes - 1] = 255;
	}

	for (int y = 0; y < nbAmeliorations; y++)
	{
		for (int i = 1; i < nbColonnes - 1; i++)
		{
			for (int j = 1; j < nbLignes - 1; j++)
			{
				if (imgIntensite[i][j] > seuilFort or (imgIntensite[i][j] > seuilFaible and (imgIntensite[i - 1][j - 1] > seuilFort or imgIntensite[i - 1][j] > seuilFort or imgIntensite[i - 1][j + 1] > seuilFort or imgIntensite[i][j - 1] > seuilFort or imgIntensite[i][j + 1] > seuilFort or imgIntensite[i + 1][j - 1] > seuilFort or imgIntensite[i + 1][j] > seuilFort or imgIntensite[i + 1][j + 1] > seuilFort)))
				//if (imgIntensite[i][j] > seuilFort or (imgIntensite[i][j] > seuilFaible and (imgIntensite[i - 1][j] > seuilFort or imgIntensite[i][j - 1] > seuilFort or imgIntensite[i][j + 1] > seuilFort or imgIntensite[i + 1][j] > seuilFort)))
				{
					imgDoubleSeuillage[i][j] = 0;
				}
				else
				{
					imgDoubleSeuillage[i][j] = 255;
				}
			}
		}
	}
	

	return imgDoubleSeuillage;
    //throw runtime_error("Fonction doubleSeuillage non implanté ligne 139");
}


void seuillageTest() {
    ASSERT( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    ASSERT( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    ASSERT( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );

	ImageGris test = doubleSeuillage(intensite(imgGrisTest), 400, 80, 4);
	//ImageGris test = intensite(imgGrisTest);
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << test[i][j] << endl;
		}
	}*/


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 80), "seuillage/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;

    ecrirePGM(doubleSeuillage(lirePGM("images/Lena.512.pgm"),
                              seuillage(intensite(lirePGM("images/Lena.512.pgm" )),80),70),
              "seuillage_double/Lena-unpas.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 250, 60, 10), "seuillage_double/Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 250, 60, 10), "seuillage_double/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}


int main(){

    seuillageTest();
    doubleSeuillageTest();

    return 0;
}
