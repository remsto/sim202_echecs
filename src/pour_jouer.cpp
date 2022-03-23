#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
#include "pour_jouer.hpp"

//////
// LISTECOUPS
//////

ostream &operator<<(ostream &out, const list<Coup> &listcoup)
{
    list<Coup>::const_iterator it = listcoup.begin();
    while (it != listcoup.end())
    {
        it->isWhite ? out << "|" << it->num_tour_de_jeu << "." : out << "";
        out << " ";
        out << *it;
        out << (it->isWhite ? "" : "\n");

        it++;
    }
    return out;
}

void addCoup(list<Coup> &L, const Coup &C)
{
    L.push_back(C);
}

// pour TTT
list<Coup> coupsPossiblesTTT(const Echiquier &plateau, bool isWhite, int num_tour) // est-ce au joueur blanc de jouer ?
{
    int taillep = plateau.taille;

    list<Coup> list_coup;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)] == NULL)
            {
                bool is_mat = is_coup_gagnant_TTT(plateau, isWhite, pair<int, int>(i, j));

                Coup coup_joue(isWhite, Piece(isWhite), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour, NULL, non_special, "Pion", false, is_mat);
                list_coup.push_back(coup_joue);
            }
        }
    }
    /// faut il faire un new ici ?
    return list_coup;
}

list<Coup> coupsPossibles(Echiquier &plateau, bool isWhit, int num_tour)
{
    int taillep = plateau.taille;
    int pour_boucle_prom;
    list<Coup> list_coup;

    // on parcour le plateau
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            // cout << "etape 1";
            int pos_piece = coor_to_pos(pair<int, int>(i, j), taillep);
            Piece *piece_a_jouer = plateau.plateau[pos_piece];
            if ((piece_a_jouer != NULL) && (piece_a_jouer->isWhite == isWhit))
            {
                //  on parcourt ses déplacements possible, si il est légal on l'ajoute.
                list<Deplac_rel> dep_piece = piece_a_jouer->deplac_relatif;
                list<Deplac_rel>::iterator it = dep_piece.begin();

                while (it != dep_piece.end())
                {
                    CoupSpecial coup_special = Special(plateau, piece_a_jouer, *it, num_tour);
                    pour_boucle_prom = 1;
                    if (coup_special != promotion)
                        pour_boucle_prom = 5;

                    string type_promu;

                    while (pour_boucle_prom <= 5)
                    {
                        if (pour_boucle_prom == 1)
                            type_promu = "Dame";
                        else if (pour_boucle_prom == 2)
                            type_promu = "Tour";
                        else if (pour_boucle_prom == 3)
                            type_promu = "Fou";
                        else if (pour_boucle_prom == 4)
                            type_promu = "Cavalier";
                        else if (pour_boucle_prom == 5)
                            type_promu = "Pion";

                        if ((is_legal(plateau, piece_a_jouer, *it, num_tour, coup_special, type_promu)))
                        {
                            if ((!is_Echec(plateau, piece_a_jouer, *it, num_tour, isWhit, type_promu, coup_special)))
                            {

                                Piece *taken = taken_coup(plateau, piece_a_jouer, *it, coup_special);

                                bool is_ech = is_Echec(plateau, piece_a_jouer, *it, num_tour, !isWhit, type_promu, coup_special);
                                bool is_mat = is_Mat(plateau, piece_a_jouer, *it, num_tour, type_promu, coup_special, is_ech);
                                piece_a_jouer = plateau.plateau[pos_piece];
                                Coup coup_joue(isWhit, *piece_a_jouer, it->coor + piece_a_jouer->position_coor, piece_a_jouer->position_coor, num_tour, taken, coup_special, type_promu, is_ech, is_mat);
                                list_coup.push_back(coup_joue);
                            }
                        }
                        pour_boucle_prom += 1;
                    }
                    it++;
                }
            }
        }
    }

    return list_coup;
}

bool is_coupsPossiblesTTT(Echiquier &plateau, bool isWhit, int num_tour)
{
    int taillep = plateau.taille;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)] == NULL)
            {
                return true;
            }
        }
    }
    /// faut il faire un new ici ?
    return false;
}

bool is_coupsPossibles(Echiquier &plateau, bool isWhit, int num_tour)
{
    int taillep = plateau.taille;

    // on parcour le plateau
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            Piece *piece_a_jouer1 = plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];

            if ((piece_a_jouer1 != NULL) && (piece_a_jouer1->isWhite == isWhit))
            {
                list<Deplac_rel> dep_piece = piece_a_jouer1->deplac_relatif;

                list<Deplac_rel>::iterator dep_current = dep_piece.begin();
                string type_promu("Pion");
                // on parcourt ses déplacements possible, si il est légal on retourne true.

                while (dep_current != dep_piece.end())
                {
                    CoupSpecial coup_special = Special(plateau, piece_a_jouer1, *dep_current, num_tour);
                    if (coup_special == promotion)
                        type_promu = string("Tour");
                    bool is_leg = is_legal(plateau, piece_a_jouer1, *dep_current, num_tour, coup_special, type_promu);
                    if (is_leg)
                    {
                        bool is_ech = is_Echec(plateau, piece_a_jouer1, *dep_current, num_tour, isWhit, type_promu, coup_special);
                        if (!is_ech)
                        {
                            return true;
                        }
                    }
                    dep_current++;
                }
            }
        }
    }
    return false;
}

