#include "ordi_min_max.hpp"
using namespace std;

////
// POSITION
////

Position::Position(Echiquier *plateau, list<Coup> Lcoups, Position *positionSoeur, Position *positionFille, bool joueur_courant, int num_tour, bool joueur, int valeur)
{
    PlateauRef = plateau;
    CoupsPrecedents = Lcoups;
    Soeur = positionSoeur;
    Fille = positionFille;
    Joueur_courant = joueur_courant;
    Num_tour_de_jeu = num_tour;
    Joueur = joueur;
    ValeurMinMax = valeur;
}

Position::~Position()
{
    if (Soeur != NULL)
    {
        delete Soeur;
    }
    if (Fille != NULL)
    {
        delete Fille;
    }
}

// pour TTT a cause de coups possibles
void Position::generateur(int profondeur, int gammap, int gammac)
{
    int taille = PlateauRef->taille;
    Position *current = NULL;
    list<Coup>::iterator it;
    if (profondeur == 0)
    {
        set_valeur(gammap, gammac);
    }
    else if (!CoupsPrecedents.empty() && CoupsPrecedents.back().is_mat)
        set_valeur(gammap, gammac);
    else
    {
        actualisePlateau(*PlateauRef, CoupsPrecedents);
        list<Coup> coup_poss;
        if (taille == 3)
            coup_poss = coupsPossiblesTTT(*PlateauRef, Joueur_courant, Num_tour_de_jeu + 1);
        else if (taille == 8)
            coup_poss = coupsPossibles(*PlateauRef, Joueur_courant, Num_tour_de_jeu + 1);
        // cout << coup_poss;
        resetPlateau(*PlateauRef, CoupsPrecedents);
        if (coup_poss.empty())
            set_valeur(0, 0);
        else
        {
            int valeur;
            if (Joueur == Joueur_courant)
                valeur = -inf;
            else
                valeur = inf;
            //////resetPlateau(*plateauRef, coupsPrecedents); !!!!!!

            // CREATION des filles
            for (it = coup_poss.begin(); it != coup_poss.end(); it++)
            {
                // copie coupsPrecedents
                list<Coup> CPCurrent = CoupsPrecedents;
                // Le 1er coupPossible devient le dernier coupPrecedent
                CPCurrent.push_back(*it);
                // cout << endl << CPCurrent;
                if (current == NULL)
                {
                    Fille = new Position(PlateauRef, CPCurrent, NULL, NULL, !Joueur_courant, Num_tour_de_jeu + 1, Joueur);
                    current = Fille;
                }
                else
                {
                    current->Soeur = new Position(PlateauRef, CPCurrent, NULL, NULL, !Joueur_courant, Num_tour_de_jeu + 1, Joueur);
                    current = current->Soeur;
                }
                // Appeler récursion sur current
                current->generateur(profondeur - 1, gammap, gammac);
                if (Joueur == Joueur_courant && current->ValeurMinMax > valeur)
                    valeur = current->ValeurMinMax;
                else if (Joueur != Joueur_courant && current->ValeurMinMax < valeur)
                    valeur = current->ValeurMinMax;
            }
            ValeurMinMax = valeur;
        }
    }
}

