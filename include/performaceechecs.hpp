#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <iostream>

#include "ordi_aleatoire.hpp"
#include "ordi_min_max.hpp"
using namespace std;

#define taillepp 8

int gagnant_echecs(int joueur1, int joueur2);
void tableau_perf_echecs(int profondeur_max, int gammap, int gammac);
list<pair<int, float>> temps_chaquecoupechecs(int joueur1, int joueur2, int gammap, int gammac);
void temps_globauxechecs(int profondeur_max, int joueur2, int gammap, int gammac);

#endif