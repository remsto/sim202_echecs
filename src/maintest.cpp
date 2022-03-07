
#include "ordi_aleatoire.hpp"
#include <iostream>
#include <random>
#include "ordi_min_max.hpp"
#include "pour_jouer.hpp"
using namespace std;
#define taillepp 8

int main()
{
    Piece *piec_test = new Piece(true, pair<int, int>(1, 1), "Cavalier");
    char premiere_lettre = piec_test->type[0];
    cout << premiere_lettre;

    Echiquier *Echiq = new Echiquier(3);
    ListeCoups listdemerde = ListeCoups(0,NULL,NULL);
    Position position = Position(*Echiq, listdemerde, NULL, NULL, true, 0);

    pair<int,int> coord = pair<int,int>(1,1);
    Piece pieece = Piece(true, coord, "Dame");
    Coup yepa = Coup(true,pieece,pair<3,4>,coord);

    //position.generateur(2);
    position.plateauRef.affiche();

    actualisePlateau(*Echiq, listdemerde);

    resetPlateau(*Echiq, listdemerde);

}