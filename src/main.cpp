#include <string>
#include <iostream>
using namespace std;
#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
//#define std::cout std::std::cout
#define taillepp 8

int main2()
{

	bool is_fini = false;
	Echiquier *Echi = new Echiquier(taillepp);
	int taillep = Echi->taille;
	int num_tour = 0;

	bool is_coups_correct;
	int joueur_courant;
	bool is_tour_joueur1;
	bool is_white_1;
	bool is_white_courant;

	Coup *coupjoue;
	Piece *piece_jouee;
	Deplac_rel dep;
	string type_promu;

	// pour le pat
	bool is_egalite = false;
	bool is_egalite_materiel = false;
	bool is_pat = false;
	bool is_echec_perpetuel = false;
	bool is_triple_rep = false;
	bool is_50_coups = false;

	int nombre_piece_blanche = 16;
	int nombre_piece_noire = 16;
	int nbr_demi_coups_sans_prise_sans_pion = 0;

	// mise en place des pièces
	mise_en_place_echec_piece(*Echi);

	// mise en place des joueurs
	std::cout << "Bienvenue, tout d'abord choisissons qui joue: \n";

	std::cout << "Pour chaque joueur, entrez un entier sachant que : \n";
	std::cout << "1: Joueur humain \n";
	std::cout << "2: Ordi aléatoire \n";
	std::cout << "3: Ordi avec min-max profondeur ... \n";
	int joueur1, joueur2;
	std::cout << "Qui est le joueur 1 ?";
	cin >> joueur1;
	std::cout << "Qui est le joueur 2 ?";
	cin >> joueur2;

	// On ajoute un tirage au sort !
	int tirage_au_sort;
	std::cout << "\nVoulez-vous tirer au sort le joueur qui commence ?\n";
	std::cout << "Entrez un entier, sachant que :\n";
	std::cout << "1: Je veux un tirage au sort\n";
	std::cout << "2: Je ne veux pas de tirage au sort\n";
	std::cout << "Entrez un entier : ";
	cin >> tirage_au_sort;

	if (tirage_au_sort == 1)
	{
		std::cout << "On tire au sort celui qui commence ...\n";
		int debutant = tirage_alea_entier(1, 2);
		if (debutant == 1)
		{
			std::cout << "FAIT, le joueur 1 commence ! Il joue donc blanc.\n";
			is_tour_joueur1 = true;
			is_white_1 = is_tour_joueur1;
		}
		else
		{
			std::cout << "FAIT, le joueur 2 commence ! Il joue donc blanc.\n";
			is_tour_joueur1 = false;
			is_white_1 = is_tour_joueur1;
		}
	}
	else
	{
		std::cout << "Très bien, le joueur 1 commence ! Il joue donc blanc.\n";
		is_tour_joueur1 = true;
		is_white_1 = is_tour_joueur1;
	}

	while (!is_egalite && !is_fini)
	{
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

		// num_tour
		if (is_white_courant)
		{
			num_tour += 1;
		}

		// c'est à l'humain de jouer, choix du coup !
		if (joueur_courant == 1)
		{
			std::cout << "C'est au tour des ";
			if (is_white_courant)
			{
				std::cout << "Blancs.";
			}
			else
			{
				std::cout << "Noirs.";
			}
			std::cout << " Voici le plateau : \n";
			Echi->affiche();

			is_coups_correct = false;
			std::cout << "où jouer ? \n";

			string case_depart;
			string case_arrive;
			pair<int, int> case_dep;
			pair<int, int> case_arr;

			CoupSpecial coup_spe;

			while (!is_coups_correct)
			{
				std::cout << "Entrez la case de départ (ex : 'b2') :";
				cin >> case_depart;
				std::cout << "Entrez la case d'arrivée :";
				cin >> case_arrive;

				if ((case_depart.length() != 2) || (case_arrive.length() != 2))
					std::cout << "Les formats de cases ne correspondent pas à la longueur souhaitée. \n";
				else
				{
					int ligne_depart = case_depart[1] - 48;
					int ligne_arrivee = case_arrive[1] - 48;
					int colonne_depart = case_depart[0] - 96;
					int colonne_arrivee = case_arrive[0] - 96;

					if ((ligne_depart < 1) || (ligne_depart > taillep) || (ligne_arrivee < 1) || (ligne_arrivee > taillep) || (colonne_depart < 1) || (colonne_depart > taillep) || (colonne_arrivee < 1) || (colonne_arrivee > taillep))
						std::cout << "l'une des cases entrées n'existe pas. \n";
					else
					{
						case_dep = pair<int, int>(ligne_depart, colonne_depart);
						case_arr = pair<int, int>(ligne_arrivee, colonne_arrivee);
						dep = Deplac_rel(case_arr - case_dep);
						piece_jouee = Echi->plateau[coor_to_pos(case_dep, taillep)];

						if ((piece_jouee == NULL) || (piece_jouee->isWhite != is_white_courant)) // traiter cas 2 dans is_legal ?
							std::cout << "La case de départ ne correspond pas à l'une de vos pièces. \n";

						else
						{
							coup_spe = Special(*Echi, piece_jouee, dep, num_tour);
							std ::cout << coup_spe << endl;
							if (coup_spe == promotion)
							{
								std::cout << "En quelle pièce faire la promotion ? ex : 'Fou' ";
								cin >> type_promu;
								if (type_promu != "Pion" && type_promu != "Tour" && type_promu != "Fou" && type_promu != "Cavalier" && type_promu != "Dame" && type_promu != "Roi")
									std::cout << "La pièce voulue n'existe pas.\n";
								else
								{
									if (!is_legal(*Echi, piece_jouee, dep, num_tour, coup_spe, type_promu))
										std::cout << "Ce coup n'est pas légal.\n";
									else if (is_Echec(*Echi, piece_jouee, dep, num_tour, is_white_courant, type_promu, coup_spe))
									{
										std::cout << "Ce coup place votre roi en echec.\n";
									}
									else
									{
										std::cout << "Le coup est correct.\n";
										is_coups_correct = true;
									}
								}
							}
							else
							{
								type_promu = string("Pion");
								if (!is_legal(*Echi, piece_jouee, dep, num_tour, coup_spe, type_promu))
									std::cout << "Ce coup n'est pas légal.\n";

								else
								{
									bool is_ech = is_Echec(*Echi, piece_jouee, dep, num_tour, is_white_courant, type_promu, non_special);
									if (is_ech)
									{
										std::cout << "Ce coup place votre roi en echec.\n";
									}
									else
									{
										std::cout << "Le coup est correct.\n";
										is_coups_correct = true;
									}
								}
							}
						}
					}
				}
			}
			std::cout << piece_jouee->position_coor.first << "," << piece_jouee->position_coor.second << endl;

			Piece *piece_prise = taken_coup(*Echi, piece_jouee, dep, coup_spe);
			// std::cout << "piece prise ok\n";
			bool is_ech = is_Echec(*Echi, piece_jouee, dep, num_tour, !is_white_courant, type_promu, coup_spe);
			// std::cout << is_ech << endl;
			bool is_ma = is_Mat(*Echi, piece_jouee, dep, num_tour, type_promu, coup_spe, is_ech);
			// std::cout << is_ma << endl;
			coupjoue = new Coup(is_white_courant, *piece_jouee, case_arr, case_dep, num_tour, piece_prise, coup_spe, type_promu, is_ech, is_ma);
			std::cout << "Le coup est : " << *coupjoue << "\n";
		}

		//  C'est à l'ordi aléatoire de jouer, , choix du coup !
		else if (joueur_courant == 2)
		{
			std::cout << "C'est au tour des ";
			if (is_white_courant)
			{
				std::cout << "Blancs.";
			}
			else
			{
				std::cout << "Noirs.";
			}
			std::cout << " Voici le plateau : \n";
			Echi->affiche();
			coupjoue = coup_aleatoire_echecs(*Echi, is_white_courant, num_tour);
			std::cout << "Le coup est : " << *coupjoue << "\n";
		}

		// C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
		else if (joueur_courant == 3)
		{
		}

		else
		{
			std::cout << "le joueur choisi n'existe pas, recommencez \n";
			return 0;
		}

		// on joue le coup
		actualisePlateau(*Echi, *coupjoue);

		for (int i = 1; i <= taillep; i++)
		{
			for (int j = 1; j <= taillep; j++)
			{
				if ((Echi->plateau[coor_to_pos(pair<int, int>(i, j), taillep)] != NULL) && (Echi->plateau[coor_to_pos(pair<int, int>(i, j), taillep)]->position_coor != pair<int, int>(i, j)))
				{
					is_echec_perpetuel = true;
					std::cout << "PROBLEME" << i << j << endl;
				}
			}
		}
		/*
				cout << "place roi blanc :" << Echi->roi_blanc->position_coor.first
					 << "," << Echi->roi_blanc->position_coor.second << endl
					 << *Echi->roi_blanc << endl;
				cout << "place roi noir :" << Echi->roi_noir->position_coor.first
					 << "," << Echi->roi_noir->position_coor.second << endl
					 << *Echi->roi_noir << endl;
		*/

		if (coupjoue->Taken != NULL)
		{
			if (is_white_courant)
				nombre_piece_blanche -= 1;
			else
				nombre_piece_noire -= 1;
			nbr_demi_coups_sans_prise_sans_pion = 0;
		}
		else if (coupjoue->pieceJouee.type == "Pion")
			nbr_demi_coups_sans_prise_sans_pion = 0;
		else
			nbr_demi_coups_sans_prise_sans_pion += 1;
		// Est ce que la partie est terminée ?

		///////VICTOIRE ?
		is_fini = coupjoue->is_mat;

		///////EGALITE  ?

		// MATERIEL
		// roi contre roi
		if (!is_fini)
		{
			cout << "il reste" << nombre_piece_blanche << "pièces blanches et" << nombre_piece_noire << "pieces noirs." << endl;
			if ((nombre_piece_blanche == 1) && (nombre_piece_noire == 1))
			{
				is_egalite_materiel = true;
			}
			//  roi blanc contre ...
			else if ((nombre_piece_blanche == 1) && (nombre_piece_noire <= 3))
			{
				Piece **Liste_piece_noire_restante = new Piece *[2]; // on ne met pas le roi dedans
				int compteur_piece_noire_sans_roi = 0;
				for (int i = 1; i <= taillep; i++)
				{
					for (int j = 1; j <= taillep; j++)
					{
						Piece *piece_current = Echi->plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
						if ((piece_current != NULL) && (!piece_current->isWhite) && ((piece_current->type) != "Roi"))
						{
							Liste_piece_noire_restante[compteur_piece_noire_sans_roi] = piece_current;
							compteur_piece_noire_sans_roi += 1;
						}
					}
				}
				// un roi et un fou ou un  cavalier
				if ((compteur_piece_noire_sans_roi == 1) && ((Liste_piece_noire_restante[0]->type == "Fou") || (Liste_piece_noire_restante[0]->type == "Cavalier")))
					is_egalite_materiel = true;

				// un roi et deux cavaliers
				else if ((compteur_piece_noire_sans_roi == 2) && (Liste_piece_noire_restante[0]->type == "Cavalier") && (Liste_piece_noire_restante[1]->type == "Cavalier"))
					is_egalite_materiel = true;
			}
			else if ((nombre_piece_noire == 1) && (nombre_piece_blanche <= 3))
			{
				Piece **Liste_piece_blanche_restante = new Piece *[2]; // on ne met pas le roi dedans
				int compteur_piece_blanche_sans_roi = 0;
				for (int i = 1; i <= taillep; i++)
				{
					for (int j = 1; j <= taillep; j++)
					{
						Piece *piece_current = Echi->plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
						if ((piece_current != NULL) && (piece_current->isWhite) && ((piece_current->type) != "Roi"))
						{
							Liste_piece_blanche_restante[compteur_piece_blanche_sans_roi] = Echi->plateau[coor_to_pos(pair<int, int>(i, j), taillep)];
							compteur_piece_blanche_sans_roi += 1;
						}
					}
				}
				// un roi et un fou ou un  cavalier
				if ((compteur_piece_blanche_sans_roi == 1) && ((Liste_piece_blanche_restante[0]->type == "Fou") || (Liste_piece_blanche_restante[0]->type == "Cavalier")))
					is_egalite_materiel = true;

				// un roi et deux cavaliers
				else if ((compteur_piece_blanche_sans_roi == 2) && (Liste_piece_blanche_restante[0]->type == "Cavalier") && (Liste_piece_blanche_restante[1]->type == "Cavalier"))
					is_egalite_materiel = true;
			}

			else if (nbr_demi_coups_sans_prise_sans_pion >= 100)
				is_50_coups = true;

			else if (!(is_coupsPossibles(*Echi, !is_white_courant, num_tour)))
			{
				is_pat = true;
			}

			// is_echec_perpetuel; pas codé
			// is_triple_rep = false; pas codé

			if (is_egalite_materiel || is_pat || is_echec_perpetuel || is_triple_rep || is_50_coups)
				is_egalite = true;
		}

		is_tour_joueur1 = (!(is_tour_joueur1));
	}

	if (is_fini)
	{
		std::cout << "BRAVO ! Victoire du joueur ";
		std::cout << (is_white_courant ? "Blanc." : "Noir.");
		std::cout << endl
				  << "Voici un récapitulatif de la partie : \n";
		std::cout << Echi->L_coup_depuis_dep;
	}

	else if (is_egalite)
	{
		std::cout << "Cette partie ce termine par une égalité.\nLa cause est : ";
		if (is_egalite_materiel)
			std::cout << "Le matériel disponible est insuffisant pour un mat.\n";
		if (is_pat)
		{
			std::cout << "Le roi ";
			std::cout << (!is_white_courant ? "blanc" : "noir") << " est pat.\n";
		}
		if (is_echec_perpetuel)
			std::cout << "Le roi ? est en échec perpétuel\n";
		if (is_triple_rep)
			std::cout << "On est en situation de triple répétition.\n";
		if (is_50_coups)
			std::cout << "50 coups ont été joué sans prise et sans déplacement de pion.\n";

		std::cout << Echi->L_coup_depuis_dep;
	}
	return 0;
}
