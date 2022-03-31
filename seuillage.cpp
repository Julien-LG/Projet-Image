#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"

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

// Niveau **
// Auteur ??? déjà présent dans l'archive
ImageGris seuillage(ImageGris img, int seuil) { 
    for(int i=0; i<img.size(); i++)
        for(int j=0; j<img[0].size(); j++)
            if(img[i][j]>=seuil)
                img[i][j]=0.;
            else
                img[i][j]=255.;
    return img;
}

// Niveau ***
// Auteur Julien
//Degré de confiance 90% : Peut être plus rapide avec une optimisation de la gestion des bords
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    
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
}

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
}
