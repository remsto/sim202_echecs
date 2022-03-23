#include <iostream>
#include <chrono>
using namespace std;
#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
//#define std::cout std::cout
#define taillepp 8

int gagnant_echecs(int joueur1, int joueur2, int gammap, int gammac)
{
    bool gagnant;
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
    int profondeur = 0;
    bool is_triple_rep = false;
    bool is_50_coups = false;

    int nombre_piece_blanche = 16;
    int nombre_piece_noire = 16;
    int nbr_demi_coups_sans_prise_sans_pion = 0;

    // mise en place des pièces
    mise_en_place_echec_piece(*Echi);

    is_tour_joueur1 = true;
    is_white_1 = is_tour_joueur1;

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

        if (joueur_courant == 0)
        {
            coupjoue = coup_aleatoire_echecs(*Echi, is_white_courant, num_tour);
            // std::cout << "Le coup est : " << *coupjoue << "\n";
        }

        else if (joueur_courant == 1)
        {
            profondeur = 1;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        // C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
        else if (joueur_courant == 2)
        {
            profondeur = 2;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 3)
        {
            profondeur = 3;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 4)
        {
            profondeur = 4;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 5)
        {
            profondeur = 5;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 6)
        {
            profondeur = 6;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
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
        is_tour_joueur1 = (!(is_tour_joueur1));

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
            // std::cout << "il reste" << nombre_piece_blanche << "pièces blanches et" << nombre_piece_noire << "pieces noirs." << endl;
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
    }

    if (is_fini)
    {
        gagnant = (is_white_courant == is_white_1 ? joueur1 : joueur2);
        return gagnant;
    }

    else if (is_egalite)
    {
        return -1;
    }

    return 0;
}

void tableau_perf_echecs(int profondeur_max, int gammap, int gammac)
{
    int nbr_egal = 0;
    int nbr_vic1 = 0;
    int nbr_vic2 = 0;
    int nbr_partie = 10;

    for (int joueur1 = 0; joueur1 <= profondeur_max; joueur1++)
        for (int joueur2 = 0; joueur2 <= 4; joueur2++)
        {
            nbr_egal = 0;
            nbr_vic1 = 0;
            nbr_vic2 = 0;
            for (int k = 0; k < nbr_partie; k++)
            {
                int gagnant = gagnant_echecs(joueur1, joueur2, gammap, gammac);
                if (gagnant == -1)
                    nbr_egal += 1;
                else if (gagnant == joueur1)
                    nbr_vic1 += 1;
                else if (gagnant == joueur2)
                    nbr_vic2 += 1;
            }

            if (joueur1 == 0)
                std::cout << "Joueur aléatoire";
            else
                std::cout << "Joueur Min-max profondeur" << joueur1;
            std::cout << " contre ";
            if (joueur2 == 0)
                std::cout << "Joueur aléatoire";
            else
                std::cout << "Joueur Min-max profondeur" << joueur2;
            std::cout << "--> V1:" << nbr_vic1 << " V2:" << nbr_vic2 << " E:" << nbr_egal << endl;
        }
}

list<pair<int, float>> temps_chaquecoupechecs(int joueur1, int joueur2, int gammap, int gammac) // contre un ordi aleatoire
{
    list<pair<int, float>> list_temps_coup;
    float temps_coup;
    bool gagnant;
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
    int profondeur = 0;
    bool is_triple_rep = false;
    bool is_50_coups = false;

    int nombre_piece_blanche = 16;
    int nombre_piece_noire = 16;
    int nbr_demi_coups_sans_prise_sans_pion = 0;

    // mise en place des pièces
    mise_en_place_echec_piece(*Echi);

    is_tour_joueur1 = true;
    is_white_1 = is_tour_joueur1;

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

        auto start = std::chrono::high_resolution_clock::now();
        if (joueur_courant == 0)
        {
            coupjoue = coup_aleatoire_echecs(*Echi, is_white_courant, num_tour);
            // std::cout << "Le coup est : " << *coupjoue << "\n";
        }

        else if (joueur_courant == 1)
        {
            profondeur = 1;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        // C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
        else if (joueur_courant == 2)
        {
            profondeur = 2;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 3)
        {
            profondeur = 3;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 4)
        {
            profondeur = 4;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 5)
        {
            profondeur = 5;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }
        else if (joueur_courant == 6)
        {
            profondeur = 6;
            // std::cout << "Le joueur minmax recherche un coup de profondeur" << profondeur << " ... ";
            coupjoue = coup_min_max(Echi, is_white_courant, num_tour, profondeur, gammap, gammac);
            // std::cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        else
        {
            std::cout << "le joueur choisi n'existe pas, recommencez \n";
            list<pair<int, float>> l;
            return l;
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> float_ms = end - start;

        temps_coup = float_ms.count();
        pair<int, float> a_add_temps(num_tour, temps_coup);
        if (is_white_1 == is_white_courant)
            list_temps_coup.push_back(a_add_temps);

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
            // std::cout << "il reste" << nombre_piece_blanche << "pièces blanches et" << nombre_piece_noire << "pieces noirs." << endl;
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
        return list_temps_coup;
    }

    else if (is_egalite)
    {
        return list_temps_coup;
    }
    return list_temps_coup;
}

void temps_globauxechecs(int profondeur_max, int joueur2, int gammap, int gammac)
{
    for (int joueur1 = 0; joueur1 <= profondeur_max; joueur1++)
    {

        list<pair<int, float>> resultat = temps_chaquecoupechecs(joueur1, joueur2, gammap, gammac);

        if (joueur1 == 0)
            std::cout << "Joueur aléatoire";
        else
            std::cout << "Joueur Min-max profondeur" << joueur1;
        std::cout << " a les performances en temps suivantes : \n";
        std::cout << resultat;
        std::cout << endl;
    }
}