
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

Deplac_rel::Deplac_rel(pair<int, int> coord, Deplac_rel *next)
{
    coor = coord;
    Next = next;
}

Deplac_rel::Deplac_rel(const Deplac_rel &dep_a_copier)
{
    coor = dep_a_copier.coor;
    Next = new Deplac_rel(*dep_a_copier.Next);
}

ostream &operator<<(ostream &out, const Deplac_rel &dep)
{
    out << "(" << dep.coor.first << "," << dep.coor.second << ")";
    return out;
}

ListDeplac_rel::ListDeplac_rel(int nbdepla, Deplac_rel *first_dep, Deplac_rel *last_dep)
{
    nb_deplacement = nbdepla;
    first = first_dep;
    last = last_dep;
}

ostream &operator<<(ostream &out, const ListDeplac_rel &listDep)
{
    Deplac_rel *dep_current = listDep.first;
    out << listDep.nb_deplacement << " : "
        << "[";
    while (dep_current != NULL)
    {
        out << *dep_current << ";";
        dep_current = dep_current->Next;
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
        Deplac_rel *dep_pion1 = new Deplac_rel(pair<int, int>(1, 0), NULL);
        Deplac_rel *dep_pion2 = new Deplac_rel(pair<int, int>(1, 1), dep_pion1);
        Deplac_rel *dep_pion3 = new Deplac_rel(pair<int, int>(1, -1), dep_pion2);
        Deplac_rel *dep_pion4 = new Deplac_rel(pair<int, int>(2, 0), dep_pion3);
        Deplac_rel *dep_pion5 = new Deplac_rel(pair<int, int>(-1, 0), dep_pion4);
        Deplac_rel *dep_pion6 = new Deplac_rel(pair<int, int>(-1, -1), dep_pion5);
        Deplac_rel *dep_pion7 = new Deplac_rel(pair<int, int>(-1, 1), dep_pion6);
        Deplac_rel *dep_pion8 = new Deplac_rel(pair<int, int>(-2, 0), dep_pion7);

        deplac_relatif = ListDeplac_rel(8, dep_pion8, dep_pion1);
    }
    else if (type == "Tour")
    {
        valeur = 5;

        Deplac_rel *dep_tour = new Deplac_rel(pair<int, int>(1, 0), NULL);
        Deplac_rel *last_dep = dep_tour;
        for (int i = 2; i <= 7; i++)
        {
            dep_tour = new Deplac_rel(pair<int, int>(i, 0), dep_tour);
        }
        for (int i = 1; i <= 7; i++)
        {
            dep_tour = new Deplac_rel(pair<int, int>(-i, 0), dep_tour);
            dep_tour = new Deplac_rel(pair<int, int>(0, i), dep_tour);
            dep_tour = new Deplac_rel(pair<int, int>(0, -i), dep_tour);
        }
        deplac_relatif = ListDeplac_rel(28, dep_tour, last_dep);
    }

    else if (type == "Cavalier")
    {
        valeur = 3;

        Deplac_rel *dep_cavalier1 = new Deplac_rel(pair<int, int>(-1, -2), NULL);
        Deplac_rel *dep_cavalier2 = new Deplac_rel(pair<int, int>(-1, 2), dep_cavalier1);
        Deplac_rel *dep_cavalier3 = new Deplac_rel(pair<int, int>(1, -2), dep_cavalier2);
        Deplac_rel *dep_cavalier4 = new Deplac_rel(pair<int, int>(1, 2), dep_cavalier3);
        Deplac_rel *dep_cavalier5 = new Deplac_rel(pair<int, int>(-2, -1), dep_cavalier4);
        Deplac_rel *dep_cavalier6 = new Deplac_rel(pair<int, int>(-2, 1), dep_cavalier5);
        Deplac_rel *dep_cavalier7 = new Deplac_rel(pair<int, int>(2, -1), dep_cavalier6);
        Deplac_rel *dep_cavalier8 = new Deplac_rel(pair<int, int>(2, 1), dep_cavalier7);

        deplac_relatif = ListDeplac_rel(8, dep_cavalier8, dep_cavalier1);
    }

    else if (type == "Fou")
    {
        valeur = 3;

        Deplac_rel *dep_fou = new Deplac_rel(pair<int, int>(1, 1), NULL);
        Deplac_rel *last_dep = dep_fou;

        for (int i = 2; i <= 7; i++)
        {
            dep_fou = new Deplac_rel(pair<int, int>(i, i), dep_fou);
        }
        for (int i = 1; i <= 7; i++)
        {
            dep_fou = new Deplac_rel(pair<int, int>(i, -i), dep_fou);
            dep_fou = new Deplac_rel(pair<int, int>(-i, -i), dep_fou);
            dep_fou = new Deplac_rel(pair<int, int>(-i, i), dep_fou);
        }
        deplac_relatif = ListDeplac_rel(28, dep_fou, last_dep);
    }
    else if (type == "Roi")
    {
        valeur = 100; // arbitraire, à réfléchir

        Deplac_rel *dep_roi1 = new Deplac_rel(pair<int, int>(-1, -1), NULL);
        Deplac_rel *dep_roi2 = new Deplac_rel(pair<int, int>(0, -1), dep_roi1);
        Deplac_rel *dep_roi3 = new Deplac_rel(pair<int, int>(1, -1), dep_roi2);
        Deplac_rel *dep_roi4 = new Deplac_rel(pair<int, int>(1, 0), dep_roi3);
        Deplac_rel *dep_roi5 = new Deplac_rel(pair<int, int>(-1, 0), dep_roi4);
        Deplac_rel *dep_roi6 = new Deplac_rel(pair<int, int>(-1, 1), dep_roi5);
        Deplac_rel *dep_roi7 = new Deplac_rel(pair<int, int>(0, -1), dep_roi6);
        Deplac_rel *dep_roi8 = new Deplac_rel(pair<int, int>(1, 1), dep_roi7);
        Deplac_rel *dep_roi9 = new Deplac_rel(pair<int, int>(0, -3), dep_roi8); // pour roquer, a reflechir
        Deplac_rel *dep_roi10 = new Deplac_rel(pair<int, int>(0, 2), dep_roi9); // pour roquer, a reflechir

        deplac_relatif = ListDeplac_rel(10, dep_roi10, dep_roi1);
    }
    else if (type == "Dame")
    {
        valeur = 9;

        Deplac_rel *dep_Dame = new Deplac_rel(pair<int, int>(1, 0), NULL);

        Deplac_rel *last_dep = dep_Dame;
        for (int i = 2; i <= 7; i++)
        {
            // colonnes et lignes
            dep_Dame = new Deplac_rel(pair<int, int>(i, 0), dep_Dame);
        }
        for (int i = 1; i <= 7; i++)
        {
            dep_Dame = new Deplac_rel(pair<int, int>(-i, 0), dep_Dame);
            dep_Dame = new Deplac_rel(pair<int, int>(0, i), dep_Dame);
            dep_Dame = new Deplac_rel(pair<int, int>(0, -i), dep_Dame);

            // diagonales
            dep_Dame = new Deplac_rel(pair<int, int>(i, i), dep_Dame);
            dep_Dame = new Deplac_rel(pair<int, int>(i, -i), dep_Dame);
            dep_Dame = new Deplac_rel(pair<int, int>(-i, -i), dep_Dame);
            dep_Dame = new Deplac_rel(pair<int, int>(-i, i), dep_Dame);
        }
        deplac_relatif = ListDeplac_rel(56, dep_Dame, last_dep);
    }
    else
    {
        valeur = 1;
        deplac_relatif = ListDeplac_rel();
    }
}

