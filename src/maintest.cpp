#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
#include <iostream>
#include <random>
using namespace std;
#define taillepp 8

int main()
{
    bool is_fini = false;
    Echiquier *Echi = new Echiquier(taillepp);
    int taillep = Echi->taille;
    int num_tour = 0;

    bool is_coups_correct;
    int joueur_courant;
    bool is_tour_joueur1;
    bool is_white_1;
    bool is_white_courant;

    Coup *coupjoue;
    Piece *piece_jouee;
    Deplac_rel *dep;

    // mise en place des pièces
    mise_en_place_echec_piece(*Echi);

    Echi->plateau[coor_to_pos(pair<int, int>(5, 5), taillep)] = Echi->plateau[coor_to_pos(pair<int, int>(7, 5), taillep)];
    Echi->plateau[coor_to_pos(pair<int, int>(5, 5), taillep)]->position_coor = pair<int, int>(5, 5);
    Echi->plateau[coor_to_pos(pair<int, int>(7, 5), taillep)] = NULL;

    Echi->plateau[coor_to_pos(pair<int, int>(4, 5), taillep)] = Echi->plateau[coor_to_pos(pair<int, int>(2, 5), taillep)];
    Echi->plateau[coor_to_pos(pair<int, int>(4, 5), taillep)]->position_coor = pair<int, int>(4, 5);
    Echi->plateau[coor_to_pos(pair<int, int>(2, 5), taillep)] = NULL;

    Echi->plateau[coor_to_pos(pair<int, int>(4, 3), taillep)] = Echi->plateau[coor_to_pos(pair<int, int>(1, 6), taillep)];
    Echi->plateau[coor_to_pos(pair<int, int>(4, 3), taillep)]->position_coor = pair<int, int>(4, 3);
    Echi->plateau[coor_to_pos(pair<int, int>(1, 6), taillep)] = NULL;

    Echi->plateau[coor_to_pos(pair<int, int>(5, 8), taillep)] = Echi->plateau[coor_to_pos(pair<int, int>(1, 4), taillep)];
    Echi->plateau[coor_to_pos(pair<int, int>(5, 8), taillep)]->position_coor = pair<int, int>(5, 8);
    Echi->plateau[coor_to_pos(pair<int, int>(1, 4), taillep)] = NULL;

    Echi->affiche();

    Piece *piece_joue = Echi->plateau[coor_to_pos(pair<int, int>(5, 8), taillep)];

    Deplac_rel *dep_dame = new Deplac_rel(pair<int, int>(2, -2));
    string promu("Pion");
    bool is_ech = is_Echec(*Echi, piece_joue, *dep_dame, 4, false, promu, non_special);
    cout << is_ech << endl;
    bool is_ma = is_Mat(*Echi, piece_joue, *dep_dame, 4, promu, non_special, is_ech);
    cout << endl
         << is_ma;
    return 0;
}