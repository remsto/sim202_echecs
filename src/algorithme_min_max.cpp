#include <iostream>
using namespace std;
#include "algorithme_min_max.hpp"
#include "environnement.hpp"

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
    if (this != NULL)
    {
        coupsPrecedents.~ListeCoups();
        soeur->~Position();
        fille->~Position();
    }
}

void Position::generateur(int profondeur)
{
    Echiquier plateau = plateauRef;
    actualisePlateau(plateau, coupsPrecedents);
    ListeCoups coupsPossibles = coupsPossibles(plateau); // a coder
    resetPlateau(plateau);

    annexe(profondeur, coupsPossibles); // a coder
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

int Position::calculeValeurPosition()
{
    if estGagnante ()
    {
        return inf;
    }
    return 0;
}

bool Position::estGagnante()
{
    Piece **plateau = plateauRef.plateau;
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

void actualisePlateau(Echiquier plateau, ListeCoups coupsPrecedents)
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
        plateau.plateau[coor_to_pos(old)] = NULL; // coder le convertisseur coor_to_pos
        plateau.plateau[coor_to_pos(new)] = piece;

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

//////
// COUP
//////

Coup::Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, bool istaken, bool isspecial, Coup *next, Coup *prev)
{
    isWhite = isW;
    pieceJouee = pieceJ;
    oldPosition = oldP;
    newPosition = newP;
    isTaken = istaken;
    isSpecial = isspecial;
    Next = next;
    Prev = prev;
}

Coup::Coup(const Coup &coup)
{
    isWhite = coup.isWhite;
    pieceJouee = coup.pieceJouee;
    oldPosition = coup.oldPosition;
    newPosition = coup.newPosition;
    isTaken = coup.isTaken;
    isSpecial = coup.isSpecial;
    if (coup.Next == 0)
    {
        Next = 0;
    }
    else
    {
        Next = new Coup(*coup.Next);
    }

    if (coup.Prev == 0)
    {
        Prev = 0;
    }
    else
    {
        Prev = new Coup(*coup.Next);
    }
}

//////
// LISTECOUPS
//////

void addCoup(ListeCoups &L, const Coup &C)
{
    Coup *K = new Coup(C);
    K->Next = NULL;
    if (L.nbCoups == 0)
        L.first = K;
    else
        L.last->Next = K;
    L.last = K;
    L.nbCoups++;
}

// pour TTT
ListeCoups coupsPossiblesTTT(Echiquier plateau, bool isWhite) // est-ce au joueur blanc de jouer ?
{
    int nbC = 0;
    Coup *first = NULL;
    Coup *current = NULL;
    Coup *prev = NULL;
    Coup *next = NULL;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (plateau.plateau[coor_to_pos_TTT(pair<int, int>(i, j))] == NULL)
            {
                if (nbC == 0)
                {
                    first = new Coup(isWhite, Piece(isWhite, pair<int, int>(i, j)), pair<int, int>(i, j), pair<int, int>(0, 0), false, false, NULL, NULL);
                    prev = first;
                }
                else
                {
                    current = new Coup(isWhite, Piece(isWhite, pair<int, int>(i, j)), pair<int, int>(i, j), pair<int, int>(0, 0), false, false, NULL, prev);
                    prev->Next = current;
                    prev = current;
                }
                nbC += 1;
            }
        }
    }
    ListeCoups coupPossibles(nbC, first, current);
    return coupPossibles;
}

ListeCoups::ListeCoups(int nbC, Coup *first_acopier, Coup *last_acopier)
{
    nbCoups = nbC;
    // Coup *first_copier = new Coup(first_acopier);
    // Coup *last_copier = new Coup(last_acopier);  // je pense qu'il ne faut pas les copier ! A vérifier !
    first = first_acopier;
    last = last_acopier;
}

ListeCoups::ListeCoups(const ListeCoups &a_copier)
{
    nbCoups = a_copier.nbCoups;
    Coup *first_copier = new Coup(*a_copier.first);
    Coup *last_copier = new Coup(*a_copier.last);
    first = first_copier;
    last = last_copier;
}

ListeCoups::ListeCoups()
{
    nbCoups = 0;
    first = NULL;
    last = NULL;
}
