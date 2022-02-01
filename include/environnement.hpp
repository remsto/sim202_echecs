#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP
using namespace std;
#include <vector>
#include <iostream>


class TypePiece 
{ public :
    char* Type; //pion pour ttt
    vector<pair<int,int>> deplac_rel;
    int valeur;
};

class TypePiece : public Piece 
{ public :
    bool isWhite; //white=rond
    

}




#endif