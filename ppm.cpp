#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "image.h"
#include "ppm.h"
using namespace std;

// Niveau **
// Auteur Baptiste
//Degré de confiance 50% : pas de gestion de commentaires d'image
Image lirePPM(string source) {
	ifstream PPM(source);
	if (not PPM)
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
    
    
    Image img(nbColonnes);
	for (int ini = 0; ini < nbColonnes; ini++) {
		img[ini] = vector<Couleur>(nbLignes);
	}
    
    for(int i = 0; i < nbColonnes; i++){
        for( int y = 0; y < nbLignes; y++){
			Couleur couleur;
			image >> couleur.r;
			image >> couleur.g;
			image >> couleur.b;

			img[i][y] = couleur;
        }
    }
	image.close();
	return img;
}

// Niveau **
// Auteur Baptiste
//Degré de confiance 80% : Ecrit forcement un taux de nuance à 255
void ecrirePPM(Image img, string cible) {
    ofstream imageC;
	imageC.open(cible);
	int nbColonnes = img.size();
	int nbLignes = img[0].size();
    
	imageC << "P3" << endl;
	imageC << nbLignes << " " << nbColonnes << endl;
	imageC << 255 << endl;
    for(int i = 0; i < nbColonnes; i++){
        for(int y = 0; y < nbLignes; y++){
			imageC << img[i][y].r << " " << img[i][y].g << " " << img[i][y].b << " " << endl;
        }
    }
	imageC.close();
}
