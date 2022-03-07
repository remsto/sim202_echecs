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
    // Piece *piece_ptr = new Piece(pieceJ);
    pieceJouee = pieceJ;
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
    if (coup.isSpecial)
    {
        out << "C'est un coup spécial.";
    }
    else
    {
        string typee = coup.pieceJouee.type;
        if (typee == "Pion")
        {
            if (coup.Taken != NULL)
            {
                out << coup.oldPosition.second + 96;
            }
        }
        else
        {
            char premiere_lettre = (typee)[0];
            out << premiere_lettre;
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

void addCoup(ListeCoups *L, Coup *C)
{

    C->Next = NULL; // inutile mais on sait jamais
    if (L->nbCoups == 0)
    {
        C->Prev = NULL;
        L->first = C;
    }
    else
    {
        C->Prev = L->last;
        (L->last)->Next = C;
    }
    L->last = C;
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
                    first = new Coup(isWhite, Piece(isWhite), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour);
                    prev = first;
                }
                else
                {
                    current = new Coup(isWhite, Piece(isWhite), pair<int, int>(i, j), pair<int, int>(0, 0), num_tour);
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

ListeCoups *coupsPossibles(Echiquier &plateau, bool isWhit, int num_tour)
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
            if ((piece_a_jouer != NULL) && (piece_a_jouer->isWhite == isWhit))
            {
                // on parcourt ses déplacements possible, si il est légal on l'ajoute.
                ListDeplac_rel dep_piece = piece_a_jouer->deplac_relatif;
                Deplac_rel *dep_current = dep_piece.first;

                while (dep_current != NULL)
                {
                    if (is_legal(plateau, piece_a_jouer, dep_current, num_tour))
                    {
                        if (nbC == 0)
                        {

                            first = new Coup(isWhit, Piece(*piece_a_jouer), dep_current->coor + piece_a_jouer->position_coor, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current, num_tour), is_Special(plateau, piece_a_jouer, dep_current), NULL, NULL, is_Echec(plateau, piece_a_jouer, dep_current, num_tour, !isWhit), is_Mat(plateau, piece_a_jouer, dep_current, num_tour));
                            prev = first;
                        }
                        else
                        {

                            current = new Coup(isWhit, Piece(*piece_a_jouer), dep_current->coor + piece_a_jouer->position_coor, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current, num_tour), is_Special(plateau, piece_a_jouer, dep_current), NULL, prev, is_Echec(plateau, piece_a_jouer, dep_current, num_tour, !isWhit), is_Mat(plateau, piece_a_jouer, dep_current, num_tour));
                            prev->Next = current;
                            prev = current;
                        }
                        nbC += 1;
                    }
                    dep_current = dep_current->Next;
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

ostream &operator<<(ostream &out, const ListeCoups &Listcoup)
{

    Coup *current_Coups = Listcoup.first;
    while (current_Coups != NULL)
    {
        current_Coups->isWhite ? out << current_Coups->num_tour_de_jeu << "." : out << "";
        out << " ";
        out << *current_Coups;
        out << (current_Coups->isWhite ? "" : "\n");

        current_Coups = current_Coups->Next;
    }
    return out;
}

///////
////MAJ plateau
///////

// quand on a qu'un coup à faire ! + actualise la pièce
void actualisePlateau(Echiquier &plateau, const Coup &coupjoue)
{
    int taillep = plateau.taille;
    pair<int, int> old = coupjoue.oldPosition;
    pair<int, int> news = coupjoue.newPosition;
    bool is_prise = (coupjoue.Taken != NULL);

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

        if (is_prise)
        {
            plateau.plateau[coor_to_pos(news, taillep)]->~Piece();
        }

        old_piece->position_coor = news;
        plateau.plateau[coor_to_pos(news, taillep)] = old_piece;
    }
}


void actualisePlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    cout << "témoin";
    // Coup *dernierCoup = coupsPrecedents.last;
    Coup *coup = coupsPrecedents.first;
    int taillep = plateau.taille;

    for(int i = 1; i==coupsPrecedents.taille; i++)
    {
        actualisePlateau(plateau, coup);
        coup = coup->Next;
    }
}


void resetPlateau(Echiquier &plateau, const Coup &coup_jouee)
{
    int taillep = plateau.taille;
    pair<int, int> old = coup_jouee.oldPosition;
    pair<int, int> news = coup_jouee.newPosition;
    Piece *new_piece = plateau.plateau[coor_to_pos(news, taillep)];

    if (taillep == 3) // si tictactoe
    {
        print("ouaf");
        //new_piece->~Piece(); // on doit supprimer la pièce !
        plateau.plateau[coor_to_pos(news, taillep)]=NULL;
    }
    else // si on joue aux echecs !
    {
        print("ouafi");
        new_piece->position_coor = old;
        plateau.plateau[coor_to_pos(old, taillep)] = new_piece;

        Piece *piece_prise = coup_jouee.Taken;
        if (piece_prise != NULL)
            plateau.plateau[coor_to_pos(news, taillep)] = piece_prise;
        else
            plateau.plateau[coor_to_pos(news, taillep)] = NULL;
    }
}


void resetPlateau(Echiquier &plateau, const ListeCoups &coupsPrecedents)
{
    Coup *coup = coupsPrecedents.last;
    int taillep = plateau.taille;
    // Coup *premierCoup = coupsPrecedents.first;

    for(int i = 1; i==coupsPrecedents.taille; i++)
    {
        resetPlateau(plateau, coup);
        coup = coup->Prev;
    }
}

///
// Autre
/////

bool is_legal(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour) // chiant
{
    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;

    // verifier si le déplacement est dans les déplacements de la pièce
    bool is_in_list = false;
    ListDeplac_rel dep_piece = piece_a_jouer->deplac_relatif;
    Deplac_rel *dep_etudie = dep_piece.first;
    while (dep_etudie != NULL) // pas opti car parcours tous les deplacements
    {
        if (dep_etudie->coor == dep_current->coor)
            is_in_list = true;
        dep_etudie = dep_etudie->Next;
    }
    if (!is_in_list)
    {
        cout << "Ce déplacement n'est pas autorisé pour cette pièce.\n";
        return false;
    }

    // verifier si on sort du plateau
    pair<int, int> old_place = piece_a_jouer->position_coor;
    pair<int, int> new_place = old_place + dep_current->coor;
    if ((new_place.first < 1) || (new_place.first > taillep) || (new_place.second < 1) || (new_place.second > taillep))
    {
        cout << "Ce déplacement sort du plateau.\n";
        return false;
    }

    // verifier si la case n'est pas déjà occupée par nous
    int new_place_pos = coor_to_pos(new_place, taillep);
    if ((plateau.plateau[new_place_pos] != NULL) && (plateau.plateau[new_place_pos]->isWhite == couleur_joueur))
    {
        cout << "Cette case est occupée par l'une de vos pièces.\n";
        return false;
    }

    // verifiez si il y a une pièce le long du déplacement
    if ((piece_a_jouer->type != "Cavalier") && (is_piece_entre(plateau, old_place, new_place)))
    {
        cout << "il y a une place qui vous bloque\n";
        return false;
    }

    // si pion, verifier où il est, s'il a déjà avancé de deux cases...
    if (piece_a_jouer->type == "Pion")
    {
        // s'il avance tout droit, il ne faut pas de pièce à l'arrivée
        if (((dep_current->coor == pair<int, int>(1, 0)) || (dep_current->coor == pair<int, int>(-1, 0)) || (dep_current->coor == pair<int, int>(2, 0)) || (dep_current->coor == pair<int, int>(-2, 0))) && (plateau.plateau[coor_to_pos(new_place, taillep)] != NULL))
        {
            cout << "Le pion qui va tout droit ne peut pas manger\n";
            return false;
        }

        // s'il avance en digonale c'est qu'il mange une pièce
        if (((dep_current->coor == pair<int, int>(1, 1)) || (dep_current->coor == pair<int, int>(1, -1)) || (dep_current->coor == pair<int, int>(-1, 1)) || (dep_current->coor == pair<int, int>(-1, -1))) && ((plateau.plateau[coor_to_pos(new_place, taillep)] == NULL) || (plateau.plateau[coor_to_pos(new_place, taillep)]->isWhite == couleur_joueur)))
        {
            cout << "Le pion qui va tout droit ne peut pas manger\n";
            return false;
        }

        // il ne peut pas avancer de deux pas sauf au début
        if ((dep_current->coor == pair<int, int>(2, 0)) && (old_place.first != 2))
        {
            cout << "On ne peut avancer de deux cases sauf au premier coup\n";
            return false;
        }
        if ((dep_current->coor == pair<int, int>(-2, 0)) && (old_place.first != 7))
        {
            cout << "On ne peut avancer de deux cases sauf au premier coup\n";
            return false;
        }
        // le pion a un sens impose
        if ((couleur_joueur == true) && ((dep_current->coor == pair<int, int>(-2, 0)) || (dep_current->coor == pair<int, int>(-1, 0)) || (dep_current->coor == pair<int, int>(-1, 1)) || (dep_current->coor == pair<int, int>(-1, -1))))
        {
            cout << "On ne peut pas reculer\n";
            return false;
        }
        if ((couleur_joueur == false) && ((dep_current->coor == pair<int, int>(2, 0)) || (dep_current->coor == pair<int, int>(1, 0)) || (dep_current->coor == pair<int, int>(1, 1)) || (dep_current->coor == pair<int, int>(1, -1))))
        {
            cout << "On ne peut pas reculer\n";
            return false;
        }
    }
    if (piece_a_jouer->type == "Roi")
    {
    }

    // verifier si on place notre propre roi en échec
    if (is_Echec(plateau, piece_a_jouer, dep_current, num_tour, couleur_joueur))
    {
        cout << "Ce déplacement placerait votre roi en échec.\n";
        return false;
    }

    cout << "Ce coup est légal. \n";
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

Piece *taken_coup(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour)
{

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

bool is_Echec(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour, bool couleur_roi_en_echec)
{
    // on ne vérifie ^pas la légalité, supposé fait avant
    int taillep = plateau.taille;
    bool couleur_joueur = piece_a_jouer->isWhite;

    // on doit verifier si l'un des déplacement de la pièce menace le roi ennemi sans piece entre les deux et si une autre piece vient menacer le roi !
    pair<int, int> new_position = piece_a_jouer->position_coor + dep_current->coor;
    Coup coup_jouee = Coup(couleur_joueur, piece_a_jouer, new_position, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current, num_tour), is_Special(plateau, piece_a_jouer, dep_current), NULL, NULL, false, false); // a voir pour les deux derniers
    actualisePlateau(plateau, coup_jouee);
    pair<int, int> place_roi_ennemi = (couleur_roi_en_echec ? plateau.roi_blanc->position_coor : plateau.roi_noir->position_coor);
    // plateau.affiche();

    // on parcourt toutes les pièces du joueur  contre le roi. peut etre changer le sens de parcours i et j pour optimalité
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            Piece *piece_a_jouer_bis = plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
            if ((piece_a_jouer_bis != NULL) && (piece_a_jouer_bis->isWhite != couleur_roi_en_echec))
            {
                ListDeplac_rel dep_rel = piece_a_jouer_bis->deplac_relatif;
                Deplac_rel *dep_current_bis = dep_rel.first;
                while (dep_current_bis != NULL)
                {
                    if ((place_roi_ennemi == (piece_a_jouer_bis->position_coor + dep_current_bis->coor)) && (is_legal(plateau, piece_a_jouer_bis, dep_current_bis, num_tour)))
                    {
                        resetPlateau(plateau, coup_jouee);
                        cout << "la piece mettant en echec est : " << *piece_a_jouer_bis << " en se déplacant ainsi " << *dep_current_bis << "a partir de " << piece_a_jouer_bis->position_coor << endl;
                        return true;
                    }
                    dep_current_bis = dep_current_bis->Next;
                }
            }
        }
    }
    resetPlateau(plateau, coup_jouee);
    // plateau.affiche();
    return false;
}

