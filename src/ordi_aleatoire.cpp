#include "ordi_aleatoire.hpp"

#include <iostream>
#include <random>
#include <ctime>

Coup *coup_aleatoire_TTT(const Echiquier &Echi, bool is_white, int num_tour)
{
    list<Coup> Liste_possible = coupsPossiblesTTT(Echi, is_white, num_tour);
    int nbc = Liste_possible.size(); // taille liste
    int choix_coup = tirage_alea_entier(1, nbc);

    list<Coup>::iterator it;
    it = Liste_possible.begin();
    for (int i = 1; i < choix_coup; i++)
    {
        it++;
    }
    Coup *a_retourner = new Coup(*it);
    // Liste_possible->~ListeCoups();
    return a_retourner;
}

Coup *coup_aleatoire_echecs(Echiquier &Echi, bool is_white, int num_tour)
{
    list<Coup> Liste_possible = coupsPossibles(Echi, is_white, num_tour);
    int nbc = Liste_possible.size();
    // cout << "Il existe " << nbc << " coups possibles.\n";
    int choix_coup = tirage_alea_entier(1, nbc);
    // cout << "Le coup aléa choisi est le numéro " << choix_coup << endl;
    list<Coup>::iterator it;
    it = Liste_possible.begin();
    for (int i = 1; i < choix_coup; i++)
    {
        it++;
    }
    Coup *a_retourner = new Coup(*it);
    // Liste_possible->~ListeCoups();
    return a_retourner;
}