#include <iostream>
using namespace std;
#include "pour_jouer.hpp"

//////
// COUP
//////

Coup::Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, int num_tour, bool istaken, bool isspecial, Coup *next, Coup *prev, bool is_ech, bool is_m)
{
    isWhite = isW;
    Piece *piece_ptr = new Piece(pieceJ);
    pieceJouee = *piece_ptr;
    oldPosition = oldP;
    newPosition = newP;
    isTaken = istaken;
    isSpecial = isspecial;
    Next = next;
    Prev = prev;
    is_echec = is_ech;
    is_mat = is_m;
    num_tour_de_jeu = num_tour;
}

Coup::Coup(const Coup &coup)
{
    isWhite = coup.isWhite;
    Piece *piece_ptr = new Piece(coup.pieceJouee);
    pieceJouee = *piece_ptr;
    oldPosition = coup.oldPosition;
    newPosition = coup.newPosition;
    isTaken = coup.isTaken;
    isSpecial = coup.isSpecial;
    is_echec = coup.is_echec;
    is_mat = coup.is_mat;
    num_tour_de_jeu = coup.num_tour_de_jeu;
    if (coup.Next == 0)
    {
        Next = 0;
    }
    else
    {
        Next = coup.Next; // new ??
    }

    if (coup.Prev == 0)
    {
        Prev = 0;
    }
    else
    {
        Prev = coup.Next;
    }
}

ostream &operator<<(ostream &out, const Coup &coup)
{
    out << coup.num_tour_de_jeu;
    out << (coup.isWhite ? "b" : "n") << " --> ";
    if (coup.isSpecial)
    {
        out << "C'est un coup spécial.";
    }
    else
    {
        if (coup.pieceJouee.type == "Pion")
        {
            if (coup.isTaken)
            {
                out << coup.oldPosition.second + 96;
            }
        }
        else
        {
            out << coup.pieceJouee.type[0];
        }

        if (coup.isTaken)
        {
            out << "x";
        }
        out << coup.newPosition;

        if (coup.is_mat)
        {
            out << "#";
        }
        else if (coup.is_echec)
        {
            out << "+";
        }

        out << (coup.isWhite ? " | " : "\n");
    }
    return out;
}

// pour TTT
bool is_coup_gagnant_TTT(const Echiquier &plateauRef, const Coup &dernierCoup)
{
    Piece **plateau = plateauRef.plateau;
    int taillep = plateauRef.taille;
    pair<int, int> this_position = dernierCoup.newPosition;
    bool couleur = dernierCoup.isWhite;

    // ligne
    int ligne = this_position.first;
    int p = 0;
    int plac;

    for (int j = 1; j <= 3; j++)
    {
        pair<int, int> coor(ligne, j);
        plac = coor_to_pos(coor, taillep);
        if (plateau[plac] != NULL)
        {
            if (plateau[plac]->isWhite == couleur)
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
            plac = coor_to_pos(coor, taillep);
            if (plateau[plac] != NULL)
            {
                if (plateau[plac]->isWhite == couleur)
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
                    plac = coor_to_pos(coor, taillep);
                    if (plateau[plac] != NULL)
                    {
                        if (plateau[plac]->isWhite == couleur)
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
                    plac = coor_to_pos(coor, taillep);
                    if (plateau[plac] != NULL)
                    {
                        if (plateau[plac]->isWhite == couleur)
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
ListeCoups *coupsPossiblesTTT(const Echiquier &plateau, bool isWhite, int num_tour) // est-ce au joueur blanc de jouer ?
{
    int nbC = 0;
    int taillep = plateau.taille;
    Coup *first = NULL;
    Coup *current = NULL;
    Coup *prev = NULL;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)] == NULL)
            {
                if (nbC == 0)
                {
                    first = new Coup(isWhite, Piece(isWhite, pair<int, int>(i, j)), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour, false, false, NULL, NULL);
                    prev = first;
                }
                else
                {
                    current = new Coup(isWhite, Piece(isWhite, pair<int, int>(i, j)), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour, false, false, NULL, prev);
                    prev->Next = current;
                    prev = current;
                }
                nbC += 1;
            }
        }
    }
    ListeCoups *coupPossibles = new ListeCoups(nbC, first, current);
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

void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    // Coup *dernierCoup = coupsPrecedents.last;
    Coup *coup = coupsPrecedents.first;
    int taillep = plateau.taille;

    while (coup != NULL)
    {
        Piece piece = &(coup->pieceJouee);
        pair<int, int> old = coup->oldPosition;
        pair<int, int> news = coup->newPosition;
        bool is_prise = coup->isTaken;
        Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)];

        if (taillep == 3) // si tictactoe
        {
            new_piece = new Piece(piece); // on doit créer la pièce !
        }
        else // si echecs
        {
            Piece *old_piece = plateau.plateau[coor_to_pos(old, taillep)];

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
    int taillep = plateau.taille;
    pair<int, int> old = coupjoue.oldPosition;
    pair<int, int> news = coupjoue.newPosition;
    bool is_prise = coupjoue.isTaken;

    if (taillep == 3) // si tictactoe
    {
        Piece *new_piece = new Piece(piece); // on doit créer la pièce ?
        new_piece->position_coor = news;
        plateau.plateau[coor_to_pos(news, taillep)] = new_piece;
    }
    else // si echecs
    {
        Piece *old_piece = plateau.plateau[coor_to_pos(old, taillep)];
        Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)];

        if (is_prise)
        {
            new_piece->~Piece();
        }
        new_piece = old_piece;
        old_piece = NULL;

        new_piece->position_coor = news;
        plateau.plateau[coor_to_pos(news, taillep)] = new_piece;
    }
}

void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    Coup *coup = coupsPrecedents.last;

    int taillep = plateau.taille;
    // Coup *premierCoup = coupsPrecedents.first;

    while (coup != NULL)
    {
        Piece piece = &(coup->pieceJouee);
        pair<int, int> old = coup->oldPosition;
        pair<int, int> news = coup->newPosition;
        Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)]; // on remonte à l'envers les étapes

        if (taillep == 3) // si tictactoe
        {
            new_piece->~Piece(); // on doit supprimer la pièce !
        }
        else // si echecs ! faire la prise ! A REVOIR ! impossible ou rajouter la liste des pièces prises
        {
            Piece *old_piece = plateau.plateau[coor_to_pos(old, taillep)];
            old_piece = new_piece;
            new_piece = NULL;
            old_piece->position_coor = old;
        }

        coup = coup->Prev;
    }
}
