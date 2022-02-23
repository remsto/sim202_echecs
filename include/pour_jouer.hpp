#ifndef POUR_JOUER_HPP
#define POUR_JOUER_HPP

#include <iostream>
#include "environnement.hpp"

//////
// COUP
//////

class Coup
{
public:
    Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, int num_tour_de_jeu = 0, Piece *taken = NULL, bool isSpecial = false, Coup *Next = NULL, Coup *Prev = NULL, bool is_echec = false, bool is_mat = false);
    Coup(const Coup &coup);
    bool isWhite;
    Piece pieceJouee;
    // convention : 1 à N, (0,0)=hors plateau
    pair<int, int> oldPosition;
    pair<int, int> newPosition;
    Piece *Taken;
    bool isSpecial;
    Coup *Next;
    Coup *Prev;
    bool is_echec;
    bool is_mat;
    int num_tour_de_jeu;
};

ostream &operator<<(ostream &out, const Coup &coup);

bool is_coup_gagnant_TTT(const Echiquier &plateauRef, const Coup &dernierCoup);

//////
// LISTECOUPS
//////

class ListeCoups
{
public:
    int nbCoups;
    Coup *first;
    Coup *last;

    ListeCoups(int nbC, Coup *first_acopier, Coup *last_acopier);
    ListeCoups(const ListeCoups &a_copier);
    ListeCoups();
};

void addCoup(ListeCoups *L, const Coup &C);

ListeCoups *coupsPossiblesTTT(const Echiquier &plateau, bool isWhite, int num_tour);
ListeCoups *coupsPossibles(const Echiquier &plateau, bool isWhite, int num_tour);

///////
////MAJ plateau
///////

void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue);

void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);

/////
// Autre
/////

bool is_legal(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current);

Piece *taken_coup(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current);

bool is_Special(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current);

// est ce qu'on met en echec le roi ennemi
bool is_Echec(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour); // s'il met en echec le roi ennemi !

bool is_Mat(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour); // le coup met mat le roi ennemi

#endif
