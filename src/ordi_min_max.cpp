#include <iostream>
using namespace std;
#include "ordi_min_max.hpp"

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
void Position::generateur(int profondeur)
{
    Position *current = NULL;
    list<Coup>::iterator it;
    if (profondeur == 0)
    {
        set_valeur();
    }
    else if (!CoupsPrecedents.empty() && CoupsPrecedents.back().is_mat)
        set_valeur();
    else
    {
        actualisePlateau(*PlateauRef, CoupsPrecedents);
        list<Coup> coup_poss = coupsPossiblesTTT(*PlateauRef, Joueur_courant, Num_tour_de_jeu + 1);
        // cout << coup_poss;
        resetPlateau(*PlateauRef, CoupsPrecedents);
        if (coup_poss.empty())
            set_valeur();
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
                current->generateur(profondeur - 1);
                if (Joueur == Joueur_courant && current->ValeurMinMax > valeur)
                    valeur = current->ValeurMinMax;
                else if (Joueur != Joueur_courant && current->ValeurMinMax < valeur)
                    valeur = current->ValeurMinMax;
            }
            ValeurMinMax = valeur;
        }
    }
}

void Position::set_valeur() // actuellement pour le TTT
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

Coup *coup_min_max(Echiquier *EchiTTT, bool is_white_courant, int num_tour, int profondeur)
{
    list<Coup> list_vide;
    Position position(EchiTTT, list_vide, NULL, NULL, is_white_courant, num_tour, is_white_courant);
    position.generateur(profondeur);
    int valeurcible = position.ValeurMinMax;
    // position.MinMax(position.Joueur);
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

/*
void Position::MinMax(bool is_white_current)
{
    // Si position terminale
    if (this->fille == NULL)
    {
        this->valeurMinMax = this->valeurPosition;
    }
    else
    {
        // Si le joueur est le joueur en train de jouer

        Position *current = this->fille;
        current->MinMax(is_white_current);
        int temp = current->valeurMinMax;
        while (current->soeur != NULL)
        {
            current = current->soeur;
            current->MinMax(is_white_current);

            if (this->joueur == is_white_current)
            {
                // Si le joueur du noeud est celui qui joue, MAX
                // VERIFIER false OU true
                if (current->valeurPosition > temp)
                {
                    cout << "RE REFLECHIS";
                    temp = current->valeurPosition;
                }
            }
            else
            {
                // Si le joueur du noeud N'est PAS celui qui joue, MIN
                if (current->valeurPosition < temp)
                {
                    temp = current->valeurPosition;
                }
            }
        }
        this->valeurMinMax = temp;
    }
}
*/