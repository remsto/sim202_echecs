#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP
using namespace std;
#include <vector>
#include <iostream>

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

class TypePiece
{
public:
    string type; // pion pour ttt
    vector<pair<int, int>> deplac_relatif;
    int valeur;
    TypePiece(string type = "Pion");
};

class Piece : public TypePiece
{
public:
    bool isWhite; // white=rond
    pair<int, int> position_coor;
    Piece(bool isWhit, pair<int, int> coor, string type = "Pion");
};

class Echiquier
{
public:
    int taille; // 3 ou 8
    Piece **plateau;
    Echiquier(int n);
    ~Echiquier();
    void affiche3() const;
};

/*
CLASSE ET FONCTIONS  TTT
*/

int coor_to_pos_TTT(pair<int, int> p);
pair<int, int> pos_to_coor_TTT(int n);

/*
CLASSE ET FONCTIONS ECHECS
*/

int coor_to_pos(pair<int, int> p);
pair<int, int> pos_to_coor(int n);

#endif