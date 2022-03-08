#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include <iostream>
#include <random>
#include <utility>
#include <string>


/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

class Deplac_rel
{
public:
    std::pair<int, int> coor;
    Deplac_rel *Next;

    Deplac_rel(std::pair<int, int> coord = std::pair<int, int>(0, 0), Deplac_rel *next = NULL);
    Deplac_rel(const Deplac_rel &dep_a_copier);
    ~Deplac_rel();
};

std::ostream &operator<<(std::ostream &out, const Deplac_rel &dep);

class ListDeplac_rel
{
public:
    int nb_deplacement;
    Deplac_rel *first;
    Deplac_rel *last;

    ListDeplac_rel(int nbdepla = 0, Deplac_rel *first_dep = NULL, Deplac_rel *last_dep = NULL);
    ~ListDeplac_rel();
};

std::ostream &operator<<(std::ostream &out, const ListDeplac_rel &listDep);

class TypePiece
{
public:
    std::string type; // pion pour ttt
    ListDeplac_rel deplac_relatif;
    int valeur;
    TypePiece(std::string type = "Pion");
};

class Piece : public TypePiece
{
public:
    bool isWhite; // white=rond
    std::pair<int, int> position_coor;

    Piece(bool isWhit = true, std::pair<int, int> coor = std::pair<int, int>(0, 0), std::string type = "Pion");
    Piece(const Piece &piece_a_copier);
};

std::ostream &operator<<(std::ostream &out, const Piece &piece);

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

int coor_to_pos(std::pair<int, int> p, int taillep);
std::pair<int, int> pos_to_coor(int n, int taillep);

std::ostream &operator<<(std::ostream &out, const std::pair<int, int> &pair);

//////
// ALEA
//////

int tirage_alea_entier(int min, int max);

/////
// Echecs
/////

void mise_en_place_echec_piece(Echiquier &EchiTTT);
std::pair<int, int> operator+(std::pair<int, int> p1, std::pair<int, int> p2);
std::pair<int, int> operator-(std::pair<int, int> p1, std::pair<int, int> p2);
#endif