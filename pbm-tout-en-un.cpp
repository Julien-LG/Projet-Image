#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include "image.h"
using namespace std;

/** Structure de donnée pour représenter une image binaire **/
//typedef vector<vector<int> > ImageNB;

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
 // Niveau *
 // Auteurs Julien / Baptiste
//Degré de confiance 50% : pas de gestion de commentaires d'image
ImageNB lirePBM(string source) {
	ifstream PBM(source);
	if (not PBM)
		throw runtime_error("Fichier non trouve: " + source);
		
	ifstream image;
	image.open(source);

	//Variable de stockage qui sert à passer une ligne ou un nombre
	string skip;
	getline(image, skip);

	int nbLignes;
	int nbColonnes;
	
	/*image >> nbColonnes;
	image >> nbLignes;*/
	image >> nbLignes;
	image >> nbColonnes;
	
	string truc;	
	/*
	if ((getline(image, skip).substr(0,1)) == "#")
	{
		while ((getline(image, skip).substr(0, 1)) == "#")
		{
			getline(image, skip);
		}
	}*/
	//cout << image.get() << endl;
	/*getline(image, skip);
	cout << skip << endl;*/
	//getline(image, skip);
	/*
	cout << "entre la " << skip << " et la" << endl;
	if (image.get() == '#')
	{
		cout << "trouvé" << endl;
		getline(image, skip);
		cout << skip << endl;
		/*while (image.get() == '#')
		{
			getline(image, skip);
		}*/
	/*}
	/*
	if (image.get() == '#')
	{
		while (image.get() == '#')
		{
			getline(image, skip);
		}
	}*/

	//Initialisation du tableau imgBinaire
	ImageNB imgBinaire(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgBinaire[ini] = vector<int>(nbLignes);
	}

	int couleur;
	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			image >> imgBinaire[i][y];
		}
	}
	/*
	//test d'affichage
	for (int i2 = 0; i2 < nbColonnes; i2++) {
		for (int y2 = 0; y2 < nbLignes; y2++) {
			cout << imgBinaire[i2][y2] << " ";
		}
		cout << endl;
	}*/
	image.close();
	return imgBinaire;
}


/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
 // Niveau *
 // Auteurs Julien / Baptiste
//Degré de confiance 100% : Pas de limitations connus
void ecrirePBM(ImageNB img, string cible) {
	ofstream imageC;
	imageC.open(cible);
	int nbColonnes = img.size();
	int nblignes = img[0].size();

	imageC << "P1" << endl;
	imageC << nbColonnes << " " << nblignes << endl;
	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nblignes; y++) {
			imageC << img[i][y] << " ";
		}
	}
	imageC.close();
}


/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
 // Niveau *
 // Auteurs Julien / Baptiste
 //Degré de confiance 100% : Pas de limitations connus
void affichePBM(ImageNB img) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();	
	
	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			if (img[i][y] == 1)
				cout << "@" << " ";

			if (img[i][y] == 0)
				cout << " " << " ";
		}
		cout << endl;
	}
}


/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
 // Niveau *
 // Auteurs Julien / Baptiste
//Degré de confiance 100% : Pas de limitations connus
ImageNB inversePBM(ImageNB img) {
	int nbColonnes = img.size();
	int nbLignes = img[0].size();

	ImageNB imgBinaireInverse(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		imgBinaireInverse[ini] = vector<int>(nbLignes);
	}

	for (int i = 0; i < nbColonnes; i++) {
		for (int y = 0; y < nbLignes; y++) {
			if (img[i][y] == 1)
				imgBinaireInverse[i][y] = 0;

			if (img[i][y] == 0)
				imgBinaireInverse[i][y] = 1;
		}
		cout << endl;
	}


    return imgBinaireInverse;
    //throw runtime_error("Fonction inversePBM non implanté ligne 48");
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

void testInversePBM() {
	cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
	ecrirePBM(inversePBM(lirePBM("images/smiley.pbm")), "pbm/smiley-Inverse.pbm");
	ecrirePBM(inversePBM(lirePBM("images/cercle.pbm")), "pbm/cercle-Inverse.pbm");
	ecrirePBM(inversePBM(lirePBM("images/code.pbm")), "pbm/code-Inverse.pbm");
	ecrirePBM(inversePBM(lirePBM("images/damier.pbm")), "pbm/damier-Inverse.pbm");
}

int main(){
	
    testLirePBM();
	testInversePBM();
	/*
	affichePBM(lirePBM("./images/smiley.pbm"));
	affichePBM(inversePBM(lirePBM("./images/smiley.pbm")));
	*/
//	affichePBM(lirePBM("./images/cercle.pbm"));
	//affichePBM(lirePBM("./images/commentaires.pbm")); 
	/*
	ecrirePBM(lirePBM("./images/smiley.pbm"), "./pbm/smiley.pbm");
	affichePBM(lirePBM("./images/smiley.pbm"));
	affichePBM(inversePBM(lirePBM("./images/smiley.pbm")));*/
	//ecrirePBM(inversePBM(lirePBM("./images/smiley.pbm")), "./pbm/smileyInverse2.pbm");
    // Remplacer la ligne suivante par le code adéquat

}

