#include <iostream>
using namespace std;
#include "environnement.hpp"

int main()
{

    int taille = 3;
    bool is_joueur;
    bool is_fini = false;
    cout << "Bienvenue, tout d'abord tirons au sort qui sera le premier à jouer : \n";

    // Si le joeur commence ! Sinon sautez cette partie
    bool is_joueur = true;
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
    is_joueur = false;

    // Boucle de jeu !
    int n = 0;
    int boucle_max = 1000;
    while (n < boucle_max &is_fini = false)
    {
    }
}