#include <stdexcept>

/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "ppm.h"
#include "image-test.h"

void lireEcrirePPMTest(){
    cout << "Vérifier que les images obtenues dans 'ppm/' sont identiques aux images d'origine dans 'images/'" << endl;
    ecrirePPM(lirePPM("images/Baboon.512.ppm"),  "ppm/Baboon.512.ppm");
    ecrirePPM(lirePPM("images/Billes.256.ppm"),  "ppm/Billes.256.ppm");
    ecrirePPM(lirePPM("images/Embryos.512.ppm"), "ppm/Embryos.512.ppm");
    ecrirePPM(lirePPM("images/House.256.ppm"),   "ppm/House.256.ppm");
    ecrirePPM(lirePPM("images/Lena.512.ppm"),    "ppm/Lena.512.ppm");
    ecrirePPM(lirePPM("images/Willis.512.ppm"),  "ppm/Willis.512.ppm");
}

int main(){
    cout << "Tests des fonctions lirePPM et ecrirePPM" << endl;
    lireEcrirePPMTest();
}
