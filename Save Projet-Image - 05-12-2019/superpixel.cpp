#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.h"

double distancePoints(Point p, Point c) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction distancePoints non implanté ligne 10");
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction distanceAEnsemble non implanté ligne 15");
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction plusProcheVoisin non implanté ligne 20");
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction sousEnsemble non implanté ligne 25");
}

Point barycentre(EnsemblePoints Q) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction barycentre non implanté ligne 30");
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction KMoyenne non implanté ligne 35");
}

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

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implanté ligne 74");
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implanté ligne 79");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implanté ligne 84");
}
