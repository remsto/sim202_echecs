using namespace std;
#include <vector>
#include <iostream>
#include "environnement.hpp"

/*
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

// class TypePiece

TypePiece::TypePiece(string type)
{
    this->type = type;
    this->deplac_relatif = vector<pair<int, int>>();
    this->valeur = 1;
}

// class Piece

Piece::Piece(bool isWhit, pair<int, int> coor, string type) : TypePiece(type)
{
    this->isWhite = isWhit;
    this->position_coor = coor;
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

void Echiquier::affiche3() const
{
    cout << "  A  B  C\n";
    for (int i = 0; i < taille * taille; i++)
    {
        Piece *piece = plateau[i];
        if (i % taille == 0)
        {
            cout << i / taille + 1 << " ";
        }
        if (piece == NULL)
        {
            cout << "   ";
        }
        else
        {
            cout << piece->type[0]; // P ou D ou R ou ...
            if (piece->isWhite)
            {
                cout << "b";
            }
            else
            {
                cout << "n";
            }
            cout << " ";
        }
        // ajout des retours à la ligne
        if (i % taille == taille - 1)
            cout << "\n";
    }
}

/*
CLASSE ET FONCTIONS TTT
*/

int coor_to_pos_TTT(pair<int, int> p)
{
    int n = (p.first - 1) * 3 + (p.second - 1);
    return n;
}

pair<int, int> pos_to_coor_TTT(int n)
{
    pair<int, int> p((n / 3) + 1, (n % 3) + 1);
    return p;
}

/*
CLASSE ET FONCTIONS ECHECS
*/

int coor_to_pos(pair<int, int> p)
{
    int n = (p.first - 1) * 8 + (p.second - 1);
    return n;
}

pair<int, int> pos_to_coor(int n)
{
    pair<int, int> p((n / 8) + 1, (n % 8) + 1);
    return p;
}
