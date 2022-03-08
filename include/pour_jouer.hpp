#ifndef POUR_JOUER_HPP
#define POUR_JOUER_HPP

#include "environnement.hpp"

//////
// COUP
//////

class Coup
{
public:
    Coup(bool isW, const Piece &pieceJ, std::pair<int, int> newP, std::pair<int, int> oldP, int num_tour_de_jeu = 0, Piece *taken = NULL, bool isSpecial = false, Coup *Next = NULL, Coup *Prev = NULL, bool is_echec = false, bool is_mat = false);
    Coup(const Coup &coup);
    bool isWhite;
    Piece pieceJouee;
    // convention : 1 à N, (0,0)=hors plateau
    std::pair<int, int> oldPosition;
    std::pair<int, int> newPosition;
    Piece *Taken;
    bool isSpecial;
    Coup *Next;
    Coup *Prev;
    bool is_echec;
    bool is_mat;
    int num_tour_de_jeu;
    ~Coup();
};

std::ostream &operator<<(std::ostream &out, const Coup &coup);

bool is_coup_gagnant_TTT(const Echiquier &plateauRef, const Coup &dernierCoup);

//////
// LISTECOUPS
//////

class ListeCoups
{
public:
    int nbCoups;
    Coup *first;
    Coup *last;

    ListeCoups(int nbC, Coup *first_acopier, Coup *last_acopier);
    ListeCoups(const ListeCoups &a_copier);
    ListeCoups();
    ~ListeCoups();
};

std::ostream &operator<<(std::ostream &out, const ListeCoups &Listcoup);

void addCoup(ListeCoups *L, Coup *C);

ListeCoups *coupsPossiblesTTT(const Echiquier &plateau, bool isWhite, int num_tour);
ListeCoups *coupsPossibles(Echiquier &plateau, bool isWhite, int num_tour);

///////
////MAJ plateau
///////

void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue);

void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents);
void resetPlateau(Echiquier &plateau, const ListeCoups &coup_jouee);

/////
// Autre
/////

bool is_legal(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour);
bool is_piece_entre(const Echiquier &plateau, std::pair<int, int> place_depart, std::pair<int, int> place_arrive);

Piece *taken_coup(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour);

bool is_Special(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current);

// est ce qu'on met en echec le roi ennemi ou le notre
bool is_Echec(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour, bool couleur_roi_en_echec); // s'il met en echec le roi ennemi !

bool is_Mat(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour); // le coup met mat le roi ennemi

#endif
