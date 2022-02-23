#include <iostream>
#include <cstdlib>
using namespace std;
#include "pour_jouer.hpp"

//////
// COUP
//////

Coup::Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, int num_tour, Piece *taken, bool isspecial, Coup *next, Coup *prev, bool is_ech, bool is_m)
{
    isWhite = isW;
    Piece *piece_ptr = new Piece(pieceJ);
    pieceJouee = *piece_ptr;
    oldPosition = oldP;
    newPosition = newP;
    Taken = taken;
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
    Taken = coup.Taken;
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
            if (coup.Taken != NULL)
            {
                out << coup.oldPosition.second + 96;
            }
        }
        else
        {
            out << coup.pieceJouee.type[0];
        }

        if (coup.Taken)
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
                    first = new Coup(isWhite, Piece(isWhite), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour, false, false, NULL, NULL);
                    prev = first;
                }
                else
                {
                    current = new Coup(isWhite, Piece(isWhite), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour, false, false, NULL, prev);
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

ListeCoups *coupsPossibles(const Echiquier &plateau, bool isWhit, int num_tour)
{
    int nbC = 0;
    int taillep = plateau.taille;
    Coup *first = NULL;
    Coup *current = NULL;
    Coup *prev = NULL;

    // on parcour le plateau
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            Piece *piece_a_jouer = plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
            if (piece_a_jouer->isWhite = isWhit)
            {
                // on parcourt ses déplacements possible, si il est légal on l'ajoute.
                ListDeplac_rel dep_piece = piece_a_jouer->deplac_relatif;
                Deplac_rel *dep_current = dep_piece.first;

                while (dep_current != NULL)
                {
                    if (is_legal(plateau, piece_a_jouer, dep_current))
                    {
                        if (nbC == 0)
                        {

                            first = new Coup(isWhit, Piece(*piece_a_jouer), dep_current->coor + piece_a_jouer->position_coor, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current), is_Special(plateau, piece_a_jouer, dep_current), NULL, NULL, is_Echec(plateau, piece_a_jouer, dep_current, num_tour), is_Mat(plateau, piece_a_jouer, dep_current, num_tour));
                            prev = first;
                        }
                        else
                        {

                            current = new Coup(isWhit, Piece(*piece_a_jouer), dep_current->coor + piece_a_jouer->position_coor, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current), is_Special(plateau, piece_a_jouer, dep_current), NULL, prev, is_Echec(plateau, piece_a_jouer, dep_current, num_tour), is_Mat(plateau, piece_a_jouer, dep_current, num_tour));
                            prev->Next = current;
                            prev = current;
                        }
                        nbC += 1;
                    }
                }
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
        bool is_prise = (coup->Taken != NULL);
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
    bool is_prise = (coupjoue.Taken != NULL);

    if (taillep == 3) // si tictactoe
    {
        Piece *new_piece = new Piece(piece); // on doit créer la pièce ?
        new_piece->position_coor = news;
        plateau.plateau[coor_to_pos(news, taillep)] = new_piece;
    }
    else // si on joue aux echecs
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

///
// Autre
/////

bool is_legal(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current) // chiant
{
    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;

    // verifier si le déplacement est dans les déplacements de la pièce
    bool is_in_list = false;
    ListDeplac_rel dep_piece = piece_a_jouer->deplac_relatif;
    Deplac_rel *dep_etudie = dep_piece.first;
    while (dep_etudie != NULL)
    {
        if (dep_etudie->coor == dep_current->coor)
            is_in_list = true;
    }
    if (!is_in_list)
    {
        cout << "ce déplacement n'est pas autorisé pour cette pièce";
        return false;
    }

    // verifier si on sort du plateau
    pair<int, int> old_place = piece_a_jouer->position_coor;
    pair<int, int> new_place = old_place + dep_current->coor;
    if (new_place.first < 1 || new_place.first >= taillep || new_place.second < 1 || new_place.second >= taillep)
    {
        cout << "ce déplacement sort du plateau";
        return false;
    }

    // verifier si la case n'est pas déjà occupée par nous
    if (plateau.plateau[coor_to_pos(new_place, taillep)]->isWhite == couleur_joueur)
    {
        cout << "cette case est occupée par l'une de vos pièce";
        return false;
    }

    // verifiez si il y a une pièce le long du déplacement
    if ((piece_a_jouer->type != "Cavalier") && (is_piece_entre(plateau, old_place, new_place)))
        return false;

    // si pion, verifier où il est

    // verifier si on place notre propre roi en échec

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
            if (plateau.plateau[coor_to_pos(pair<int, int>(kj, l), taillep)] != NULL)
                return true;
        }
    }
    else
    {
        int m = 1;
        for (int l = min(kj, roi_j) + 1; l <= max(kj, roi_j) - 1; l++)
        {
            if (plateau.plateau[coor_to_pos(pair<int, int>(min(ki, roi_i) + m, l), taillep)] != NULL)
                return true;
            m += 1;
        }
    }
    return true;
}

