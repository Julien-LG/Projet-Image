#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

#include "superpixel.h"
#include "pgm.h"
#include "ppm.h"
#include "gris-couleurs.h"
#include "image-test.h"

void distancePointsTest() {

    ASSERT( distancePoints( Point( {2,0,1}), Point( {2,0,1})) == 0);
    ASSERT( distancePoints( Point( {1,0,1}), Point( {1,0,0})) == 1);
    ASSERT( distancePoints( Point( {2,2,2,2}), Point( {1,1,1,1})) == 2);
}

void plusProcheVoisinTest() {
    ASSERT( plusProcheVoisin( Point( {1,0,1}),
                              EnsemblePoints( { Point({2,3,6}), Point({1,0,0}), Point({-1,2,0})}))
        == 1);
}

/** Test du filtre SuperPixel **/
void superPixelTest() {
    // TODO: beaucoup d'étudiants ont eu 128.91
    ASSERT( ImageGrisEgal(CouleurAuGris(superPixel( imgTest, 2, 60, 15 )),
              ImageGris( {
                  {71.971, 71.971, 71.971, 71.971},
                  {71.971, 71.971, 71.971, 71.971},
                  {71.971, 71.971, 71.971, 71.971},
                  {71.971, 71.971, 71.971, 71.971}
                  }),
              0.001) );
    cout << "Vérifier que les images obtenues dans 'superpixel/' sont semblables à celles fournies dans 'superpixel/correction/'" << endl;
    ecrirePPM(superPixel(lirePPM("images/Billes.256.ppm"), 1, 30, 25),  "superpixel/Billes.256.ppm");
    ecrirePPM(superPixel(lirePPM("images/Baboon.512.ppm"), 2, 60, 15),  "superpixel/Baboon.512.ppm");
    ecrirePPM(superPixel(lirePPM("images/Lena.512.ppm"  ), 2, 60, 15),  "superpixel/Lena.512.ppm");

    cout << "Proposer des paramètres pour Embryos.512.ppm et House.256.ppm et ajouter des tests ci-dessous" << endl;
}


void KMoyenneTest(){
    EnsemblePoints P;
    for(int i=0;i<100;i++){
        double xbiais=0.;
        double ybiais=0.;
        if(i%3==1){
            xbiais = 100.;
            ybiais = 0.;
        }
        if(i%3==2){
            xbiais = 0.;
            ybiais = 100.;
        }
        Point p;
        p.push_back(xbiais + 1.*(rand()%10)-20.);
        p.push_back(ybiais + 1.*(rand()%10)-20.);
        P.push_back(p);
    }

    EnsemblePoints C = {
        {75.,50.}, {50., 75.}, {25., 25.}};

    EnsemblePoints Cout = KMoyenne(P,C,100);
    EnsemblePoints CRef = FAST_KMoyenne(P,C,100);

    for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
        ASSERT( abs( Cout[i][j] - CRef[i][j] ) <= 0.5 );
}


int main(){
    cout << "Tests de la fonction distancePoints" << endl;
    distancePointsTest();
    cout << "Tests de la fonction plusProcheVoisin" << endl;
    plusProcheVoisinTest();
    cout << "Tests de la fonction KMoyenne" << endl;
    KMoyenneTest();
    cout << "Tests de la fonction superPixel" << endl;
    superPixelTest();
}
