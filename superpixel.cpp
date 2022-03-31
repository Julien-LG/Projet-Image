#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.h"

 /** Renvoie la distance Euclidienne entre deux points
 * @param p un point
 * @param c un point
 * @return la distance entre p et c
 **/
 // Niveau *
 // Auteurs Baptiste + Julien
//Degré de confiance 90% : Pas de limitations connus
double distancePoints(Point p, Point c) {
	//d = sqrt(((xa - xb) * (xa - xb)) + ((ya - yb) * (ya - yb)));
	//d = sqrt(((xp - xc) * (xp - xc)) + ((yp - yc) * (yp - yc)));
	double distance = 0;
	for (int i = 0; i < p.size(); i++)
	{
		//axe des x						axe des y
		//return sqrt((p[i] - c[i]) * (p[0] - c[0]));
		//accumulation de la distance au carré
		distance += (p[i] - c[i]) * (p[i] - c[i]);
	}
	distance = sqrt(distance);
	return distance;
}

/** Renvoie la distance Euclidienne d'un point a un ensemble de points
* @param p un point
* @param C un ensemble de points
* @return la distance
**/
// Niveau *
// Auteur Baptiste
//Degré de confiance 100% : Pas de limitations connus
double distanceAEnsemble(Point p, EnsemblePoints C) {
	double distance = distancePoints(p, C[0]);

	for (int i = 1; i < C.size(); i++)
	{
		if (distance > distancePoints(p, C[i]))
		{
			distance = distancePoints(p, C[i]);
		}
	}
	return distance;
}

/** Renvoie le plus proche voisin d'un point p dans un ensemble C
* @param p un point
* @param C un ensemble de points
* @return l'index du plus proche voisin
**/
// Niveau *
// Auteur Baptiste
//Degré de confiance 100% : Pas de limitations connus
int plusProcheVoisin(Point p, EnsemblePoints C) {    
	//pour le plus proche voisin, il faut prendre le point avec la plus petite distance
	// min distancePoint
	
	double distance = distancePoints(p, C[0]);
	int min = 0;

	for (int i = 1; i < C.size(); i++)
	{
		if (distance > distancePoints(p, C[i]))
		{
			distance = distancePoints(p, C[i]);
			min = i;
		}
	}
	//distanceAensemble ??
	//return distance;
	return min;
}

/** Renvoie les points p de P tels que C[k] est le plus proche voisin de p dans C
* @param P un ensemble de points
* @param C un ensemble de points
* @param k un entier
* @return un sous ensemble des points de P
*/
// Niveau *
// Auteur Baptiste
//Degré de confiance 100% : Pas de limitations connus
EnsemblePoints sousEnsemble(EnsemblePoints P, EnsemblePoints C, int k) {
	EnsemblePoints sousEnsemble;
	for (int i = 0; i < P.size(); i++)
	{
		if (k == plusProcheVoisin(P[i], C))
		{
			sousEnsemble.push_back(P[i]);
		}
	}
	return sousEnsemble;
}

/** Renvoie le barycentre d'un ensemble de points
* @param Q un ensemble de points
* @return c le barycentre de Q
**/
// Niveau *
// Auteur Julien
//Degré de confiance 50% : Na pas pu être testée car K-Moyenne non fait
Point barycentre(EnsemblePoints Q) {
	int xQ = Q.size();
	int yQ = Q[0].size();

	Point barycentreX;
	Point barycentreY;
	Point barycentre(yQ);
	double total = 0;

	/*for (int i = 0; i < xQ; i++)
	{
		for (int y = 0; y < yQ; y++)
		{
			total += Q[i][y];
		}
		barycentre[i] = total / yQ;
	}*/

	for (int i = 0; i < yQ; i++)
	{
		for (int y = 0; y < xQ; y++)
		{
			total += Q[y][i];
		}
		barycentre[i] = total / xQ;
		//barycentre[i] = total / 100;
	}

	//barycentre = 

	return barycentre;
}

/** Renvoie la K-moyenne de deux ensembles de points
* @param P un ensemble de points
* @param C un ensemble de points
* @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
* @return C un ensemble de points les positions finales de points pilotes
**/
EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
	/*EnsemblePoints kMoyenne;

	for (int i = 0; i < nbAmeliorations; i++)
	{



	}

	return kMoyenne;*/
	throw runtime_error("Fonction pivotSuperPixel non implanté ligne 158");
}

/** Implantation optimisee de K-moyenne
* @param P un ensemble de points
* @param C un ensemble de points
* @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
* @return C un ensemble de points les positions finales de points pilotes
**/
EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

/** Renvoie un ensemble de points (espace spatio colorimetrique)
* regulierement espaces dans une image
* @param img une image
* @param lambda un double
* @param mu un entier
* @return un ensemble de points dans l'espace spatio colorimetrique
**/
EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implanté ligne 74");
}

/** Renvoie les superpixels d'une image dans l'espace spatio colorimetrique
* @param img une image en teintes de gris
* @param lambda un double
* @param mu un entier
* @param nbAmeliorations un entier
* @return un ensemble de points, les superpixels
**/
EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implanté ligne 79");
}

/** Filtre SuperPixel
* @param img une image
* @param lambda un double
* @param mu un entier
* @param nbAmeliorations
* @return l'image associee aux superpixels d'une image
**/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implanté ligne 84");
}
