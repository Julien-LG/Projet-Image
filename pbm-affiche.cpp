#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {  
	ifstream PBM(source);
	if (not PBM)
		throw runtime_error("Fichier non trouve: " + source);

	ifstream image;
	image.open(source);

	//Variable de stockage qui sert à passer une ligne ou un nombre
	string skip;
	getline(image, skip);
	//ignore()
	//nextLine(image);

	int taille;
	image >> taille;
	image >> skip;

	int couleur;
	int y = 1;
	while (image >> couleur) {
		if (couleur == 1)
			cout << "@" << " ";

		if (couleur == 0)
			cout << " " << " ";

		if (y == taille) {
			cout << endl;
			y = 0;
		}
		y++;
	}
	image.close();
    //throw runtime_error("Fonction affichePBM non implanté ligne 17");*/
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
	ifstream PBM(source);
	if (not PBM)
		throw runtime_error("Fichier non trouve: " + source);

	ifstream imageS;
	imageS.open(source);
	ofstream imageC;
	imageC.open(cible);

	int i = 0;
	string ligne;
	while (i < 2) {
		getline(imageS, ligne);
		imageC << ligne << endl;
		i++;
	}

	int couleur;	
	while (imageS >> couleur) {
		if (couleur == 1)
			imageC << 0 << " ";

		if (couleur == 0)
			imageC << 1 << " ";
	}
	imageS.close();
	imageC.close();
    //throw runtime_error("Fonction inversePBM non implanté ligne 26");
}


int main(){
    cout << "Affichage du smiley " << endl;
	affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("./images/smiley.pbm","./pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}
