
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "environnement.hpp"
using namespace std;

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS !


pour info :
(ligne,colonne)

3| 6 | 7 | 8 |
2| 3 | 4 | 5 |
1| 0 | 1 | 2 |
   1   2   3
   A   B   C


2| 3 | 4 | 5 | 3 | 4 | 5 | 3 | 4 |
1| 0 | 1 | 2 | 3 | 4 | 5 | 3 | 4 |
3| 6 | 7 | 8 | 3 | 4 | 5 | 3 | 4 |
2| 3 | 4 | 5 | 3 | 4 | 5 | 3 | 4 |
1| 0 | 1 | 2 | 3 | 28| 5 | 3 | 4 |
3| 6 | 7 | 8 | 3 | 20| 5 | 3 | 4 |
2| 8 | 9 | 10| 11| 12| 5 | 3 | 4 |
1| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
   1   2   3
   A   B   C   D   E   F   G   H
*/

// class Deplac_rel et ListDeplac_rel

Deplac_rel::Deplac_rel(pair<int, int> coord)
{
    coor = coord;
}

Deplac_rel::Deplac_rel(const Deplac_rel &dep_a_copier)
{
    coor = dep_a_copier.coor;
}

ostream &operator<<(ostream &out, const Deplac_rel &dep)
{
    out << "(" << dep.coor.first << "," << dep.coor.second << ")";
    return out;
}

ostream &operator<<(ostream &out, const list<Deplac_rel> &listDep)
{
    list<Deplac_rel>::const_iterator it = listDep.begin();
    out << listDep.size() << " : "
        << "[";
    while (it != listDep.end())
    {
        out << *it << ";";
        it++;
    }
    out << "]";
    return out;
}

// class TypePiece

TypePiece::TypePiece(string typee)
{
    type = typee;

    if (type == "Pion")
    {
        valeur = 1;
        list<Deplac_rel> list_dep;
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 0)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, 0)));

        deplac_relatif = list_dep;
    }

    else if (type == "Tour")
    {
        valeur = 5;

        list<Deplac_rel> list_dep;

        for (int i = 1; i <= 7; i++)
        {
            list_dep.push_back(Deplac_rel(pair<int, int>(i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, 0)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(0, -i)));
        }
        deplac_relatif = list_dep;
    }

    else if (type == "Cavalier")
    {
        valeur = 3;

        list<Deplac_rel> list_dep;

        list_dep.push_back(Deplac_rel(pair<int, int>(-1, -2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-1, 2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, -2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(1, 2)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(-2, 1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, -1)));
        list_dep.push_back(Deplac_rel(pair<int, int>(2, 1)));

        deplac_relatif = list_dep;
    }

    else if (type == "Fou")
    {
        valeur = 3;

        list<Deplac_rel> list_dep;

        for (int i = 1; i <= 7; i++)
        {
            list_dep.push_back(Deplac_rel(pair<int, int>(i, i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, -i)));
            list_dep.push_back(Deplac_rel(pair<int, int>(-i, i)));
        }
        deplac_relatif = list_dep;
    }
    else if (type == "Roi")
    {
        valeur = 100; // arbitraire, à réfléchir
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

        deplac_relatif = list_dep;
    }
    else if (type == "Dame")
    {
        valeur = 9;

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
        deplac_relatif = list_dep;
    }
    else
    {
        valeur = 1;
        list<Deplac_rel> list_dep;
        deplac_relatif = list_dep;
    }
}

// class Piece

Piece::Piece(bool isWhit, int bouger, pair<int, int> coor, string typee) : TypePiece(typee)
{
    isWhite = isWhit;
    position_coor = coor;
    a_bouge = bouger;
}

Piece::Piece(const Piece &piece_a_copier) : TypePiece(piece_a_copier.type)
{
    isWhite = piece_a_copier.isWhite;
    position_coor = piece_a_copier.position_coor;
    a_bouge = piece_a_copier.a_bouge;
}

ostream &operator<<(ostream &out, const Piece &piece)
{
    out << (piece.type[0]); // P ou D ou R ou ...
    if (piece.isWhite)
    {
        out << "b";
    }
    else
    {
        out << "n";
    }
    return out;
}

//////
// COUP
//////

Coup::Coup(bool isW, const Piece &pieceJ, pair<int, int> newP, pair<int, int> oldP, int num_tour, Piece *taken, CoupSpecial coup_special, string type_promu, bool is_ech, bool is_m)
{
    isWhite = isW;
    pieceJouee = pieceJ;
    oldPosition = oldP;
    newPosition = newP;
    Taken = taken;
    Coup_special = coup_special;
    Type_Promu = type_promu;
    is_echec = is_ech;
    is_mat = is_m;
    num_tour_de_jeu = num_tour;
}

