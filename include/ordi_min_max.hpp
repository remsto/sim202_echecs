#ifndef ORDI_MIN_MAX_HPP
#define ORDI_MIN_MAX_HPP

#include <iostream>
#include "pour_jouer.hpp"

#define inf 1000000

////
// POSITION
////

class Position
{
public:
    Echiquier *PlateauRef;
    list<Coup> CoupsPrecedents;
    // int ValeurPosition; // attribut, à iniialiser avec set_valeur()
    int ValeurMinMax;
    Position *Soeur;
    Position *Fille;
    bool Joueur_courant; // qui a joule le prochain coup =is white ?
    int Num_tour_de_jeu;
    bool Joueur;

    Position(Echiquier *plateau, list<Coup> coups, Position *positionSoeur, Position *positionFille, bool joueur_courant, int num_tour, bool joueur, int valeur = 0);
    // bool estGagnante();
    void set_valeur(int gammap, int gammac); // si on arrive à une fille, on apelle cette fonction
    void generateur(int profondeur, int gammap = 0, int gammac = 0);
    // void MinMax(bool is_white_current);

    ~Position();
};

Coup *coup_min_max(Echiquier *EchiTTT, bool is_white_courant, int num_tour, int profondeur, int gammap = 0, int gammac = 0);

#endif
