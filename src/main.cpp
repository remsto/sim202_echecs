#include <iostream>
using namespace std;
#include "ordi_aleatoire.hpp"
//#define cout std::cout

int main()
{

	bool is_fini = false;
	Echiquier *EchiTTT = new Echiquier(taillep);
	int n = 0;
	int boucle_max = taillep * taillep;
	int ligne;
	char colonne_char;
	int colonne; // pour entrer où jouer
	bool is_coups_correct;
	int joueur_courant;
	bool is_tour_joueur1;
	bool is_white_1;
	bool is_white_courant;
	pair<int, int> p;

	Coup *coupjoue;
	Piece *piece_jouee;

	ListeCoups *historique_coups = new ListeCoups();

	// Tirez au sort celui qui commence
	cout << "Bienvenue, tout d'abord choisissons qui joue: \n";

	cout << "Pour chaque joueur, entrez un entier sachant que : \n";
	cout << "1: Joueur humain \n";
	cout << "2: Ordi aléatoire \n";
	cout << "3: Ordi avec min-max profondeur ... \n";
	int joueur1, joueur2;
	cout << "Qui est le joueur 1 ?";
	cin >> joueur1;
	cout << "Qui est le joueur 2 ?";
	cin >> joueur2;

	// ajoutez un tirage au sort ???

	cout << "Le joueur 1 commence ! Il joue donc blanc.\n";

	is_tour_joueur1 = true;
	is_white_1 = is_tour_joueur1;

	while (n < boucle_max && !is_fini)
	{
		n += 1; // a enlever a terme

		// a qui est-ce de jouer ?
		if (is_tour_joueur1)
		{
			joueur_courant = joueur1;
			is_white_courant = is_white_1;
		}
		else
		{
			joueur_courant = joueur2;
			is_white_courant = (!is_white_1);
		}

		// c'est à l'humain de jouer, choix du coup !
		if (joueur_courant == 1)
		{
			cout << "Voici le plateau : \n";
			EchiTTT->affiche();

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
				if (ligne > taillep || ligne <= 0)
				{
					cout << "la ligne ne conviennt pas, recommencez \n";
				}
				else if (colonne > taillep || colonne <= 0)
				{
					cout << "la colonne ne convient pas, recommencez \n";
				}
				else
				{
					p = pair<int, int>(ligne, colonne);
					if (EchiTTT->plateau[coor_to_pos(p)] != NULL)
					{
						cout << "la case est déjà occupée, recommencez\n";
					}
					else
					{
						is_coups_correct = true;
					}
				}
			}

			piece_jouee = new Piece(is_white_courant);
			coupjoue = new Coup(is_white_courant, *piece_jouee, p, piece_jouee->position_coor);
			cout << *coupjoue << "\n";
		}

		// C'est à l'ordi aléatoire de jouer, , choix du coup !
		else if (joueur_courant == 2)
		{
			coupjoue = coup_aleatoire_TTT(*EchiTTT, is_white_courant);
			cout << *coupjoue << "\n";
		}

		// C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
		else if (joueur_courant == 3)
		{
		}

		else
		{
			cout << "le joueur choisi n'existe pas, recommencez \n";
			return 0;
		}

		// on joue le coup

		actualisePlateau(*EchiTTT, *coupjoue);
		cout << "Voici le déplacement effectué : \n";
		EchiTTT->affiche();
		addCoup(historique_coups, *coupjoue);
		is_fini = is_coup_gagnant(*EchiTTT, *coupjoue);
		if (is_fini)
		{
			cout << "Victoire";
		}
		else
		{
			if (n != boucle_max)
			{
				cout << "Pas de Victoire, on continue ! \n";
			}
			else
			{
				cout << "Egalité !\n";
			}
		}
		is_tour_joueur1 = (!(is_tour_joueur1));
	}
	return 0;
}