#include <string>
#include <iostream>
using namespace std;
#include "partieechecs.hpp"
#include "partieTTT.hpp"
#include "performanceTTT.hpp"
#include "performaceechecs.hpp"

int main()
{
    cout << "Que voulez-vous faire ?\n";
    cout << "1: Jouer une partie de morpion\n";
    cout << "2: Jouer une partie d'echecs\n";
    cout << "3: Tester les performances de victoire sur le morpion\n";
    cout << "4: Tester les performances en temps sur le morpion\n";
    cout << "5: Tester les performances de victoire sur les echecs\n";
    cout << "6: Tester les performances en temps sur les echecs\n";
    cout << "Votre choix :";

    int choix;
    cin >> choix;
    cout << endl;

    if (choix == 1)
    {
        int ok;
        ok = partie_morpion();
    }
    if (choix == 2)
    {
        int gammap;
        int gammac;
        cout << "Quelle doit etre la valeur de gammap ?(int)";
        cin >> gammap;
        cout << "Quelle doit etre la valeur de gammac ?(int)";
        cin >> gammac;
        cout << endl;
        int ok;
        ok = partie_echecs(gammap, gammac);
    }
    if (choix == 3)
    {
        cout << "A quelle profondeur de min max aller au maximum ?";
        int profondeur_max;
        cin >> profondeur_max;
        tableau_perf_TTT(profondeur_max);
    }
    if (choix == 4)
    {
        cout << "A quelle profondeur de min max aller au maximum ?";
        int profondeur_max;
        cin >> profondeur_max;
        int joueur2 = 0;
        temps_globauxTTT(profondeur_max, joueur2);
    }
    if (choix == 5)
    {
        cout << "A quelle profondeur de min max aller au maximum ?";
        int profondeur_max, gammap, gammac;
        cin >> profondeur_max;
        cout << "Quelle doit etre la valeur de gammap ?(int)";
        cin >> gammap;
        cout << "Quelle doit etre la valeur de gammac ?(int)";
        cin >> gammac;
        cout << endl;
        tableau_perf_echecs(profondeur_max, gammap, gammac);
    }
    if (choix == 6)
    {
        cout << "A quelle profondeur de min max aller au maximum ?";
        int profondeur_max, gammap, gammac;
        cin >> profondeur_max;
        int joueur2 = 0;
        cout << "Quelle doit etre la valeur de gammap ?(int)";
        cin >> gammap;
        cout << "Quelle doit etre la valeur de gammac ?(int)";
        cin >> gammac;
        temps_globauxechecs(profondeur_max, joueur2, gammap, gammac);
    }
    return 0;
}