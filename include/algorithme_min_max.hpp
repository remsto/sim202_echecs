#ifndef ALGORITHME_MIN_MAX_HPP
#define ALGORITHME_MIN_MAX_HPP
#include <iostream>
#define inf = 1000000

////
// POSITION
////

class Position
{
public:
    Position(Echiquier &plateau, ListeCoups &coups, Position *positionSoeur, Position *positionFille, bool joueurCoup);
    Echiquier plateauRef;       // classe Plateau à implémenter
    ListeCoups coupsPrecedents; // classe Coup à implémenter
    int valeurPosition = 0;     // attribut, à iniialiser avec valeurPosition()
    Position *soeur;
    Position *fille;
    bool joueur;

    bool estGagnante();
    int calculeValeurPosition();
    void generateur(int profondeur);
    ~Position();
};

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

void addCoup(ListeCoups &L, const Coup &C);

ListeCoups coupsPossiblesTTT(Echiquier plateau, bool isWhite);

////

void actualisePlateau(Echiquier plateau, ListeCoups coupsPrecedents);

void resetPlateau(Echiquier plateau, ListeCoups coupsPrecedents);

#endif
