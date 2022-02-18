#include "ordi_aleatoire.hpp"

#include <iostream>
#include <random>
#include <ctime>

Coup *coup_aleatoire_TTT(const Echiquier &Echi, bool is_white)
{
    ListeCoups *Liste_possible = coupsPossiblesTTT(Echi, is_white);
    int nbc = Liste_possible->nbCoups;
    int choix_coup = tirage_alea_entier(1, nbc);
    Coup *coup_choisi = Liste_possible->first;
    for (int i = 1; i < choix_coup; i++)
    {
        coup_choisi = coup_choisi->Next;
    }
    Coup *a_retourner = new Coup(*coup_choisi);
    Liste_possible->~ListeCoups();
    return a_retourner;
}