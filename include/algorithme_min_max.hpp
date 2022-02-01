#ifndef ALGORITHME_MIN_MAX_HPP
#define ALGORITHME_MIN_MAX_HPP
#include <iostream>


class Position 
{
public:
    Plateau plateauRef; // classe Plateau à implémenter
    Coup* coupsPrecedents; // classe Coup à implémenter
    int valeurPosition();
    Position* soeur;
    Position* fille;
    bool joueur;
    void generateur(int profondeur);
};

class Plateau {

};

#endif