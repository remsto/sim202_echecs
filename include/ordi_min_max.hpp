#ifndef ORDI_MIN_MAX_HPP
#define ORDI_MIN_MAX_HPP

#include <iostream>
#include "environnement.hpp"
#include "pour_jouer.hpp"

#define inf 1000000

////
// POSITION
////

class Position
{
public:
    Echiquier plateauRef;
    ListeCoups coupsPrecedents;
    int valeurPosition = 0; // attribut, à iniialiser avec set_valeur()
    int valeurMinMax;
    Position *soeur;
    Position *fille;
    bool joueur; // qui a joule le prochain coup =is white ?
    int num_tour_de_jeu;

    Position(Echiquier &plateau, ListeCoups &coups, Position *positionSoeur, Position *positionFille, bool joueurCoup, int num_tour);
    bool estGagnante();
    int set_valeur();
    void generateur(int profondeur);
    void MinMax(bool is_white_current);


    ~Position();
};

Coup *coup_min_max(Position position, int profondeur);



#endif