Piece *taken_coup(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current)
{
    if (!is_legal)
        return false;
    int taille = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;
    pair<int, int> coor_arriver = piece_a_jouer->position_coor + dep_current->coor;
    int place_arriver = coor_to_pos(coor_arriver, taille);
    Piece *piece_arriver = plateau.plateau[place_arriver];
    if (piece_arriver != NULL && piece_arriver->isWhite != couleur_joueur)
    {
        return piece_arriver;
    }
    return NULL;
}

bool is_Special(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current)
{
    return false;
}

bool is_Echec(const Echiquier &plateau, Piece *piece_a_joue, Deplac_rel *dep_current, int num_tour)
{
    if (!is_legal)
    {
        return false;
    }
    int taillep = plateau.taille;
    Piece *piece_a_jouer = new Piece(piece_a_joue);
    bool couleur_joueur = piece_a_jouer->isWhite;
    pair<int, int> place_roi_ennemi = (couleur_joueur ? plateau.roi_blanc->position_coor : plateau.roi_noir->position_coor);

    // on doit verifier si l'un des déplacement de la pièce menace le roi ennemi sans piece entre les deux et si une autre piece vient menacer le roi !
    pair<int, int> new_position = piece_a_jouer->position_coor + dep_current->coor;

    Echiquier plateau_copier = Echiquier(plateau);
    Coup coup_jouee = Coup(couleur_joueur, piece_a_jouer, new_position, piece_a_jouer->position_coor, num_tour, taken_coup(plateau_copier, piece_a_jouer, dep_current), is_Special(plateau_copier, piece_a_jouer, dep_current), NULL, NULL, false, false); // a voir pour les deux derniers
    actualisePlateau(plateau_copier, coup_jouee);

    // on parcourt toutes les pièces du joueur
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; i <= taillep; j++)
        {
            Piece *piece_a_jouer_bis = plateau_copier.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
            if (piece_a_jouer_bis != NULL && piece_a_jouer_bis->isWhite == couleur_joueur)
            {
                ListDeplac_rel dep_rel = piece_a_jouer_bis->deplac_relatif;
                Deplac_rel *dep_current_bis = dep_rel.first;
                while (dep_current_bis != NULL)
                {
                    if ((place_roi_ennemi == (piece_a_jouer_bis->position_coor + dep_current_bis->coor)) && (is_legal(plateau_copier, piece_a_jouer, dep_current_bis)))
                    {
                        if (piece_a_jouer_bis->type == "Cavalier")
                            return true;
                        else if ((piece_a_jouer_bis->type == "Pion")) //&& (dep_current_bis->coor != pair<int, int>(1, 0)) ) inutile car le coup serait illégal
                            return true;
                        else // on doit tester si il y a une piece entre les deux
                        {
                            if (!is_piece_entre(plateau_copier, place_roi_ennemi, piece_a_jouer_bis->position_coor))
                                return true;
                        }
                    }
                    dep_current_bis = dep_current_bis->Next;
                }
            }
        }
    }
    plateau_copier.~Echiquier();
    return false;
}

bool is_Mat(const Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current)
{
    if (!is_legal)
        return false;

    // check si le roi peut bouger sans etre en échec

    // check si une pièce peut se mettre devant

    // check si on peut graille la pièce
    return false;
}