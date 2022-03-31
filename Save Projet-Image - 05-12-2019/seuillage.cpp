#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"

ImageGris renormalise(ImageGris img) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction renormalise non implanté ligne 12");
}

ImageGris seuillage(ImageGris img, int seuil) { 
    for(int i=0; i<img.size(); i++)
        for(int j=0; j<img[0].size(); j++)
            if(img[i][j]>=seuil)
                img[i][j]=0.;
            else
                img[i][j]=255.;
    return img;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implanté ligne 27");
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implanté ligne 32");
}
