#include <iostream>
using namespace std;
#include "algorithme_min_max.hpp"



Position::Position(Echiquier& plateau, Coup& coups, Position* positionSoeur, Position* positionFille, bool joueurCoup){
    plateauRef=plateau;
    joueur=joueurCoup;
    soeur=positionSoeur;
    fille=positionFille;
    coupsPrecedents=coups;
    valeurPosition=valeurPosition(); // à réfléchir
}

Position::~Position(){
    delete [] coupsPrecedents;
}

int Position::valeurPosition(){
    if estGagnante(joueur){
        return inf;
    }
}

bool Position::estGagnante(){

    //Coup dernierCoup = coupsPrecedents
    //while(coupsPrecedents[i]!=)
}


Coup::Coup(bool isW, Piece& pieceJ, pair<int,int>& newP, pair<int,int>& oldP, bool isTaken=False, bool isSpecial=False){}