///////
////MAJ plateau
///////

void actualise_type(Piece &piece, string new_type)
{
    piece.type = new_type;

    if (new_type == "Pion")
    {
        piece.valeur = 1;
        list<Deplac_rel> list_dep;
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, 0)));

        piece.deplac_relatif = list_dep;
    }

    else if (new_type == "Tour")
    {
        piece.valeur = 5;

        list<Deplac_rel> list_dep;

        for (int i = 1; i <= 7; i++)
        {
            list_dep.push_back(Deplac_rel(pair<int, int>(i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, -i)));
        }
        piece.deplac_relatif = list_dep;
    }

    else if (new_type == "Cavalier")
    {
        piece.valeur = 3;

        list<Deplac_rel> list_dep;

        list_dep.push_back(Deplac_rel(pair<int, int>(-1, -2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, -2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, 1)));

        piece.deplac_relatif = list_dep;
    }

    else if (new_type == "Fou")
    {
        piece.valeur = 3;

        list<Deplac_rel> list_dep;

        for (int i = 1; i <= 7; i++)
        {
            list_dep.push_back(Deplac_rel(pair<int, int>(i, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, i)));
        }
        piece.deplac_relatif = list_dep;
    }
    else if (new_type == "Roi")
    {
        piece.valeur = 100; // arbitraire, à réfléchir
        list<Deplac_rel> list_dep;

        list_dep.push_back(Deplac_rel(pair<int, int>(-1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(0, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(0, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(0, 2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(0, -2)));

        piece.deplac_relatif = list_dep;
    }
    else if (new_type == "Dame")
    {
        piece.valeur = 9;

        list<Deplac_rel> list_dep;

        for (int i = 1; i <= 7; i++)
        {
            // colonnes et lignes
            list_dep.push_back(Deplac_rel(pair<int, int>(i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, -i)));

            // diagonales
            list_dep.push_back(Deplac_rel(pair<int, int>(i, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, i)));
        }
        piece.deplac_relatif = list_dep;
    }
    else
    {
        piece.valeur = 1;
        list<Deplac_rel> list_dep;
        piece.deplac_relatif = list_dep;
    }
}

void actualisePlateau(Echiquier &plateau, const list<Coup> &coupsPrecedents)
{
    if (!coupsPrecedents.empty())
    {
        list<Coup>::const_iterator coupjoue = coupsPrecedents.begin();
        int taillep = plateau.taille;

        while (coupjoue != coupsPrecedents.end())
        {
            pair<int, int> old = coupjoue->oldPosition;
            pair<int, int> news = coupjoue->newPosition;
            bool is_prise = (coupjoue->Taken != NULL);
            CoupSpecial coup_special = coupjoue->Coup_special;

            if (taillep == 3) // si tictactoe
            {
                Piece *new_piece = new Piece(coupjoue->pieceJouee); // on doit créer la pièce ?
                new_piece->position_coor = news;
                plateau.plateau[coor_to_pos(news, taillep)] = new_piece;
            }
            else // si on joue aux echecs
            {
                Piece *old_piece = plateau.plateau[coor_to_pos(old, taillep)];
                plateau.plateau[coor_to_pos(old, taillep)] = NULL;

                if (coup_special == petit_roque)
                {
                    old_piece->position_coor = news;
                    old_piece->a_bouge += 1;
                    plateau.plateau[coor_to_pos(news, taillep)] = old_piece;

                    pair<int, int> place_tour_old(old.first, 8);
                    Piece *old_piece_tour = plateau.plateau[coor_to_pos(place_tour_old, taillep)];
                    plateau.plateau[coor_to_pos(place_tour_old, taillep)] = NULL;
                    pair<int, int> new_place_tour = place_tour_old + pair<int, int>(0, -2);
                    old_piece_tour->position_coor = new_place_tour;
                    old_piece_tour->a_bouge += 1;
                    plateau.plateau[coor_to_pos(new_place_tour, taillep)] = old_piece_tour;
                }
                else if (coup_special == grand_roque)
                {
                    old_piece->position_coor = news;
                    old_piece->a_bouge += 1;
                    plateau.plateau[coor_to_pos(news, taillep)] = old_piece;

                    pair<int, int> place_tour_old(old.first, 1);
                    Piece *old_piece_tour = plateau.plateau[coor_to_pos(place_tour_old, taillep)];
                    plateau.plateau[coor_to_pos(place_tour_old, taillep)] = NULL;
                    pair<int, int> new_place_tour = place_tour_old + pair<int, int>(0, 3);
                    old_piece_tour->position_coor = new_place_tour;
                    old_piece_tour->a_bouge += 1;
                    plateau.plateau[coor_to_pos(new_place_tour, taillep)] = old_piece_tour;
                }
                else if (coup_special == prise_en_passant)
                {
                    old_piece->position_coor = news;
                    old_piece->a_bouge += 1;
                    plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
                    pair<int, int> place_prise(old.first, news.second);
                    delete plateau.plateau[coor_to_pos(place_prise, taillep)];
                    plateau.plateau[coor_to_pos(place_prise, taillep)] = NULL;
                }
                else if (coup_special == promotion)
                {
                    if (is_prise)
                    {
                        delete plateau.plateau[coor_to_pos(news, taillep)];
                        plateau.plateau[coor_to_pos(news, taillep)] = NULL;
                    }
                    old_piece->position_coor = news;
                    old_piece->a_bouge += 1;
                    string new_type = coupjoue->Type_Promu;
                    actualise_type(*old_piece, new_type);
                    plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
                }
                else // non_special
                {
                    if (is_prise)
                    {
                        delete plateau.plateau[coor_to_pos(news, taillep)];
                        plateau.plateau[coor_to_pos(news, taillep)] = NULL;
                    }
                    old_piece->position_coor = news;
                    old_piece->a_bouge += 1;
                    plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
                }

                addCoup(plateau.L_coup_depuis_dep, *coupjoue);
            }

            coupjoue++;
        }
    }
}

// quand on a qu'un coup à faire ! + actualise la pièce
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue)
{
    int taillep = plateau.taille;
    pair<int, int> old = coupjoue.oldPosition;
    pair<int, int> news = coupjoue.newPosition;
    bool is_prise = (coupjoue.Taken != NULL);
    CoupSpecial coup_special = coupjoue.Coup_special;

    if (taillep == 3) // si tictactoe
    {
        Piece *new_piece = new Piece(coupjoue.pieceJouee); // on doit créer la pièce ?
        new_piece->position_coor = news;
        plateau.plateau[coor_to_pos(news, taillep)] = new_piece;
    }
    else // si on joue aux echecs
    {
        Piece *old_piece = plateau.plateau[coor_to_pos(old, taillep)];
        plateau.plateau[coor_to_pos(old, taillep)] = NULL;

        if (coup_special == petit_roque)
        {
            old_piece->position_coor = news;
            old_piece->a_bouge += 1;
            plateau.plateau[coor_to_pos(news, taillep)] = old_piece;

            pair<int, int> place_tour_old(old.first, 8);
            Piece *old_piece_tour = plateau.plateau[coor_to_pos(place_tour_old, taillep)];
            plateau.plateau[coor_to_pos(place_tour_old, taillep)] = NULL;
            pair<int, int> new_place_tour = place_tour_old + pair<int, int>(0, -2);
            old_piece_tour->position_coor = new_place_tour;
            old_piece_tour->a_bouge += 1;
            plateau.plateau[coor_to_pos(new_place_tour, taillep)] = old_piece_tour;
        }
        else if (coup_special == grand_roque)
        {
            old_piece->position_coor = news;
            old_piece->a_bouge += 1;
            plateau.plateau[coor_to_pos(news, taillep)] = old_piece;

            pair<int, int> place_tour_old(old.first, 1);
            Piece *old_piece_tour = plateau.plateau[coor_to_pos(place_tour_old, taillep)];
            plateau.plateau[coor_to_pos(place_tour_old, taillep)] = NULL;
            pair<int, int> new_place_tour = place_tour_old + pair<int, int>(0, 3);
            old_piece_tour->position_coor = new_place_tour;
            old_piece_tour->a_bouge += 1;
            plateau.plateau[coor_to_pos(new_place_tour, taillep)] = old_piece_tour;
        }
        else if (coup_special == prise_en_passant)
        {
            old_piece->position_coor = news;
            old_piece->a_bouge += 1;
            plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
            pair<int, int> place_prise(old.first, news.second);
            delete plateau.plateau[coor_to_pos(place_prise, taillep)];
            plateau.plateau[coor_to_pos(place_prise, taillep)] = NULL;
        }
        else if (coup_special == promotion)
        {
            if (is_prise)
            {
                delete plateau.plateau[coor_to_pos(news, taillep)];
                plateau.plateau[coor_to_pos(news, taillep)] = NULL;
            }
            old_piece->position_coor = news;
            old_piece->a_bouge += 1;
            string new_type = coupjoue.Type_Promu;
            actualise_type(*old_piece, new_type);
            plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
        }
        else // non_special
        {
            if (is_prise)
            {
                delete plateau.plateau[coor_to_pos(news, taillep)];
                plateau.plateau[coor_to_pos(news, taillep)] = NULL;
            }
            old_piece->position_coor = news;
            old_piece->a_bouge += 1;
            plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
        }

        addCoup(plateau.L_coup_depuis_dep, coupjoue);
    }
}

void resetPlateau(Echiquier &plateau, const list<Coup> &coupsPrecedents)
{
    if (!coupsPrecedents.empty())
    {
        list<Coup>::const_reverse_iterator coup_jouee = coupsPrecedents.rbegin();
        int taillep = plateau.taille;

        while (coup_jouee != coupsPrecedents.rend())
        {
            pair<int, int> old = coup_jouee->oldPosition;
            pair<int, int> news = coup_jouee->newPosition;
            Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)];
            Piece *piece_prise = coup_jouee->Taken;
            CoupSpecial coup_special = coup_jouee->Coup_special;

            if (taillep == 3) // si tictactoe
            {
                delete plateau.plateau[coor_to_pos(news, taillep)]; // on doit supprimer la pièce !
                plateau.plateau[coor_to_pos(news, taillep)] = NULL;
            }
            else // si on joue aux echecs !
            {
                plateau.plateau[coor_to_pos(news, taillep)] = NULL;
                new_piece->position_coor = old;
                new_piece->a_bouge -= 1;
                plateau.plateau[coor_to_pos(old, taillep)] = new_piece;

                if (coup_special == petit_roque)
                {
                    pair<int, int> place_tour_old(old.first, 8);
                    pair<int, int> place_tour_new(old.first, 6);
                    Piece *piece_tour = plateau.plateau[coor_to_pos(place_tour_new, taillep)];
                    plateau.plateau[coor_to_pos(place_tour_new, taillep)] = NULL;
                    piece_tour->position_coor = place_tour_old;
                    piece_tour->a_bouge -= 1;
                    plateau.plateau[coor_to_pos(place_tour_old, taillep)] = piece_tour;
                }
                else if (coup_special == grand_roque)
                {
                    pair<int, int> place_tour_old(old.first, 1);
                    pair<int, int> place_tour_new(old.first, 4);
                    Piece *piece_tour = plateau.plateau[coor_to_pos(place_tour_new, taillep)];
                    plateau.plateau[coor_to_pos(place_tour_new, taillep)] = NULL;
                    piece_tour->position_coor = place_tour_old;
                    piece_tour->a_bouge -= 1;
                    plateau.plateau[coor_to_pos(place_tour_old, taillep)] = piece_tour;
                }
                else if (coup_special == prise_en_passant)
                {
                    pair<int, int> place_prise(old.first, news.second);
                    plateau.plateau[coor_to_pos(place_prise, taillep)] = new Piece(*piece_prise);
                }

                else if (coup_special == promotion)
                {
                    if (piece_prise != NULL)
                    {
                        plateau.plateau[coor_to_pos(news, taillep)] = new Piece(*piece_prise);
                    }

                    string old_type = "Pion";
                    actualise_type(*plateau.plateau[coor_to_pos(old, taillep)], old_type);
                }
                else // non_special
                {
                    if (piece_prise != NULL)
                    {
                        plateau.plateau[coor_to_pos(news, taillep)] = new Piece(*piece_prise);
                    }
                }

                plateau.L_coup_depuis_dep.pop_back();
            }

            coup_jouee++;
        }
    }
}

