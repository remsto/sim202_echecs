#ifndef POUR_JOUER_HPP
#define POUR_JOUER_HPP

#include <iostream>
#include <string>
#include "environnement.hpp"

//////
// LISTECOUPS
//////

ostream &operator<<(ostream &out, const list<Coup> &Listcoup);

void addCoup(list<Coup> &L, const Coup &C);

list<Coup> coupsPossiblesTTT(const Echiquier &plateau, bool isWhite, int num_tour);
list<Coup> coupsPossibles(Echiquier &plateau, bool isWhite, int num_tour);
bool is_coupsPossiblesTTT(Echiquier &plateau, bool isWhite, int num_tour);
bool is_coupsPossibles(Echiquier &plateau, bool isWhite, int num_tour);
///////
////MAJ plateau
///////

void actualise_type(Piece &piece, string new_type);

void actualisePlateau(Echiquier &plateau, const list<Coup> &coupsPrecedents);
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue);

void resetPlateau(Echiquier &plateau, const list<Coup> &coupsPrecedents);
void resetPlateau(Echiquier &plateau, const Coup &coup_jouee);

/////
// Autre
/////

bool is_legal(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, CoupSpecial coup_special, string type_promu);

bool is_piece_entre(const Echiquier &plateau, pair<int, int> place_depart, pair<int, int> place_arrive);

Piece *taken_coup(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, CoupSpecial coup_special);

CoupSpecial Special(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour);

// est ce qu'on met en echec le roi ennemi ou le notre
bool is_Echec(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, bool couleur_roi_en_echec, string type_promu, CoupSpecial coup_special); // s'il met en echec le roi ennemi !

bool is_Mat(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, string type_promu, CoupSpecial coup_special, bool is_ech); // le coup met mat le roi ennemi

#endif
