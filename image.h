#include <stdexcept>
#include <vector>
using namespace std;

/** @file
 ** Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H
    struct Couleur
	{
		/** Intensite de rouge**/
		double r;
		/** Intensite de vert**/
		double g;
		/** Intensite de bleu**/
		double b;
	};
#endif

typedef vector<vector<int> > ImageNB;
typedef vector<vector<double> > ImageGris;
typedef vector<vector<Couleur> > Image;