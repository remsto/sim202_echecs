#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include <iostream>
#include <random>
#include <list>
#include <algorithm>
#include <string>

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

class Deplac_rel
{
public:
    pair<int, int> coor;

    Deplac_rel(pair<int, int> coord = pair<int, int>(0, 0));
    Deplac_rel(const Deplac_rel &dep_a_copier);
    ~Deplac_rel(){};
};

ostream &operator<<(ostream &out, const Deplac_rel &dep);

ostream &operator<<(ostream &out, const list<Deplac_rel> &listDep);

class TypePiece
{
public:
    string type; // pion pour ttt
    list<Deplac_rel> deplac_relatif;
    int valeur;
    TypePiece(string typee = "Pion");
    ~TypePiece(){};
};

class Piece : public TypePiece
{
public:
    bool isWhite; // white=rond
    int a_bouge;
    pair<int, int> position_coor;

    Piece(bool isWhit = true, int a_bouge = 0, pair<int, int> coor = pair<int, int>(0, 0), string typee = "Pion");
    Piece(const Piece &piece_a_copier);
    ~Piece(){};
};

std::ostream &operator<<(std::ostream &out, const Piece &piece);

//////
// COUP
//////

enum CoupSpecial
{
    non_special,
    petit_roque,
    grand_roque,
    promotion,
    prise_en_passant
};

class Coup
{
public:
    bool isWhite;
    Piece pieceJouee;
    // convention : 1 à N, (0,0)=hors plateau
    pair<int, int> oldPosition;
    pair<int, int> newPosition;
    Piece *Taken;
    CoupSpecial Coup_special;
    string Type_Promu;
    bool is_echec;
    bool is_mat;
    int num_tour_de_jeu;

    Coup(bool isW = true, const Piece &pieceJ = Piece(), pair<int, int> newP = pair<int, int>(0, 0), pair<int, int> oldP = pair<int, int>(0, 0), int num_tour_de_jeu = 0, Piece *taken = NULL, CoupSpecial coup_special = non_special, string type_promu = "Pion", bool is_echec = false, bool is_mat = false);
    Coup(const Coup &coup);
    ~Coup();
};

ostream &operator<<(ostream &out, const Coup &coup);

class Echiquier
{
public:
    int taille; // 3 ou 8
    Piece **plateau;
    Piece *roi_noir; // car on en a tjrs besoin (pour is_echec and co)!
    Piece *roi_blanc;

    list<Coup> L_coup_depuis_dep;

    Echiquier(int n = 8);
    ~Echiquier();
    void affiche() const;
};

int coor_to_pos(std::pair<int, int> p, int taillep);
std::pair<int, int> pos_to_coor(int n, int taillep);

std::ostream &operator<<(std::ostream &out, const std::pair<int, int> &pair);

bool is_coup_gagnant_TTT(const Echiquier &plateauRef, bool couleur, const pair<int, int> &coor);

//////
// ALEA
//////

int tirage_alea_entier(int min, int max);

/////
// Echecs
/////

void mise_en_place_echec_piece(Echiquier &EchiTTT);
pair<int, int> operator+(pair<int, int> p1, pair<int, int> p2);
pair<int, int> operator-(pair<int, int> p1, pair<int, int> p2);

ostream &operator<<(ostream &out, const list<pair<int, float>> &pair);

#endif