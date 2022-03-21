#include <iostream>
using namespace std;
#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
//#define cout std::cout
#define taillepp 3

int gagnant_TTT(int joueur1, int joueur2)
{
    bool is_fini = false;
    Echiquier *EchiTTT = new Echiquier(taillepp);
    int taillep = EchiTTT->taille;
    int num_tour = 0;
    char ligne_char;
    int ligne;
    char colonne_char;
    int colonne; // pour entrer où jouer
    bool is_coups_correct;
    int joueur_courant;
    bool is_tour_joueur1;
    bool is_white_1;
    bool is_white_courant;
    int profondeur;
    pair<int, int> p;
    int gagnant;

    Coup *coupjoue;
    Piece *piece_jouee;

    is_tour_joueur1 = true;
    is_white_1 = is_tour_joueur1;

    while (!is_fini)
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
        if (joueur_courant == 0)
        {
            coupjoue = coup_aleatoire_TTT(*EchiTTT, is_white_courant, num_tour);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        // C'est à l'ordi aléatoire de jouer, , choix du coup !
        else if (joueur_courant == 1)
        {
            profondeur = 1;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        // C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
        else if (joueur_courant == 2)
        {
            profondeur = 2;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 3)
        {
            profondeur = 3;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 4)
        {
            profondeur = 4;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 5)
        {
            profondeur = 5;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 6)
        {
            profondeur = 6;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 7)
        {
            profondeur = 7;
            // cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(EchiTTT, is_white_courant, num_tour, profondeur);
            // cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        else
        {
            cout << "le joueur choisi n'existe pas, recommencez \n";
            return 0;
        }

        // on joue le coup

        actualisePlateau(*EchiTTT, *coupjoue);
        // cout << "Voici le déplacement effectué : \n";
        // EchiTTT->affiche();
        is_fini = coupjoue->is_mat;
        if (is_fini)
        {
            // cout << "Victoire du joueur ";
            // cout << (is_white_courant ? "Blanc" : "Noir");
            // cout << "!";
            gagnant = (is_white_courant == is_white_1 ? joueur1 : joueur2);
            return gagnant;
        }
        else
        {
            if (is_coupsPossiblesTTT(*EchiTTT, !is_white_courant, num_tour))
            {
                // cout << "Pas de Victoire, on continue ! \n";
            }
            else
            {
                // cout << "Egalité !\n";
                is_fini = true;
                return -1;
            }
        }
        is_tour_joueur1 = (!(is_tour_joueur1));
    }
    return 0;
}

void tableau_perf_TTT()
{
    int nbr_egal = 0;
    int nbr_vic1 = 0;
    int nbr_vic2 = 0;
    int nbr_partie = 100;

    for (int joueur1 = 0; joueur1 <= 4; joueur1++)
        for (int joueur2 = 0; joueur2 <= 4; joueur2++)
        {
            nbr_egal = 0;
            nbr_vic1 = 0;
            nbr_vic2 = 0;
            for (int k = 0; k < nbr_partie; k++)
            {
                int gagnant = gagnant_TTT(joueur1, joueur2);
                if (gagnant == -1)
                    nbr_egal += 1;
                else if (gagnant == joueur1)
                    nbr_vic1 += 1;
                else if (gagnant == joueur2)
                    nbr_vic2 += 1;
            }

            if (joueur1 == 0)
                cout << "Joueur aléatoire";
            else
                cout << "Joueur Min-max profondeur" << joueur1;
            cout << " contre ";
            if (joueur2 == 0)
                cout << "Joueur aléatoire";
            else
                cout << "Joueur Min-max profondeur" << joueur2;
            cout << "--> V1:" << nbr_vic1 << " V2:" << nbr_vic2 << " E:" << nbr_egal << endl;
        }
}