void resetPlateau(Echiquier &plateau, const Coup &coup_jouee)
{
    int taillep = plateau.taille;
    pair<int, int> old = coup_jouee.oldPosition;
    pair<int, int> news = coup_jouee.newPosition;
    Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)];
    Piece *piece_prise = coup_jouee.Taken;
    CoupSpecial coup_special = coup_jouee.Coup_special;

    if (taillep == 3) // si tictactoe
    {
        delete plateau.plateau[coor_to_pos(news, taillep)]; // on doit supprimer la pièce !
        plateau.plateau[coor_to_pos(news, taillep)] = NULL;
    }
    else // si on joue aux echecs !
    {
        plateau.plateau[coor_to_pos(news, taillep)] = NULL;
        new_piece->position_coor = old;
        new_piece->a_bouge -= 1;
        plateau.plateau[coor_to_pos(old, taillep)] = new_piece;

        if (coup_special == petit_roque)
        {
            pair<int, int> place_tour_old(old.first, 8);
            pair<int, int> place_tour_new(old.first, 6);
            Piece *piece_tour = plateau.plateau[coor_to_pos(place_tour_new, taillep)];
            plateau.plateau[coor_to_pos(place_tour_new, taillep)] = NULL;
            piece_tour->position_coor = place_tour_old;
            piece_tour->a_bouge -= 1;
            plateau.plateau[coor_to_pos(place_tour_old, taillep)] = piece_tour;
        }
        else if (coup_special == grand_roque)
        {
            pair<int, int> place_tour_old(old.first, 1);
            pair<int, int> place_tour_new(old.first, 4);
            Piece *piece_tour = plateau.plateau[coor_to_pos(place_tour_new, taillep)];
            plateau.plateau[coor_to_pos(place_tour_new, taillep)] = NULL;
            piece_tour->position_coor = place_tour_old;
            piece_tour->a_bouge -= 1;
            plateau.plateau[coor_to_pos(place_tour_old, taillep)] = piece_tour;
        }
        else if (coup_special == prise_en_passant)
        {
            pair<int, int> place_prise(old.first, news.second);
            plateau.plateau[coor_to_pos(place_prise, taillep)] = new Piece(*piece_prise);
        }

        else if (coup_special == promotion)
        {
            if (piece_prise != NULL)
            {
                plateau.plateau[coor_to_pos(news, taillep)] = new Piece(*piece_prise);
            }

            string old_type = "Pion";
            actualise_type(*plateau.plateau[coor_to_pos(old, taillep)], old_type);
        }
        else // non_special
        {
            if (piece_prise != NULL)
            {
                plateau.plateau[coor_to_pos(news, taillep)] = piece_prise;
            }
            else if (old != news)
                plateau.plateau[coor_to_pos(news, taillep)] = NULL;
        }

        plateau.L_coup_depuis_dep.pop_back();
    }
}