Coup::Coup(const Coup &coup)
{
    isWhite = coup.isWhite;
    pieceJouee = coup.pieceJouee;
    oldPosition = coup.oldPosition;
    newPosition = coup.newPosition;
    Taken = coup.Taken;
    Coup_special = coup.Coup_special;
    Type_Promu = coup.Type_Promu;
    is_echec = coup.is_echec;
    is_mat = coup.is_mat;
    num_tour_de_jeu = coup.num_tour_de_jeu;
}

Coup::~Coup()
{
}

ostream &operator<<(ostream &out, const Coup &coup)
{
    if (coup.Coup_special == petit_roque)
    {
        out << "0-0";
    }
    else if (coup.Coup_special == grand_roque)
    {
        out << "0-0-0";
    }

    else
    {
        string typee = coup.pieceJouee.type;
        if (typee == "Pion")
        {
            if (coup.Taken != NULL)
            {
                char colonne_pion = coup.oldPosition.second + 96;
                out << colonne_pion;
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

        if (coup.Coup_special == prise_en_passant)
        {
            out << "e.p";
        }
        else if (coup.Coup_special == promotion)
        {
            out << "=" << coup.Type_Promu[0];
        }

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

/////
// class Echiquier
/////

Echiquier::Echiquier(int n)
{
    taille = n;
    plateau = new Piece *[n * n];
    for (int i = 0; i < n * n; i++)
    {
        plateau[i] = NULL;
    }
    roi_noir = NULL;
    roi_blanc = NULL;
    list<Coup> l_coups;
    L_coup_depuis_dep = l_coups;
}

Echiquier::~Echiquier()
{
    for (int i = 0; i < taille * taille; i++)
    {
        if (plateau[i] != NULL)
            delete plateau[i];
    }
    delete[] plateau;
}

void Echiquier::affiche() const
{
    for (int i = taille; i > 0; i--)
    {
        cout << "   ";
        for (int i = 0; i < taille; i++)
        {
            cout << "-----";
        }
        cout << endl;
        cout << i << " |";

        for (int j = 1; j <= taille; j++)
        {
            Piece *piece = plateau[coor_to_pos(pair<int, int>(i, j), taille)];
            if (piece == NULL)
            {
                cout << "    |";
            }
            else
            {
                cout << " " << *piece;
                cout << " |";
            }
        }
        cout << "\n";
    }
    cout << "   ";
    for (int i = 0; i < taille; i++)
    {
        cout << "-----";
    }
    cout << endl;
    cout << "     ";
    for (int i = 1; i <= taille; i++)
    {
        char lettre = i + 96;
        cout << lettre << "    ";
    }
    cout << "\n";
}

int coor_to_pos(pair<int, int> p, int taillep)
{
    int n = (p.first - 1) * taillep + (p.second - 1);
    return n;
}

pair<int, int>
pos_to_coor(int n, int taillep)
{
    pair<int, int> p((n / taillep) + 1, (n % taillep) + 1);
    return p;
}

ostream &operator<<(ostream &out, const pair<int, int> &pair)
{
    char colonne = pair.second + 96;
    out << colonne;
    out << pair.first;
    return out;
}

// pour TTT
bool is_coup_gagnant_TTT(const Echiquier &plateauRef, bool couleur, const pair<int, int> &coor)
{
    Piece **plateau = plateauRef.plateau;
    int taillep = plateauRef.taille;

    // ligne
    int ligne = coor.first;
    int colonne = coor.second;
    int p = 1;
    int plac;

    for (int j = 1; j <= 3; j++)
    {
        pair<int, int> coor(ligne, j);
        plac = coor_to_pos(coor, taillep);
        if (plateau[plac] != NULL && plateau[plac]->isWhite == couleur)
        {
            p++;
        }
    }
    if (p == 3)
        return true;

    // colonne
    int q = 1;
    for (int i = 1; i <= 3; i++)
    {
        pair<int, int> coor(i, colonne);
        plac = coor_to_pos(coor, taillep);
        if (plateau[plac] != NULL && plateau[plac]->isWhite == couleur)
            q++;
    }

    if (q == 3)
        return true;

    // diagonale aigu
    if (ligne == colonne)
    {
        int r = 1;
        for (int k = 1; k <= 3; k++)
        {
            pair<int, int> coor(k, k);
            plac = coor_to_pos(coor, taillep);
            if (plateau[plac] != NULL && plateau[plac]->isWhite == couleur)
                r++;
        }

        if (r == 3)
            return true;
    }

    // diagonale grave
    if (colonne + ligne == 4)
    {
        int s = 1;
        int j = 3;
        for (int i = 1; i <= 3; i++)
        {
            pair<int, int> coor(i, j);
            plac = coor_to_pos(coor, taillep);
            if (i != ligne && plateau[plac] != NULL && plateau[plac]->isWhite == couleur) // c'est normal !!!
                s++;
            j -= 1;
        }

        if (s == 3)
            return true;
    }

    return false;
}

//////
// ALEA
//////

int tirage_alea_entier(int min, int max)
{
    default_random_engine re(chrono::system_clock::now().time_since_epoch().count());
    mt19937 gen(re());
    uniform_int_distribution<> distr(min, max);

    int n = distr(gen);
    return n;
}

// pour echecs
void mise_en_place_echec_piece(Echiquier &Echi)
{
    int taillep = Echi.taille;
    bool is_white = true;
    int place;

    // pions
    for (int j = 1; j <= taillep; j++)
    {
        // blanc
        Piece *pion = new Piece(is_white, false, pair<int, int>(2, j), "Pion");
        place = coor_to_pos(pair<int, int>(2, j), taillep);
        Echi.plateau[place] = pion;

        // noir
        pion = new Piece(!is_white, false, pair<int, int>(7, j), "Pion");
        place = coor_to_pos(pair<int, int>(7, j), taillep);
        Echi.plateau[place] = pion;
    }

    // tour
    Piece *tour = new Piece(is_white, false, pair<int, int>(1, 1), "Tour");
    place = coor_to_pos(pair<int, int>(1, 1), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(is_white, false, pair<int, int>(1, 8), "Tour");
    place = coor_to_pos(pair<int, int>(1, 8), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(!is_white, false, pair<int, int>(8, 1), "Tour");
    place = coor_to_pos(pair<int, int>(8, 1), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(!is_white, false, pair<int, int>(8, 8), "Tour");
    place = coor_to_pos(pair<int, int>(8, 8), taillep);
    Echi.plateau[place] = tour;

    // Cavalier
    Piece *cavalier = new Piece(is_white, false, pair<int, int>(1, 2), "Cavalier");
    place = coor_to_pos(pair<int, int>(1, 2), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(is_white, false, pair<int, int>(1, 7), "Cavalier");
    place = coor_to_pos(pair<int, int>(1, 7), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(!is_white, false, pair<int, int>(8, 2), "Cavalier");
    place = coor_to_pos(pair<int, int>(8, 2), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(!is_white, false, pair<int, int>(8, 7), "Cavalier");
    place = coor_to_pos(pair<int, int>(8, 7), taillep);
    Echi.plateau[place] = cavalier;

    // fou
    Piece *fou = new Piece(is_white, false, pair<int, int>(1, 3), "Fou");
    place = coor_to_pos(pair<int, int>(1, 3), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(is_white, false, pair<int, int>(1, 6), "Fou");
    place = coor_to_pos(pair<int, int>(1, 6), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(!is_white, false, pair<int, int>(8, 3), "Fou");
    place = coor_to_pos(pair<int, int>(8, 3), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(!is_white, false, pair<int, int>(8, 6), "Fou");
    place = coor_to_pos(pair<int, int>(8, 6), taillep);
    Echi.plateau[place] = fou;

    // roi
    Piece *roi = new Piece(is_white, false, pair<int, int>(1, 5), "Roi");
    place = coor_to_pos(pair<int, int>(1, 5), taillep);
    Echi.plateau[place] = roi;
    Echi.roi_blanc = roi;

    roi = new Piece(!is_white, false, pair<int, int>(8, 5), "Roi");
    place = coor_to_pos(pair<int, int>(8, 5), taillep);
    Echi.plateau[place] = roi;
    Echi.roi_noir = roi;

    // dame
    Piece *Dame = new Piece(is_white, false, pair<int, int>(1, 4), "Dame");
    place = coor_to_pos(pair<int, int>(1, 4), taillep);
    Echi.plateau[place] = Dame;

    Dame = new Piece(!is_white, false, pair<int, int>(8, 4), "Dame");
    place = coor_to_pos(pair<int, int>(8, 4), taillep);
    Echi.plateau[place] = Dame;
}

pair<int, int> operator+(pair<int, int> p1, pair<int, int> p2)
{
    return pair<int, int>(p1.first + p2.first, p1.second + p2.second);
}
pair<int, int> operator-(pair<int, int> p1, pair<int, int> p2)
{
    return pair<int, int>(p1.first - p2.first, p1.second - p2.second);
}

ostream &operator<<(ostream &out, const list<pair<int, float>> &list_temps)
{
    list<std::pair<int, float>>::const_iterator it;

    for (it = list_temps.begin(); it != list_temps.end(); it++)
        cout << "Coup" << it->first << " " << it->second << "ms\n";
}