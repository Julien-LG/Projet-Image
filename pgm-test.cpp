#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "pgm.h"
#include "image-test.h"

void lireEcrirePGMTest() {
	cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
	ecrirePGM(lirePGM("images/brain.pgm"), "pgm/brain.pgm");
	ecrirePGM(lirePGM("images/illusion.pgm"), "pgm/illusion.pgm");
}

void inversePGMTest() {
	ImageGris imageOriginale;
	cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
	imageOriginale = lirePGM("images/brain.pgm");
	ecrirePGM(inversePGM(imageOriginale), "pgm/brain-inverse.pgm");
	imageOriginale = lirePGM("images/illusion.pgm");
	ecrirePGM(inversePGM(imageOriginale), "pgm/illusion-inverse.pgm");
}

int main(){
    cout << "Tests des fonctions lirePPM et ecrirePPM" << endl;
    lireEcrirePGMTest();
    cout << "Tests de la fonction inverseePGM" << endl;
    inversePGMTest();
}
