#include "environnement.hpp"
#include <iostream>
#include <random>

int main3()
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(1, 4);

    for (int n = 0; n < 100; n++)
    {
        cout << distr(eng) << ";";
    }
    cout << "\n L'autre \n";
    return 0;
}