///
// Autre
/////

bool is_legal(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, CoupSpecial coup_special, string type_promu)
{

    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;

    if (coup_special == non_special || coup_special == promotion)
    {
        // verifier si le déplacement est dans les déplacements de la pièce
        list<Deplac_rel> dep_piece = piece_a_jouer->deplac_relatif;

        list<Deplac_rel>::iterator it;
        bool trouve = false;
        for (it = dep_piece.begin(); it != dep_piece.end(); it++)
            if (it->coor == dep_current.coor)
                trouve = true;

        if (!trouve)
        {
            // cout << "Ce déplacement n'est pas autorisé pour cette pièce.\n";
            return false;
        }

        // verifier si on sort du plateau
        pair<int, int> old_place = piece_a_jouer->position_coor;
        pair<int, int> new_place = old_place + dep_current.coor;
        if ((new_place.first < 1) || (new_place.first > taillep) || (new_place.second < 1) || (new_place.second > taillep))
        {
            // cout << "Ce déplacement sort du plateau.\n";
            return false;
        }

        // verifier si la case n'est pas déjà occupée par nous
        int new_place_pos = coor_to_pos(new_place, taillep);
        if ((plateau.plateau[new_place_pos] != NULL) && (plateau.plateau[new_place_pos]->isWhite == couleur_joueur))
        {
            // cout << "Cette case est occupée par l'une de vos pièces.\n";
            return false;
        }

        // verifiez si il y a une pièce le long du déplacement
        if ((piece_a_jouer->type != "Cavalier") && (is_piece_entre(plateau, old_place, new_place)))
        {
            // cout << "il y a une place qui vous bloque\n";
            return false;
        }

        // si pion, verifier où il est, s'il a déjà avancé de deux cases...
        if (piece_a_jouer->type == "Pion")
        {
            // s'il avance tout droit, il ne faut pas de pièce à l'arrivée
            if (((dep_current.coor == pair<int, int>(1, 0)) || (dep_current.coor == pair<int, int>(-1, 0)) || (dep_current.coor == pair<int, int>(2, 0)) || (dep_current.coor == pair<int, int>(-2, 0))) && (plateau.plateau[coor_to_pos(new_place, taillep)] != NULL))
            {
                // cout << "Le pion qui va tout droit ne peut pas manger\n";
                return false;
            }

            // il ne peut pas avancer de deux pas sauf au début
            if ((dep_current.coor == pair<int, int>(2, 0)) && (piece_a_jouer->a_bouge != 0))
            {
                // cout << "On ne peut avancer de deux cases sauf au premier coup\n";
                return false;
            }
            if ((dep_current.coor == pair<int, int>(-2, 0)) && (piece_a_jouer->a_bouge != 0))
            {
                // cout << "On ne peut avancer de deux cases sauf au premier coup\n";
                return false;
            }
            // le pion a un sens impose
            if ((couleur_joueur == true) && ((dep_current.coor == pair<int, int>(-2, 0)) || (dep_current.coor == pair<int, int>(-1, 0)) || (dep_current.coor == pair<int, int>(-1, 1)) || (dep_current.coor == pair<int, int>(-1, -1))))
            {
                // cout << "On ne peut pas reculer\n";
                return false;
            }
            if ((couleur_joueur == false) && ((dep_current.coor == pair<int, int>(2, 0)) || (dep_current.coor == pair<int, int>(1, 0)) || (dep_current.coor == pair<int, int>(1, 1)) || (dep_current.coor == pair<int, int>(1, -1))))
            {
                // cout << "On ne peut pas reculer\n";
                return false;
            }

            // s'il avance en diagonale c'est qu'il mange une pièce sauf si en passant
            if (((dep_current.coor == pair<int, int>(1, 1)) || (dep_current.coor == pair<int, int>(1, -1)) || (dep_current.coor == pair<int, int>(-1, 1)) || (dep_current.coor == pair<int, int>(-1, -1))) && ((plateau.plateau[coor_to_pos(new_place, taillep)] == NULL) || (plateau.plateau[coor_to_pos(new_place, taillep)]->isWhite == couleur_joueur)))
            {
                // cout << "Le pion qui va en diagonale doit manger\n";
                return false;
            }

            if ((coup_special == promotion) && (type_promu != "Dame") && (type_promu != "Tour") && (type_promu != "Fou") && (type_promu != "Cavalier"))
            {
                // cout << "Piece promu non légale.\n";
                return false;
            }
        }
        if ((piece_a_jouer->type == "Roi") && ((dep_current.coor == pair<int, int>(0, -2)) || (dep_current.coor == pair<int, int>(0, 2))))
        {
            // cout << "Le roi ne peut effecteur ce déplacement qu'en roquant\n";
            return false;
        }
    }

    // ON NE PEUT PAS FAIRE CA ICI §!!!!!!
    //  verifier si on place notre propre roi en échec

    // if (is_Echec(plateau, piece_a_jouer, dep_current, num_tour, couleur_joueur, promu, coup_special))
    //{
    //  cout << "Ce déplacement placerait votre roi en échec.\n";
    // return false;
    //}

    // la légalité des coups speciaux sauf promotion se fait des Special()

    // cout << "Ce coup est légal. \n";
    return true;
}

