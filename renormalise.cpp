#include <stdexcept>
/** @file
 * Petit programme appliquant le filtre de renormalisation à un fichier PGM
 **/

#include <iostream>
#include "image.h"
#include "pgm.h"
#include "seuillage.h"

using namespace std;

/** Fonction principale **/
int main(int argc, char ** argv) {
    if (argc != 3) {
        cerr << "Utilisation: renormalize source.pgm destination.pgm\n";
        return -1;
    }
    string source = argv[1];
    string destination = argv[2];
    ecrirePGM(renormalise(lirePGM(source)), destination);
    return 0;
}
