#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "pgm.h"
#include "sobel.h"
#include "image-test.h"

void sobelTest() {
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

int main(){
    sobelTest();
    
	return 0;
}
