#ifndef ALGORITHME_MIN_MAX_HPP
#define ALGORITHME_MIN_MAX_HPP
#include <iostream>
#define inf=1000000


class Position 
{
public:
    Position(Echiquier& plateau, ListeCoups& coups, Position* positionSoeur, Position* positionFille, bool joueurCoup);
    Echiquier plateauRef; // classe Plateau à implémenter
    ListeCoup* coupsPrecedents; // classe Coup à implémenter
    int valeurPosition = 0; // attribut, à iniialiser avec valeurPosition()
    Position* soeur;
    Position* fille;
    bool joueur;

    bool estGagnante();
    int valeurPosition();
    void generateur(int profondeur);
    ~Position();
};

class Coup
{
public:
    Coup(bool isW, Piece& pieceJ, pair<int,int>& newP, pair<int,int>& oldP, bool isTaken=False, bool isSpecial=False);
    bool isWhite;
    Piece pieceJouee;
    // convention : 1 à N, (0,0)=hors plateau
    pair<int,int> oldPosition;
    pair<int,int> newPosition;
    bool isTaken;
    bool isSpecial;
    Coup* Next;
    Coup* Prev;
};

class ListeCoups{
public:
    int nbCoups;
    Coup∗ first; 
    Coup∗ last ;

    ListeCoups(int nbC, ) // Constructeur à faire
}

#endif