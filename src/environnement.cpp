
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "environnement.hpp"
using namespace std;

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS


pour info :


3| 6 | 7 | 8 |
2| 3 | 4 | 5 |
1| 0 | 1 | 2 |
   1   2   3
*/

// class TypePiece

TypePiece::TypePiece(string type)
{
    type = type;
    deplac_relatif = vector<pair<int, int>>();
    valeur = 1;
}

// class Piece

Piece::Piece(bool isWhit, pair<int, int> coor, string type) : TypePiece(type)
{
    isWhite = isWhit;
    position_coor = coor;
}

Piece::Piece() : TypePiece()
{
    isWhite = true;
    position_coor = pair<int, int>(0, 0);
}

ostream &operator<<(ostream &out, const Piece &piece)
{
    out << "P";
    // cout << (piece.type[0]); // P ou D ou R ou ...
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
        std::cout << "   --------------\n";
        std::cout << i << " |";

        for (int j = 1; j <= taille; j++)
        {
            Piece *piece = plateau[coor_to_pos(pair<int, int>(i, j))];
            if (piece == NULL)
            {
                std::cout << "    |";
            }
            else
            {
                std::cout << " " << *piece;
                std::cout << " |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "   --------------\n";
    std::cout << "     A    B    C  \n";
}

int coor_to_pos(pair<int, int> p)
{
    int n = (p.first - 1) * taillep + (p.second - 1);
    return n;
}

pair<int, int> pos_to_coor(int n)
{
    pair<int, int> p((n / taillep) + 1, (n % taillep) + 1);
    return p;
}

ostream &operator<<(ostream &out, const pair<int, int> &pair)
{
    out << "(" << pair.first << ",";
    int colonne_int = pair.second;
    if (colonne_int == 0)
    {
        out << colonne_int << ")";
    }
    else
    {
        char colonne = pair.second + 64;
        out << colonne << ")";
    }
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