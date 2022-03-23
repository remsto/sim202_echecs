#ifndef PERFORMANCETTT_HPP
#define PERFORMANCETTT_HPP

#include <iostream>

#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
using namespace std;

#define taillepp 3

int gagnant_TTT(int joueur1, int joueur2);
void tableau_perf_TTT(int profondeur_max);
list<pair<int, float>> temps_chaquecoupTTT(int joueur1, int joueur2);
void temps_globauxTTT(int profondeur_max, int joueur2);

#endif