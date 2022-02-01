#ifndef ALGORITHME_MIN_MAX_HPP
#define ALGORITHME_MIN_MAX_HPP
#include <iostream>


class Position 
{
public:

    int valeurPosition();
    Position* soeur;
    Position* fille;
    int n;
    bool joueur;
    void generateur(int profondeur);
};

class Plateau {

};

#endif