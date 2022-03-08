#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
#include "ordi_min_max.hpp"
#include "pour_jouer.hpp"
using namespace std;
#define taillepp 8

int main()
{
    Echiquier echiq(3);
    pair<int, int> newP = pair<int,int>(1,1);
    pair<int, int> oldP = pair<int,int>(0,0);

    Coup *coup = new Coup(true, NULL, newP, oldP, 0, NULL, false, NULL, NULL, false, false);
    ListeCoups Lcoups(1, coup, coup);
    //echiq.affiche();
    actualisePlateau(echiq, Lcoups);
    //echiq.affiche();
    resetPlateau(echiq, Lcoups);
    //echiq.affiche();
    cout << Lcoups; 
    Position TTT(echiq, Lcoups, NULL, NULL, false, 0);
    //TTT.generation(2);
}