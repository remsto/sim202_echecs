#include <iostream>
using namespace std;
#include "environnement.hpp"

int main()
{

    int taille = 3;
    cout << "Bienvenue, tout d'abord tirons au sort qui sera le premier à jouer : \n";
    cout << "Le joueur commence ! Il joue donc blanc.\n";
    cout << "Voici le plateau : \n";

    Echiquier EchiTTT(taille);
    EchiTTT.affiche3();

    cout << "où jouer ? \n";
    int ligne, colonne;
    cout << "Entrez la ligne :";
    cin >> ligne;
    cout << "Entrez la colonne :";
    cin >> colonne;

    pair<int, int> p(ligne, colonne);

    EchiTTT.plateau[coor_to_pos_TTT(p)] = new Piece(true, p);

    EchiTTT.affiche3();
}