bool is_piece_entre(const Echiquier &plateau, pair<int, int> place_depart, pair<int, int> place_arrive)
{
    int taillep = plateau.taille;
    int roi_i = place_arrive.first;
    int roi_j = place_arrive.second;
    int ki = place_depart.first;
    int kj = place_depart.second;

    if (roi_i == ki)
    {
        for (int l = min(kj, roi_j) + 1; l <= max(kj, roi_j) - 1; l++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(ki, l), taillep)] != NULL)
                return true;
        }
    }
    else if (roi_j == kj)
    {
        for (int l = min(ki, roi_i) + 1; l <= max(ki, roi_i) - 1; l++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(l, kj), taillep)] != NULL)
                return true;
        }
    }
    else if ((roi_i - ki) * (roi_j - kj) > 0) // diagonale aigue
    {
        int m = 1;
        for (int l = min(kj, roi_j) + 1; l <= max(kj, roi_j) - 1; l++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(min(ki, roi_i) + m, l), taillep)] != NULL)
                return true;
            m += 1;
        }
    }
    else // diagonale grave  (1,6)-->(4,3) l=4,5
    {
        int n = 1;
        for (int l = min(kj, roi_j) + 1; l <= max(kj, roi_j) - 1; l++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(max(ki, roi_i) - n, l), taillep)] != NULL)
                return true;
            n += 1;
        }
    }
    return false;
}