void Position::set_valeur(int gammap, int gammac) // actuellement pour le TTT
{
    int taillep = PlateauRef->taille;
    if (taillep == 3) // TTT
    {
        if (CoupsPrecedents.empty())
        {
            cout << "ca ne devrait pas arriver \n";
        }
        else
        {
            Coup coup = CoupsPrecedents.back();
            if (coup.is_mat && Joueur_courant != Joueur)
                ValeurMinMax = inf;
            else if (coup.is_mat && Joueur_courant == Joueur)
                ValeurMinMax = -inf;
            else
                ValeurMinMax = 0;
        }
    }
    else /// pour les echecs
    {
        if (CoupsPrecedents.empty())
        {
            cout << "ca ne devrait pas arriver \n";
        }
        else if (gammap == 0 && gammac == 0) // pat
            ValeurMinMax = 0;
        else
        {
            Coup coup = CoupsPrecedents.back();
            if (coup.is_mat && Joueur_courant != Joueur)
                ValeurMinMax = inf;
            else if (coup.is_mat && Joueur_courant == Joueur)
                ValeurMinMax = -inf;
            else
            {
                actualisePlateau(*PlateauRef, CoupsPrecedents);
                int valeur_piece_Joueur = 0;
                int valeur_piece_adv = 0;
                int nombre_case_Joueur = 0;
                int nombre_case_adv = 0;

                for (int i = 1; i <= 8; i++)
                {
                    for (int j = 1; j <= 8; j++)
                    {
                        int place = coor_to_pos(pair<int, int>(i, j), taillep);
                        Piece *piece_current = PlateauRef->plateau[place];
                        if (piece_current != NULL && piece_current->isWhite == Joueur)
                        {
                            valeur_piece_Joueur += piece_current->valeur;
                            list<Deplac_rel> dep_hyp = piece_current->deplac_relatif;
                            list<Deplac_rel>::iterator it;
                            for (it = dep_hyp.begin(); it != dep_hyp.end(); it++)
                            {
                                CoupSpecial coup_spe = Special(*PlateauRef, piece_current, *it, Num_tour_de_jeu);
                                string type_promu = "Pion";
                                if (coup_spe == promotion)
                                    type_promu = "Tour";
                                if (is_legal(*PlateauRef, piece_current, *it, Num_tour_de_jeu, coup_spe, type_promu))
                                    nombre_case_Joueur += 1;
                            }
                        }
                        else if (piece_current != NULL && piece_current->isWhite != Joueur)
                        {
                            valeur_piece_adv += piece_current->valeur;
                            list<Deplac_rel> dep_hyp = piece_current->deplac_relatif;
                            list<Deplac_rel>::iterator it;
                            for (it = dep_hyp.begin(); it != dep_hyp.end(); it++)
                            {
                                CoupSpecial coup_spe = Special(*PlateauRef, piece_current, *it, Num_tour_de_jeu);
                                string type_promu = "Pion";
                                if (coup_spe == promotion)
                                    type_promu = "Tour";
                                if (is_legal(*PlateauRef, piece_current, *it, Num_tour_de_jeu, coup_spe, type_promu))
                                    nombre_case_adv += 1;
                            }
                        }
                    }
                }
                resetPlateau(*PlateauRef, CoupsPrecedents);
                ValeurMinMax = gammap * (valeur_piece_Joueur - valeur_piece_adv) + gammac * (nombre_case_Joueur - nombre_case_adv);
            }
        }
    }
}

/*
bool Position::estGagnante()
{
    bool is_coup_gagne = false;

    if (!CoupsPrecedents.empty())
    {
        actualisePlateau(*PlateauRef, CoupsPrecedents);

        // vérifier comme des bourrins TicTacToe (le dernier coup est decisif)
        Coup dernierCoup = CoupsPrecedents.back();
        is_coup_gagne = is_coup_gagnant_TTT(*plateauRef, dernierCoup);

        // On réinitialise le plateau
        resetPlateau(*plateauRef, coupsPrecedents);
    }
    return is_coup_gagne;
}
*/

Coup *coup_min_max(Echiquier *EchiTTT, bool is_white_courant, int num_tour, int profondeur, int gammap, int gammac)
{
    list<Coup> list_vide;
    Position position(EchiTTT, list_vide, NULL, NULL, is_white_courant, num_tour, is_white_courant);
    position.generateur(profondeur, gammap, gammac);
    int valeurcible = position.ValeurMinMax;
    // cout << valeurcible << endl;
    Position *current = position.Fille;

    while (current != NULL)
    {
        if (current->ValeurMinMax == valeurcible)
        {
            Coup *coup = new Coup(current->CoupsPrecedents.back());
            return coup;
        }
        current = current->Soeur;
    }
    return NULL;
}
