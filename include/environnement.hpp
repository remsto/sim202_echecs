#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include <iostream>
#include <random>

using namespace std;

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

class Deplac_rel
{
public:
    pair<int, int> coor;
    Deplac_rel *Next;

    Deplac_rel(pair<int, int> coord = pair<int, int>(0, 0), Deplac_rel *next = NULL);
    Deplac_rel(const Deplac_rel &dep_a_copier);
};
ostream &operator<<(ostream &out, const Deplac_rel &dep);

class ListDeplac_rel
{
public:
    int nb_deplacement;
    Deplac_rel *first;
    Deplac_rel *last;

    ListDeplac_rel(int nbdepla = 0, Deplac_rel *first_dep = NULL, Deplac_rel *last_dep = NULL);
};

ostream &operator<<(ostream &out, const ListDeplac_rel &listDep);

class TypePiece
{
public:
    string type; // pion pour ttt
    ListDeplac_rel deplac_relatif;
    int valeur;
    TypePiece(string type = "Pion");
};

class Piece : public TypePiece
{
public:
    bool isWhite; // white=rond
    pair<int, int> position_coor;

    Piece(bool isWhit, pair<int, int> coor = pair<int, int>(0, 0), string type = "Pion");
    Piece(const Piece &piece_a_copier);
    Piece();
};
ostream &operator<<(ostream &out, const Piece &piece);

class Echiquier
{
public:
    int taille; // 3 ou 8
    Piece **plateau;
    Piece *roi_noir; // car on en a tjrs besoin (pour is_echec and co)!
    Piece *roi_blanc;

    Echiquier(int n = 8);
    ~Echiquier();
    void affiche() const;
};

int coor_to_pos(pair<int, int> p, int taillep);
pair<int, int> pos_to_coor(int n, int taillep);

ostream &operator<<(ostream &out, const pair<int, int> &pair);

//////
// ALEA
//////

int tirage_alea_entier(int min, int max);

/////
// Echecs
/////

void mise_en_place_echec_piece(Echiquier &EchiTTT);
pair<int, int> operator+(pair<int, int> p1, pair<int, int> p2);

#endif