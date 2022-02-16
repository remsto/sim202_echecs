#include <iostream>
using namespace std;
#include "environnement.hpp"

int main()
{

	int taille = 8;
	bool is_ordi;	// joue-t-on en 1V1
	bool is_joueur; // est ce au joueur de jouer
	bool is_fini = false;
	Echiquier EchiTTT(taille);
	int n = 0;
	int boucle_max = 1000;
	int ligne, colonne; // pour entrer où jouer
	bool is_coups_correct;

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
			is_coups_correct = false;
			cout << "où jouer ? \n";

			while (!is_coups_correct)
			{
				cout << "Entrez la ligne :";
				cin >> ligne;

				cout << "Entrez la colonne :";
				cin >> colonne_char; // conversion
				colonne = colonne_char - 64;

				// verifiez conformité
				if (ligne > taille || ligne < 0)
				{
					cout << "la ligne ne convient pas recommencez";
				}
				else if (colonne > taille || colonne < 0)
				{
					cout << "la colonne ne convient pas recommencez";
				}
				else
				{
					is_coups_correct = true;
				}
			}

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