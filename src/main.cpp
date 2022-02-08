#include <iostream>
using namespace std;
#include "environnement.hpp"

int main2()
{
	int taille = 3;
	cout << "Bienvenue, tout d'abord tirons au sort qui sera le premier à jouer :";
	cout << "Le joueur commence !";
	cout << "Voici le plateau :";

	Echiquier EchiTTT(taille);
	EchiTTT.affiche3();

	int ligne, colonne;
	cin >> ligne;
	cin >> colonne;
}