
#include "ordi_aleatoire.hpp"
#include <iostream>
#include <random>
using namespace std;
#define taillepp 8

int main1()
{
    Piece *piec_test = new Piece(true, pair<int, int>(1, 1), "Cavalier");
    char premiere_lettre = piec_test->type[0];
    cout << premiere_lettre;
}