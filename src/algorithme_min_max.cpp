#include <iostream>
using namespace std;
#include "algorithme_min_max.hpp"
#include "environnement.hpp"

Position::Position(Echiquier &plateau, ListeCoups &coups, Position *positionSoeur, Position *positionFille, bool joueurCoup)
{
    plateauRef = plateau;
    joueur = joueurCoup;
    soeur = positionSoeur;
    fille = positionFille;
    coupsPrecedents = coups;
}

Position::~Position()
{
    delete[] coupsPrecedents;
}

void Position::generateur(int profondeur)
{
    Piece **plateau = plateauRef->plateau;
    actualisePlateau(plateau, coupsPrecedents);
    ListeCoups coupsPossibles = coupsPossibles(); // a coder
    resetPlateau(plateau);

    annexe(profondeur, coupsPossibles) // a coder
    // for (int i = 0; i<coupsPossibles.nbCoups;i++){
    //     Coup* coup = coupsPrecedents.last;
    //     coup->next =
    //     Position(plateau, coupsPrecedents, Position* positionSoeur, Position* positionFille, bool joueurCoup)
    // }
}

void annexe(int profondeur, ListeCoups coupsPossibles)
{
    if ((profondeur != 0))
    {
        if (coupsPossibles.first != coupsPossibles.last)
        {
            // créer soeur, appeler annexe dessus
        }
        // créer fille, appeler annexe dessus (profondeur -1)
    }
}

void addCoup(ListeCoups &L, const Coup &C)
{
    Coup *K = new Coup(C);
    K->next = NULL;
    if (L.nbCoups == 0)
        L.first = K;
    else
        L.last->next = K;
    L.last = K;
    L.nbCoups++;
}

ListeCoups coupsPossibles(Echiquier plateau)
{

    for (i = 1; i <= 3; i++)
    {
        for (j = 1; j <= 3; j++)
        {
            if (plateauRef)
            {
            }
        }
    }
}

int Position::valeurPosition()
{
    if estGagnante ()
    {
        return inf;
    }
    return 0;
}

bool Position::estGagnante()
{
    Piece **plateau = plateauRef->plateau;
    actualisePlateau(plateau, coupsPrecedents);

    // vérifier comme des bourrins TicTacToe (le dernier coup est decisif)

    pair<int, int> this_position = dernierCoup->newPosition;
    bool couleur = dernierCoup->isWhite;
    // ligne
    int ligne = this_position.first;
    int p = 0;
    for (int j = 1; j <= 3; j++)
    {
        if (plateau[(i-1)*taille + (j-1)]!=Null{
            if (plateau[(i - 1) * taille + (j - 1)]->isWhite == couleur)
                p++;
        }
    }
    if (p == 3)
        return True;

    // colonne
    int colonne = this_position.second;
    int q = 0;
    for (int i = 1; i <= 3; i++)
    {
        if (plateau[(i-1)*taille + (colonne-1)]!=Null{
            if (plateau[(i - 1) * taille + (colonne - 1)]->isWhite == couleur)
                q++;
        }
    }
    if (q == 3)
        return True;

    // diagonales
    if (ligne == colonne)
    {
        p = 0;
        q = 0;
        for (int k = 1; k <= 3; k++)
        {
            if (plateau[(k-1)*taille + (k-1)]!=Null{
                if (plateau[(k - 1) * taille + (k - 1)]->isWhite == couleur)
                    p++;
            }
            if (plateau[(3-k)*taille + (3-k)]!=Null{
                if (plateau[(3 - k) * taille + (3 - k)]->isWhite == couleur)
                    q++;
            }
        }
    }

    if ((p == 3) || (q == 3))
        return True;
    return False;

    // On réinitialise le plateau
    resetPlateau(plateau, coupsPrecedents);
}

Void actualisePlateau(Echiquier plateau, ListeCoups coupsPrecedents)
{
    Coup *dernierCoup = coupsPrecedents->last;
    Coup *premierCoup = coupsPrecedents->first;
    Coup *coup = premierCoup;
    bool check = True;
    while (check)
    {
        Piece *piece = &(coup->pieceJouee);
        int old = coup->oldPosition;
        int new = coup->newPosition;
        plateau[coor_to_pos(old)] = NULL; // coder le convertisseur coor_to_pos
        plateau[coor_to_pos(new)] = piece;

        check = (coup != dernierCoup);
        coup = coup.Next;
    }
}

void resetPlateau(Echiquier plateau, ListeCoups coupsPrecedents)
{
    Coup *dernierCoup = coupsPrecedents->last;
    Coup *premierCoup = coupsPrecedents->first;
    Coup *coup = premierCoup;

    bool check = True;
    coup = dernierCoup;
    while (check)
    {
        Piece *piece = &(coup->pieceJouee);
        int old = coup->oldPosition;
        int new = coup->newPosition;
        plateau[coor_to_pos(new)] = NULL; // coder le convertisseur coor_to_pos
        plateau[coor_to_pos(old)] = piece;

        check = (coup != premierCoup);
        coup = coup.Prev;
    }
}
Coup::Coup(bool isW, Piece &pieceJ, pair<int, int> &newP, pair<int, int> &oldP, bool isTaken = False, bool isSpecial = False) {}