// class Piece

Piece::Piece(bool isWhit, pair<int, int> coor, string type) : TypePiece(type)
{
    isWhite = isWhit;
    position_coor = coor;
}

Piece::Piece(const Piece &piece_a_copier) : TypePiece(piece_a_copier.type)
{
    isWhite = piece_a_copier.isWhite;
    position_coor = piece_a_copier.position_coor;
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

// class Echiquier

Echiquier::Echiquier(int n)
{
    this->taille = n;
    this->plateau = new Piece *[n * n];
    for (int i = 0; i < n * n; i++)
    {
        this->plateau[i] = NULL;
    }
}

Echiquier::~Echiquier()
{
    for (int i = 0; i < taille * taille; i++)
    {
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
        Piece *pion = new Piece(is_white, pair<int, int>(2, j), "Pion");
        place = coor_to_pos(pair<int, int>(2, j), taillep);
        Echi.plateau[place] = pion;

        // noir
        pion = new Piece(!is_white, pair<int, int>(7, j), "Pion");
        place = coor_to_pos(pair<int, int>(7, j), taillep);
        Echi.plateau[place] = pion;
    }

    // tour
    Piece *tour = new Piece(is_white, pair<int, int>(1, 1), "Tour");
    place = coor_to_pos(pair<int, int>(1, 1), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(is_white, pair<int, int>(1, 8), "Tour");
    place = coor_to_pos(pair<int, int>(1, 8), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(!is_white, pair<int, int>(8, 1), "Tour");
    place = coor_to_pos(pair<int, int>(8, 1), taillep);
    Echi.plateau[place] = tour;

    tour = new Piece(!is_white, pair<int, int>(8, 8), "Tour");
    place = coor_to_pos(pair<int, int>(8, 8), taillep);
    Echi.plateau[place] = tour;

    // Cavalier
    Piece *cavalier = new Piece(is_white, pair<int, int>(1, 2), "Cavalier");
    place = coor_to_pos(pair<int, int>(1, 2), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(is_white, pair<int, int>(1, 7), "Cavalier");
    place = coor_to_pos(pair<int, int>(1, 7), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(!is_white, pair<int, int>(8, 2), "Cavalier");
    place = coor_to_pos(pair<int, int>(8, 2), taillep);
    Echi.plateau[place] = cavalier;

    cavalier = new Piece(!is_white, pair<int, int>(8, 7), "Cavalier");
    place = coor_to_pos(pair<int, int>(8, 7), taillep);
    Echi.plateau[place] = cavalier;

    // fou
    Piece *fou = new Piece(is_white, pair<int, int>(1, 3), "Fou");
    place = coor_to_pos(pair<int, int>(1, 3), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(is_white, pair<int, int>(1, 6), "Fou");
    place = coor_to_pos(pair<int, int>(1, 6), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(!is_white, pair<int, int>(8, 3), "Fou");
    place = coor_to_pos(pair<int, int>(8, 3), taillep);
    Echi.plateau[place] = fou;

    fou = new Piece(!is_white, pair<int, int>(8, 6), "Fou");
    place = coor_to_pos(pair<int, int>(8, 6), taillep);
    Echi.plateau[place] = fou;

    // roi
    Piece *roi = new Piece(is_white, pair<int, int>(1, 5), "Roi");
    place = coor_to_pos(pair<int, int>(1, 5), taillep);
    Echi.plateau[place] = roi;
    Echi.roi_blanc = roi;

    roi = new Piece(!is_white, pair<int, int>(8, 5), "Roi");
    place = coor_to_pos(pair<int, int>(8, 5), taillep);
    Echi.plateau[place] = roi;
    Echi.roi_noir = roi;

    // dame
    Piece *Dame = new Piece(is_white, pair<int, int>(1, 4), "Dame");
    place = coor_to_pos(pair<int, int>(1, 4), taillep);
    Echi.plateau[place] = Dame;

    Dame = new Piece(!is_white, pair<int, int>(8, 4), "Dame");
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