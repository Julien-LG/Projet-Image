#include <stdexcept>
/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Une image 4x4 pour faire des tests **/
Image imgTest = {
    { Couleur({0,0,0}), Couleur({255,255,255}), Couleur({255,0,0}), Couleur({255,255,0}) },
    { Couleur({0,0,255}), Couleur({0,255,0}), Couleur({0,255,255}), Couleur({120,120,120}) },
    { Couleur({42,174,86}), Couleur({141,194,57}), Couleur({68,107,43}), Couleur({73, 98, 40}) },
    { Couleur({60, 196, 74}), Couleur({141,194,57}), Couleur({61,102,43}), Couleur({214,38,102}) }
};

/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};