Piece *taken_coup(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, CoupSpecial coup_special)
{

    int taille = plateau.taille;
    pair<int, int> coor_arriver = piece_a_jouer->position_coor + dep_current.coor;
    int place_arriver = coor_to_pos(coor_arriver, taille);
    Piece *piece_arriver = plateau.plateau[place_arriver];
    if (coup_special == prise_en_passant)
    {
        int ligne_pion_mange = piece_a_jouer->position_coor.first;
        int colonne_pion_mange = coor_arriver.second;
        pair<int, int> place_pion_mange(ligne_pion_mange, colonne_pion_mange);
        return new Piece(*plateau.plateau[coor_to_pos(place_pion_mange, taille)]);
    }
    else if (dep_current.coor == pair<int, int>(0, 0))
        return NULL;
    else if (piece_arriver != NULL)
    {

        return new Piece(*piece_arriver);
    }
    return NULL;
}

// on vérifie leur légalité ici ! Apelé avant is légal
CoupSpecial Special(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour)
{
    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;
    pair<int, int> place_roi = (couleur_joueur ? (plateau.roi_blanc->position_coor) : (plateau.roi_noir->position_coor));

    // petit_roque
    // le roi n'a pas bougé et fait le bon déplacement
    if ((piece_a_jouer->type == "Roi") && (dep_current.coor == pair<int, int>(0, 2)) && (!piece_a_jouer->a_bouge))
    {
        pair<int, int> place_tour_normalement = (couleur_joueur ? pair<int, int>(1, 8) : pair<int, int>(8, 8));
        Piece *case_tour = plateau.plateau[coor_to_pos(place_tour_normalement, taillep)];
        // la tour est au bon endroit et n'a pas bouge
        if ((case_tour != NULL) && (case_tour->type == "Tour") && (!case_tour->a_bouge))
        {
            // il ne doit pas y avoir de piece sur le passage
            if (!is_piece_entre(plateau, place_roi, place_tour_normalement))
            {
                // aucune place ne doit etre une place d'echec
                Deplac_rel dep_temp_1(pair<int, int>(0, 0));
                Deplac_rel dep_temp_2(pair<int, int>(0, 1));
                Deplac_rel dep_temp_3(pair<int, int>(0, 2));
                string promu("Pion");
                if (!is_Echec(plateau, piece_a_jouer, dep_temp_1, num_tour, couleur_joueur, promu, non_special))
                    if (!is_Echec(plateau, piece_a_jouer, dep_temp_2, num_tour, couleur_joueur, promu, non_special))
                        if (!is_Echec(plateau, piece_a_jouer, dep_temp_3, num_tour, couleur_joueur, promu, non_special))
                            return petit_roque;
            }
        }
    }

    // grand roque
    // le roi n'a pas bougé et fait le bon déplacement
    if ((piece_a_jouer->type == "Roi") && (dep_current.coor == pair<int, int>(0, -2)) && (!piece_a_jouer->a_bouge))
    {
        pair<int, int> place_tour_normalement = (couleur_joueur ? pair<int, int>(1, 1) : pair<int, int>(8, 1));
        Piece *case_tour = plateau.plateau[coor_to_pos(place_tour_normalement, taillep)];
        // la tour est au bon endroit et n'a pas bouge
        if (case_tour != NULL && case_tour->type == "Tour" && (!case_tour->a_bouge))
        {
            // il ne doit pas y avoir de piece sur le passage
            if (!is_piece_entre(plateau, place_roi, place_tour_normalement))
            {
                // aucune place ne doit etre une place d'echec
                Deplac_rel dep_temp_1(pair<int, int>(0, 0));
                Deplac_rel dep_temp_2(pair<int, int>(0, -1));
                Deplac_rel dep_temp_3(pair<int, int>(0, -2));
                string promu("Pion");
                if (!is_Echec(plateau, piece_a_jouer, dep_temp_1, num_tour, couleur_joueur, promu, non_special) && (!is_Echec(plateau, piece_a_jouer, dep_temp_2, num_tour, couleur_joueur, promu, non_special)) && (!is_Echec(plateau, piece_a_jouer, dep_temp_3, num_tour, couleur_joueur, promu, non_special)))
                    return grand_roque;
            }
        }
    }

    // les PIONS
    pair<int, int> old_place = piece_a_jouer->position_coor;
    pair<int, int> place_arrive = piece_a_jouer->position_coor + dep_current.coor;
    if ((place_arrive.first < 1) || (place_arrive.first > taillep) || (place_arrive.second < 1) || (place_arrive.second > taillep))
    {
        // cout << "Ce déplacement sort du plateau.\n";
        return non_special; // sera considéré non légal ainsi
    }

    // promotion
    int ligne_arrive = place_arrive.first;
    if (piece_a_jouer->type == "Pion" && (ligne_arrive == 8 || ligne_arrive == 1))
    {
        return promotion;
    }

    // prise en passant
    Piece *case_arrive = plateau.plateau[coor_to_pos(place_arrive, taillep)];
    if (piece_a_jouer->type == "Pion" && case_arrive == NULL && (num_tour > 3))
    {
        Coup dernier_coup = plateau.L_coup_depuis_dep.back();
        // les blancs

        if (couleur_joueur && (dep_current.coor == pair<int, int>(1, 1)) && ligne_arrive == 6)
        {
            pair<int, int> place_pion_mange_normalement = old_place + pair<int, int>(0, 1);
            Piece derniere_piece = dernier_coup.pieceJouee;
            pair<int, int> dep_coor_dernier_coup = dernier_coup.newPosition - dernier_coup.oldPosition;
            if ((derniere_piece.type == "Pion") && (dep_coor_dernier_coup == pair<int, int>(-2, 0)) && (dernier_coup.newPosition == place_pion_mange_normalement))
                return prise_en_passant;
        }
        else if (couleur_joueur && dep_current.coor == pair<int, int>(1, -1) && ligne_arrive == 6)
        {
            pair<int, int> place_pion_mange_normalement = old_place + pair<int, int>(0, -1);
            Piece derniere_piece = dernier_coup.pieceJouee;
            pair<int, int> dep_coor_dernier_coup = dernier_coup.newPosition - dernier_coup.oldPosition;
            if (derniere_piece.type == "Pion" && dep_coor_dernier_coup == pair<int, int>(-2, 0) && dernier_coup.newPosition == place_pion_mange_normalement)
                return prise_en_passant;
        }
        else if (!couleur_joueur && dep_current.coor == pair<int, int>(-1, -1) && ligne_arrive == 3)
        {
            pair<int, int> place_pion_mange_normalement = old_place + pair<int, int>(0, -1);
            Piece derniere_piece = dernier_coup.pieceJouee;
            pair<int, int> dep_coor_dernier_coup = dernier_coup.newPosition - dernier_coup.oldPosition;
            if (derniere_piece.type == "Pion" && dep_coor_dernier_coup == pair<int, int>(2, 0) && dernier_coup.newPosition == place_pion_mange_normalement)
                return prise_en_passant;
        }
        else if (!couleur_joueur && dep_current.coor == pair<int, int>(-1, 1) && ligne_arrive == 3)
        {
            pair<int, int> place_pion_mange_normalement = old_place + pair<int, int>(0, 1);
            Piece derniere_piece = dernier_coup.pieceJouee;
            pair<int, int> dep_coor_dernier_coup = dernier_coup.newPosition - dernier_coup.oldPosition;
            if (derniere_piece.type == "Pion" && dep_coor_dernier_coup == pair<int, int>(2, 0) && dernier_coup.newPosition == place_pion_mange_normalement)
                return prise_en_passant;
        }
    }
    return non_special;
}

