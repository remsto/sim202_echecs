#include <iostream>
using namespace std;
#include "ordi_aleatoire.hpp"
//#define cout std::cout
#define taillepp 3

int main2()
{

    bool is_fini = false;
    Echiquier *EchiTTT = new Echiquier(taillepp);
    int taillep = EchiTTT->taille;
    int num_tour = 0;
    int boucle_max = taillep * taillep;
    int ligne;
    char colonne_char;
    int colonne; // pour entrer où jouer
    bool is_coups_correct;
    int joueur_courant;
    bool is_tour_joueur1;
    bool is_white_1;
    bool is_white_courant;
    pair<int, int> p;

    Coup *coupjoue;
    Piece *piece_jouee;

    ListeCoups *historique_coups = new ListeCoups();

    // Tirez au sort celui qui commence
    cout << "Bienvenue, tout d'abord choisissons qui joue: \n";

    cout << "Pour chaque joueur, entrez un entier sachant que : \n";
    cout << "1: Joueur humain \n";
    cout << "2: Ordi aléatoire \n";
    cout << "3: Ordi avec min-max profondeur ... \n";
    int joueur1, joueur2;
    cout << "Qui est le joueur 1 ?";
    cin >> joueur1;
    cout << "Qui est le joueur 2 ?";
    cin >> joueur2;

    // On ajoute un tirage au sort !
    int tirage_au_sort;
    cout << "\nVoulez-vous tirer au sort le joueur qui commence ?\n";
    cout << "Entrez un entier, sachant que :\n";
    cout << "1: Je veux un tirage au sort\n";
    cout << "2: Je ne veux pas de tirage au sort\n";
    cout << "Entrez un entier : ";
    cin >> tirage_au_sort;

    if (tirage_au_sort == 1)
    {
        cout << "On tire au sort celui qui commence ...\n";
        int debutant = tirage_alea_entier(1, 2);
        if (debutant == 1)
        {
            cout << "FAIT, le joueur 1 commence ! Il joue donc blanc.\n";
            is_tour_joueur1 = true;
            is_white_1 = is_tour_joueur1;
        }
        else
        {
            cout << "FAIT, le joueur 2 commence ! Il joue donc blanc.\n";
            is_tour_joueur1 = false;
            is_white_1 = is_tour_joueur1;
        }
    }
    else
    {
        cout << "Très bien, le joueur 1 commence ! Il joue donc blanc.\n";
        is_tour_joueur1 = true;
        is_white_1 = is_tour_joueur1;
    }

    while (num_tour < boucle_max && !is_fini)
    {

        // a qui est-ce de jouer ?
        if (is_tour_joueur1)
        {
            joueur_courant = joueur1;
            is_white_courant = is_white_1;
        }
        else
        {
            joueur_courant = joueur2;
            is_white_courant = (!is_white_1);
        }

        // num_tour
        if (is_white_courant)
        {
            num_tour += 1;
        }

        // c'est à l'humain de jouer, choix du coup !
        if (joueur_courant == 1)
        {
            cout << "C'est au tour des ";
            if (is_white_courant)
            {
                cout << "Blancs.";
            }
            else
            {
                cout << "Noirs.";
            }
            cout << " Voici le plateau : \n";
            EchiTTT->affiche();

            is_coups_correct = false;
            cout << "où jouer ? \n";
            while (!is_coups_correct)
            {
                cout << "Entrez la ligne :";
                cin >> ligne;
                cout << "Entrez la colonne :";
                cin >> colonne_char; // conversion
                colonne = colonne_char - 96;
                // verifiez conformité
                if (ligne > taillep || ligne <= 0)
                {
                    cout << "la ligne ne conviennt pas, recommencez \n";
                }
                else if (colonne > taillep || colonne <= 0)
                {
                    cout << "la colonne ne convient pas, recommencez \n";
                }
                else
                {
                    p = pair<int, int>(ligne, colonne);
                    if (EchiTTT->plateau[coor_to_pos(p, taillep)] != NULL)
                    {
                        cout << "la case est déjà occupée, recommencez\n";
                    }
                    else
                    {
                        is_coups_correct = true;
                    }
                }
            }

            piece_jouee = new Piece(is_white_courant);
            coupjoue = new Coup(is_white_courant, *piece_jouee, p, piece_jouee->position_coor, num_tour);
            cout << "Le coup est : " << *coupjoue << "\n";
        }

        // C'est à l'ordi aléatoire de jouer, , choix du coup !
        else if (joueur_courant == 2)
        {
            coupjoue = coup_aleatoire_TTT(*EchiTTT, is_white_courant, num_tour);
            cout << "Au tour " << num_tour << ", le coup du joueur " << (is_white_courant ? "blanc" : "noir") << " est : " << *coupjoue << endl;
        }

        // C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
        else if (joueur_courant == 3)
        {
        }

        else
        {
            cout << "le joueur choisi n'existe pas, recommencez \n";
            return 0;
        }

        // on joue le coup

        actualisePlateau(*EchiTTT, *coupjoue);
        cout << "Voici le déplacement effectué : \n";
        EchiTTT->affiche();
        addCoup(historique_coups, coupjoue);
        is_fini = is_coup_gagnant_TTT(*EchiTTT, *coupjoue);
        if (is_fini)
        {
            cout << "Victoire";
        }
        else
        {
            if ((num_tour < 5))
            {
                cout << "Pas de Victoire, on continue ! \n";
            }
            else
            {
                cout << "Egalité !\n";
                is_fini = true;
            }
        }
        is_tour_joueur1 = (!(is_tour_joueur1));
    }
    return 0;
}