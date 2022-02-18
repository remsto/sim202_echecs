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
    Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, bool isTaken = false, bool isSpecial = false, Coup *Next = NULL, Coup *Prev = NULL);
    Coup(const Coup &coup);
    bool isWhite;
    Piece pieceJouee;
    // convention : 1 à N, (0,0)=hors plateau
    pair<int, int> oldPosition;
    pair<int, int> newPosition;
    bool isTaken;
    bool isSpecial;
    Coup *Next;
    Coup *Prev;
};

ostream &operator<<(ostream &out, const Coup &coup);
bool is_coup_gagnant(const Echiquier &plateauRef, const Coup &dernierCoup);

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

ListeCoups *coupsPossiblesTTT(const Echiquier &plateau, bool isWhite);

///////
////MAJ plateau
///////

void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue);

void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);

#endif