bool is_Echec(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, bool couleur_roi_en_echec, string type_promu, CoupSpecial coup_special)
{
    // on ne vérifie ^pas la légalité, supposé fait avant
    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;

    // on doit verifier si l'un des déplacement de la pièce menace le roi ennemi sans piece entre les deux et si une autre piece vient menacer le roi !
    pair<int, int> new_position = piece_a_jouer->position_coor + dep_current.coor;

    Piece *taken = taken_coup(plateau, piece_a_jouer, dep_current, coup_special);
    Coup coup_jouee(couleur_joueur, piece_a_jouer, new_position, piece_a_jouer->position_coor, num_tour, taken, coup_special, type_promu, false, false); // a voir pour les deux derniers
    actualisePlateau(plateau, coup_jouee);
    pair<int, int> place_roi_ennemi = (couleur_roi_en_echec ? (plateau.roi_blanc->position_coor) : (plateau.roi_noir->position_coor));

    // plateau.affiche();

    // on parcourt toutes les pièces du joueur  contre le roi. peut etre changer le sens de parcours i et j pour optimalité
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            Piece *piece_a_jouer_bis = plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
            if ((piece_a_jouer_bis != NULL) && (piece_a_jouer_bis->isWhite != couleur_roi_en_echec))
            {
                list<Deplac_rel> dep_rel = piece_a_jouer_bis->deplac_relatif;
                list<Deplac_rel>::iterator dep_current_bis = dep_rel.begin();
                string promu_bis;
                while (dep_current_bis != dep_rel.end())
                {

                    CoupSpecial coup_special_bis = Special(plateau, piece_a_jouer_bis, *dep_current_bis, num_tour);
                    if (coup_special_bis == promotion)
                        promu_bis = "Fou";
                    else
                        promu_bis = "Pion";

                    if (place_roi_ennemi == (piece_a_jouer_bis->position_coor + dep_current_bis->coor))
                    {
                        if (is_legal(plateau, piece_a_jouer_bis, *dep_current_bis, num_tour, coup_special_bis, promu_bis))
                        {
                            resetPlateau(plateau, coup_jouee);
                            return true;
                        }
                    }
                    dep_current_bis++;
                }
            }
        }
    }

    resetPlateau(plateau, coup_jouee);
    // plateau.affiche();
    return false;
}

