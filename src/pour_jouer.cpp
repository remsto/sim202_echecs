#include <iostream>
using namespace std;
#include "pour_jouer.hpp"
#include "environnement.hpp"

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

ostream &operator<<(ostream &out, const Coup &coup)
{
    out << "le coup est : ";
    out << coup.pieceJouee << " se déplace de " << coup.oldPosition << " à " << coup.newPosition;
}

bool is_coup_gagnant(const Echiquier &plateauRef, const Coup &dernierCoup)
{
    Piece **plateau = plateauRef.plateau;
    pair<int, int> this_position = dernierCoup.newPosition;
    bool couleur = dernierCoup.isWhite;

    // ligne
    int ligne = this_position.first;
    int p = 0;
    for (int j = 1; j <= 3; j++)
    {
        pair<int, int> coor(ligne, j);
        if (plateau[coor_to_pos(coor)] != NULL)
        {
            if (plateau[coor_to_pos(coor)]->isWhite == couleur)
                p++;
        }
    }
    if (p == 3)
        return true;

    else
    {

        // colonne
        int colonne = this_position.second;
        int q = 0;
        for (int i = 1; i <= 3; i++)
        {
            pair<int, int> coor(i, colonne);
            if (plateau[coor_to_pos(coor)] != NULL)
            {
                if (plateau[coor_to_pos(coor)]->isWhite == couleur)
                    q++;
            }
        }
        if (q == 3)
            return true;
        else
        {

            // diagonales aigu
            if (ligne == colonne)
            {
                int r = 0;
                for (int k = 1; k <= 3; k++)
                {
                    pair<int, int> coor(k, k);
                    if (plateau[coor_to_pos(coor)] != NULL)
                    {
                        if (plateau[coor_to_pos(coor)]->isWhite == couleur)
                            r++;
                    }
                }
                if (r == 3)
                    return true;
            }
            else
            {

                // diagonales grave
                int s = 0;
                int j = 3;
                for (int i = 1; i <= 3; i++)
                {
                    pair<int, int> coor(i, j);
                    if (plateau[coor_to_pos(coor)] != NULL)
                    {
                        if (plateau[coor_to_pos(coor)]->isWhite == couleur)
                            s++;
                    }
                    j -= 1;
                }
                if (s == 3)
                    return true;
            }
        }
    }
    return false;
}

//////
// LISTECOUPS
//////

void addCoup(ListeCoups *L, const Coup &C)
{
    Coup *K = new Coup(C);
    K->Next = NULL;
    if (L->nbCoups == 0)
        L->first = K;
    else
        L->last->Next = K;
    L->last = K;
    L->nbCoups++;
}

// pour TTT
ListeCoups coupsPossiblesTTT(Echiquier plateau, bool isWhite) // est-ce au joueur blanc de jouer ?
{
    int nbC = 0;
    Coup *first = NULL;
    Coup *current = NULL;
    Coup *prev = NULL;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(i, j))] == NULL)
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

///////
////MAJ plateau
///////

// TTT
void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    // Coup *dernierCoup = coupsPrecedents.last;
    Coup *coup = coupsPrecedents.first;

    while (coup != NULL)
    {
        Piece piece = &(coup->pieceJouee);
        pair<int, int> old = coup->oldPosition;
        pair<int, int> news = coup->newPosition;
        bool is_prise = coup->isTaken;
        Piece *new_piece = plateau.plateau[coor_to_pos(news)];

        if (old == pair<int, int>(0, 0)) // si tictactoe
        {
            new_piece = new Piece(piece); // on doit créer la pièce !
        }
        else // si echecs
        {
            Piece *old_piece = plateau.plateau[coor_to_pos(old)];

            if (is_prise)
            {
                new_piece->~Piece();
            }
            new_piece = old_piece;
            old_piece = NULL;
        }
        new_piece->position_coor = news;
        coup = coup->Next;
    }
}

// quand on a qu'un coup à faire ! + actualise la pièce
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue)
{
    Piece piece = (coupjoue.pieceJouee);
    pair<int, int> old = coupjoue.oldPosition;
    pair<int, int> news = coupjoue.newPosition;
    bool is_prise = coupjoue.isTaken;
    Piece *new_piece;

    if (old == pair<int, int>(0, 0)) // si tictactoe
    {
        new_piece = new Piece(piece); // on doit créer la pièce !
    }
    else // si echecs
    {
        Piece *old_piece = plateau.plateau[coor_to_pos(old)];

        if (is_prise)
        {
            new_piece->~Piece();
        }
        new_piece = old_piece;
        old_piece = NULL;
    }
    new_piece->position_coor = news;
    plateau.plateau[coor_to_pos(news)] = new_piece;
}

void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    Coup *coup = coupsPrecedents.last;
    // Coup *premierCoup = coupsPrecedents.first;

    while (coup != NULL)
    {
        Piece piece = &(coup->pieceJouee);
        pair<int, int> old = coup->oldPosition;
        pair<int, int> news = coup->newPosition;
        Piece *new_piece = plateau.plateau[coor_to_pos(news)]; // on remonte à l'envers les étapes

        if (old == pair<int, int>(0, 0)) // si tictactoe
        {
            new_piece->~Piece(); // on doit supprimer la pièce !
        }
        else // si echecs ! faire la prise ! A REVOIR ! impossible ou rajouter la liste des pièces prises
        {
            Piece *old_piece = plateau.plateau[coor_to_pos(old)];
            old_piece = new_piece;
            new_piece = NULL;
            old_piece->position_coor = old;
        }

        coup = coup->Prev;
    }
}
