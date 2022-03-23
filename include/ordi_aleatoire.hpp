#ifndef ORDI_ALEATOIRE_HPP
#define ORDI_ALEATOIRE_HPP

#include <iostream>
#include <random>
#include "environnement.hpp"
#include "pour_jouer.hpp"

Coup *coup_aleatoire_TTT(const Echiquier &Echi, bool is_white, int num_tour);

Coup *coup_aleatoire_echecs(Echiquier &Echi, bool is_white, int num_tour);
#endif
