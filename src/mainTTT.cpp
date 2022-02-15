#include <iostream>
using namespace std;
#include "environnement.hpp"

int main()
{

    int taille = 3;
    bool is_joueur; // est ce qu joueur de jouer
    bool is_fini = false;
    Echiquier EchiTTT(taille);
    int n = 0;
    int boucle_max = 1000;
    int ligne, colonne; // pour entrer où jouer

    // Tirez au sort celui qui commence
    cout << "Bienvenue, tout d'abord tirons au sort qui sera le premier à jouer : \n";
    is_joueur = true;
    bool is_whit_joueur = true;
    cout << "Le joueur commence ! Il joue donc blanc.\n";

    // Boucle de jeu !
    while (n < boucle_max && !is_fini)
    {
        n += 1;
        cout << " coucou";
        // c'est au joueur de faire un choix
        if (is_joueur)
        {
            cout << "Voici le plateau : \n";
            EchiTTT.affiche3();
            cout << "où jouer ? \n";

                        cout << "Entrez la ligne :";
            cin >> ligne;
            // vérifier conformité de l'entrée
            cout << "Entrez la colonne :";
            cin >> colonne;
            // vérifier conformité de l'entrée

            pair<int, int> p(ligne, colonne);

            EchiTTT.plateau[coor_to_pos_TTT(p)] = new Piece(is_whit_joueur, p);
            EchiTTT.affiche3();
            is_joueur = false;
            is_fini = true;
        }

        // C'est à l'ordi de jouer
        else
        {
            cout << "flemme";
        }
    }
}