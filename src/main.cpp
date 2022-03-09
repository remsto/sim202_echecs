#include <iostream>
using namespace std;
#include "include/ordi_aleatoire.hpp"
//#define cout std::cout
#define taillepp 8

int main() {
  bool is_fini = false;
  Echiquier *Echi = new Echiquier(taillepp);
  int taillep = Echi->taille;
  int num_tour = 0;
  int boucle_max = 1000; // a enlever à terme

  bool is_coups_correct;
  int joueur_courant;
  bool is_tour_joueur1;
  bool is_white_1;
  bool is_white_courant;

  Coup *coupjoue;
  Piece *piece_jouee;
  Deplac_rel *dep;

  ListeCoups *historique_coups = new ListeCoups();

  // mise en place des pièces
  mise_en_place_echec_piece(*Echi);

  // mise en place des joueurs
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

  if (tirage_au_sort == 1) {
    cout << "On tire au sort celui qui commence ...\n";
    int debutant = tirage_alea_entier(1, 2);
    if (debutant == 1) {
      cout << "FAIT, le joueur 1 commence ! Il joue donc blanc.\n";
      is_tour_joueur1 = true;
      is_white_1 = is_tour_joueur1;
    } else {
      cout << "FAIT, le joueur 2 commence ! Il joue donc blanc.\n";
      is_tour_joueur1 = false;
      is_white_1 = is_tour_joueur1;
    }
  } else {
    cout << "Très bien, le joueur 1 commence ! Il joue donc blanc.\n";
    is_tour_joueur1 = true;
    is_white_1 = is_tour_joueur1;
  }

  while (num_tour < boucle_max && !is_fini) {
    // a qui est-ce de jouer ?
    if (is_tour_joueur1) {
      joueur_courant = joueur1;
      is_white_courant = is_white_1;
    } else {
      joueur_courant = joueur2;
      is_white_courant = (!is_white_1);
    }

    // num_tour
    if (is_white_courant) {
      num_tour += 1;
    }

    // c'est à l'humain de jouer, choix du coup !
    if (joueur_courant == 1) {
      cout << "C'est au tour des ";
      if (is_white_courant) {
        cout << "Blancs.";
      } else {
        cout << "Noirs.";
      }
      cout << " Voici le plateau : \n";
      Echi->affiche();

      is_coups_correct = false;
      cout << "où jouer ? \n";

      string case_depart;
      string case_arrive;
      pair<int, int> case_dep;
      pair<int, int> case_arr;

      while (!is_coups_correct) {
        cout << "Entrez la case de départ (ex : 'b2') :";
        cin >> case_depart;
        cout << "Entrez la case d'arrivée :";
        cin >> case_arrive;

        if ((case_depart.length() != 2) || (case_arrive.length() != 2))
          cout << "Les formats de cases ne correspondent pas à la longueur "
                  "souhaitée. \n";
        else {
          int ligne_depart = case_depart[1] - 48;
          int ligne_arrivee = case_arrive[1] - 48;
          int colonne_depart = case_depart[0] - 96;
          int colonne_arrivee = case_arrive[0] - 96;

          if ((ligne_depart < 1) || (ligne_depart > taillep) ||
              (ligne_arrivee < 1) || (ligne_arrivee > taillep) ||
              (colonne_depart < 1) || (colonne_depart > taillep) ||
              (colonne_arrivee < 1) || (colonne_arrivee > taillep))
            cout << "l'une des cases entrées n'existe pas. \n";
          else {
            case_dep = pair<int, int>(ligne_depart, colonne_depart);
            case_arr = pair<int, int>(ligne_arrivee, colonne_arrivee);
            dep = new Deplac_rel(case_arr - case_dep);
            piece_jouee = Echi->plateau[coor_to_pos(case_dep, taillep)];
            if ((piece_jouee == NULL) ||
                (piece_jouee->isWhite !=
                 is_white_courant)) // traiter cas 2 dans is_legal
              cout << "La case de départ ne correspond pas à l'une de vos "
                      "pièces. \n";
            else if (!is_legal(*Echi, piece_jouee, dep, num_tour))
              cout << "Ce coup n'est pas légal.\n";
            else {
              cout << "Le coup est correct.\n";
              is_coups_correct = true;
            }
          }
        }
      }

      Piece *piece_prise = taken_coup(*Echi, piece_jouee, dep, num_tour);
      // cout << "piece prise ok\n";
      bool is_spe = is_Special(*Echi, piece_jouee, dep);
      // cout << is_spe << endl;
      bool is_ech =
          is_Echec(*Echi, piece_jouee, dep, num_tour, !is_white_courant);
      // cout << is_ech << endl;
      bool is_ma = is_Mat(*Echi, piece_jouee, dep, num_tour);
      // cout << is_ma << endl;
      coupjoue =
          new Coup(is_white_courant, piece_jouee, case_arr, case_dep, num_tour,
                   piece_prise, is_spe, NULL, NULL, is_ech, is_ma);
      cout << *piece_jouee << endl;
      cout << "Le coup est : " << *coupjoue << "\n";
    }

    //  C'est à l'ordi aléatoire de jouer, , choix du coup !
    else if (joueur_courant == 2) {
      coupjoue = coup_aleatoire_echecs(*Echi, is_white_courant, num_tour);
      cout << "Le coup est : " << *coupjoue << "\n";
    }

    // C'est à l'ordi min_max de profondeur ?? de jouer,, choix du coup !
    else if (joueur_courant == 3) {
    }

    else {
      cout << "le joueur choisi n'existe pas, recommencez \n";
      return 0;
    }

    // on joue le coup

    actualisePlateau(*Echi, *coupjoue);
    cout << "Voici le déplacement effectué : \n";
    Echi->affiche();
    addCoup(historique_coups, coupjoue);

    is_fini = coupjoue->is_mat;

    if (is_fini) {
      cout << "BRAVO ! Victoire du joueur ";
      cout << (is_white_courant ? "Blanc." : "Noir.");
      cout << endl << "Voici un récapitulatif de la partie : \n";
      cout << *historique_coups;
    } else {
      if (num_tour != boucle_max) {
        cout << "On continue ! \n";
      } else {
        cout << "nombre de boucle max atteint !\n";
      }
    }
    is_tour_joueur1 = (!(is_tour_joueur1));
  }
  return 0;
}
