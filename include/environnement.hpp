#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP
using namespace std;
#include <vector>
#include <iostream>
#define taillep 3

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

    Piece(bool isWhit, pair<int, int> coor = pair<int, int>(0, 0), string type = "Pion");
    Piece();
};
ostream &operator<<(ostream &out, const Piece &piece);

class Echiquier
{
public:
    int taille; // 3 ou 8
    Piece **plateau;
    Echiquier(int n = 8);
    ~Echiquier();
    void affiche() const;
};

int coor_to_pos(pair<int, int> p);
pair<int, int> pos_to_coor(int n);

ostream &operator<<(ostream &out, const pair<int, int> &pair);

#endif