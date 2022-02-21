#include "environnement.hpp"
#include <iostream>
#include <random>
using namespace std;

int main1()
{

    Piece *test = new Piece(true, pair<int, int>(0, 0), "Pion");
    string a = test->type;
    cout << "type : " << a;
    char b = (test->type).at(0);
    cout << "premiere lettre : " << b;
    char c = (test->type)[0];
    cout << " " << c;
}