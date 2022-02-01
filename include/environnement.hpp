#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP
using namespace std;
#include <vector>
#include <iostream>


/* 
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

class TypePiece 
{ public :
    string type; //pion pour ttt
    vector<pair<int,int>> deplac_relatif;
    int valeur;
    TypePiece(string type="Pion");
};

class Piece : public TypePiece 
{ public :
    bool isWhite; //white=rond
    pair<int,int> position_coor;
};


class Echiquier 
{public :
    int taille; // 3 ou 8
    Piece** plateau; 
    void affiche() const; 
};




#endif