bool is_Mat(Echiquier &plateau, Piece *piece_a_jouer, Deplac_rel *dep_current, int num_tour)
{
    bool couleur_joueur = piece_a_jouer->isWhite;
    if (!is_Echec(plateau, piece_a_jouer, dep_current, num_tour, !couleur_joueur)) // pas opti !
        return false;

    int taillep = plateau.taille;
    Piece *roi_ennemi = ((!couleur_joueur) ? plateau.roi_blanc : plateau.roi_noir);
    bool couleur_roi_ennemi = roi_ennemi->isWhite;

    pair<int, int> new_position = piece_a_jouer->position_coor + dep_current->coor;

    Coup coup_jouee = Coup(couleur_joueur, piece_a_jouer, new_position, piece_a_jouer->position_coor, num_tour, taken_coup(plateau, piece_a_jouer, dep_current, num_tour), is_Special(plateau, piece_a_jouer, dep_current), NULL, NULL, false, false); // a voir pour les deux derniers
    actualisePlateau(plateau, coup_jouee);
    // plateau.affiche();

    // TOUT CA SE FAIT EN UNE BOUCLE
    //  check si le roi peut bouger sans etre ensuite en echec
    //  check si une pièce ennemi autre le roi peut se mettre enstre les pièces ou une piece peut graille la pièce = si le roi est toujours en echec
    for (int i = 1; i <= taillep; i++)
    {
        for (int j = 1; j <= taillep; j++)
        {
            Piece *piece_pouvant_defendre = plateau.plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
            if (piece_pouvant_defendre != NULL && piece_pouvant_defendre->isWhite == couleur_roi_ennemi)
            {
                ListDeplac_rel Listdep_piece_pouvant_defendre = piece_pouvant_defendre->deplac_relatif;
                Deplac_rel *dep_piece_pouvant_defendre = Listdep_piece_pouvant_defendre.first;
                while (dep_piece_pouvant_defendre != NULL)
                {

                    if (is_legal(plateau, piece_pouvant_defendre, dep_piece_pouvant_defendre, num_tour + 1)) // && (!is_Echec(plateau, piece_pouvant_defendre, dep_piece_pouvant_defendre, num_tour + 1, couleur_roi_ennemi))) DEJA TEST DANS IS LEGAL !!!
                    {
                        resetPlateau(plateau, coup_jouee);
                        cout << "la piece pouvant defendre est : " << *piece_pouvant_defendre << " en se déplacant ainsi " << *dep_piece_pouvant_defendre << "a partir de " << piece_pouvant_defendre->position_coor;
                        return false;
                    }
                    dep_piece_pouvant_defendre = dep_piece_pouvant_defendre->Next;
                }
            }
        }
    }

    resetPlateau(plateau, coup_jouee);
    return true;
}
