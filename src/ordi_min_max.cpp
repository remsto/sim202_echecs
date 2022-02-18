#include <iostream>
using namespace std;
#include "ordi_min_max.hpp"

////
// POSITION
////

Position::Position(Echiquier &plateau, ListeCoups &coups, Position *positionSoeur, Position *positionFille, bool joueurCoup)
{
    plateauRef = plateau;
    joueur = joueurCoup;
    soeur = positionSoeur;
    fille = positionFille;
    coupsPrecedents = coups;
}

Position::~Position() // a faire
{

    coupsPrecedents.~ListeCoups();
    if (soeur != NULL)
    {
        soeur->~Position();
    }
    if (fille != NULL)
    {
        fille->~Position();
    }
}

// pour TTT a cause de coups possibles
void Position::generateur(int profondeur)
{
    if (profondeur != 0)
    {
        actualisePlateau(plateauRef, coupsPrecedents);
        ListeCoups *coupsPossibles = coupsPossiblesTTT(plateauRef, joueur); // regrouper avec valeur dans une méthode?
        resetPlateau(plateauRef, coupsPrecedents);

        // CREATION 1ere FILLE
        // copie coupsPrecedents
        ListeCoups coupsPrecedentsCurrent(coupsPrecedents);
        // Le 1er coupPossible devient le dernier coupPrecedent
        (coupsPrecedentsCurrent.last)->Next = coupsPossibles.first;
        coupsPrecedentsCurrent.last = (coupsPrecedentsPrec.last)->Next;
        coupsPrecedentsCurrent.nbCoups++;

        this->fille = new Position(plateauRef, coupsPrecedentsCurrent, NULL, NULL, !joueur);
        Position *current = this->fille;

        for (int i = 0; i < coupsPossibles.nbCoups; i++)
        {   // maj coupsPossibles
            coupsPossibles.first = (coupsPossibles.first)->Next;
            coupsPossibles.nbCoups = coupsPossibles.nbCoups - 1;

            // cps = this.cp
            ListeCoups coupsPrecedentsSoeur(coupsPrecedents);

            // cps.last.next = dernier coup = b
            (coupsPrecedentsSoeur.last)->Next = coupsPossibles->first;
            // cps.last = b
            coupsPrecedentsSoeur.last = (coupsPrecedentsSoeur.last)->Next;
            coupsPrecedentsSoeur.nbCoups++;

            // CREATION SOEUR
            current->soeur = new Position(plateauRef, coupsPrecedentsSoeur, NULL, NULL, !joueur);
            
            // Passer à la suivante
            current = current->soeur;

            // Appeler récursion sur current
            current->generateur(profondeur - 1);

        }
    }
}

void annexe(int profondeur, ListeCoups coupsPossibles) //+ Position pos)
{
    if (coupsPossibles.first != coupsPossibles.last)
    {
    }
    if ((profondeur != 0))
    {
        // créer fille, appeler annexe dessus (profondeur -1)
    }
}

int Position::calculeValeurPosition()
{
    if ((*this).estGagnante())
    {
        return inf;
    }
    else
    {
        return 0;
    }
}

bool Position::estGagnante()
{
    actualisePlateau(plateauRef, coupsPrecedents);

    // vérifier comme des bourrins TicTacToe (le dernier coup est decisif)
    Coup *dernierCoup = coupsPrecedents.last;
    bool is_coup_gagne = is_coup_gagnant(plateauRef, *dernierCoup);
    // On réinitialise le plateau
    resetPlateau(plateauRef, coupsPrecedents);
    return is_coup_gagne;
}