bool is_Mat(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel dep_current, int num_tour, string type_promu, CoupSpecial coup_special, bool is_ech)
{
    int taillep = plateau.taille;
    // int posi_piece_a_jouer = coor_to_pos(piece_a_jouer.position_coor, taillep);
    bool couleur_joueur = piece_a_jouer->isWhite;
    if (!is_ech)
        //! is_Echec(plateau, piece_a_jouer, dep_current, num_tour, !couleur_joueur, type_promu, coup_special)) // pas opti !
        return false;

    Piece *roi_ennemi = ((!couleur_joueur) ? plateau.roi_blanc : plateau.roi_noir);
    bool couleur_roi_ennemi = roi_ennemi->isWhite;

    pair<int, int> new_position = piece_a_jouer->position_coor + dep_current.coor;

    Coup coup_jouee(couleur_joueur, piece_a_jouer, new_position, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current, coup_special), coup_special, type_promu, false, false); // a voir pour les deux derniers
    actualisePlateau(plateau, coup_jouee);
    // plateau.affiche();

    // TOUT CA SE FAIT EN UNE BOUCLE
    // DEJA CODER DANS COUPS POSSIBLES WESH
    //  check si le roi peut bouger sans etre ensuite en echec
    //  check si une pièce ennemi autre le roi peut se mettre enstre les pièces ou une piece peut graille la pièce = si le roi est toujours en echec
    bool is_cp_poss = is_coupsPossibles(plateau, couleur_roi_ennemi, num_tour);
    if (is_cp_poss)
    {
        resetPlateau(plateau, coup_jouee);
        return false;
    }
    resetPlateau(plateau, coup_jouee);
    return true;
}
