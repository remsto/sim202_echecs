#include <iostream>
using namespace std;
#include "ordi_min_max.hpp"

////
// POSITION
////

Position::Position(Echiquier &plateau, ListeCoups &coups, Position *positionSoeur, Position *positionFille, bool joueurCoup, int num_tour)
{
    plateauRef = plateau;
    joueur = joueurCoup;
    soeur = positionSoeur;
    fille = positionFille;
    coupsPrecedents = coups;
    num_tour_de_jeu = num_tour;
}

Position::~Position() // a faire
{

    coupsPrecedents.~ListeCoups();
    if (soeur != NULL)
    {
        soeur->~Position();
    }
    if (fille != NULL)
    {
        fille->~Position();
    }
} 

// pour TTT a cause de coups possibles
void Position::generateur(int profondeur)
{

    if (profondeur != 0)
    {
        actualisePlateau(plateauRef, coupsPrecedents);
        //actualise valeur de 1ere soeur
        set_valeur(self); // à coder pour les échecs
        ListeCoups *coupsPossibles = coupsPossiblesTTT(plateauRef, joueur, num_tour_de_jeu + 1); // regrouper avec valeur dans une méthode?
        resetPlateau(plateauRef, coupsPrecedents);

        // CREATION 1ere FILLE
        // copie coupsPrecedents
        ListeCoups coupsPrecedentsCurrent(coupsPrecedents);
        // Le 1er coupPossible devient le dernier coupPrecedent
        (coupsPrecedentsCurrent.last)->Next = coupsPossibles->first;
        coupsPrecedentsCurrent.last = coupsPossibles->first;
        coupsPrecedentsCurrent.nbCoups++;

        this->fille = new Position(plateauRef, coupsPrecedentsCurrent, NULL, NULL, !joueur, num_tour_de_jeu + 1);
        Position *current = this->fille;

        for (int i = 0; i < coupsPossibles->nbCoups; i++)
        { // maj coupsPossibles
            coupsPossibles->first = (coupsPossibles->first)->Next;
            coupsPossibles->nbCoups = coupsPossibles->nbCoups - 1;

            // cps = this.cp
            ListeCoups coupsPrecedentsSoeur(coupsPrecedents);

            // cps.last.next = dernier coup = b
            (coupsPrecedentsSoeur.last)->Next = coupsPossibles->first;
            // cps.last = b
            coupsPrecedentsSoeur.last = (coupsPrecedentsSoeur.last)->Next;
            coupsPrecedentsSoeur.nbCoups++;

            // CREATION SOEUR
            current->soeur = new Position(plateauRef, coupsPrecedentsSoeur, NULL, NULL, !joueur, num_tour_de_jeu + 1);

            // Passer à la suivante

            current = current->soeur;

            //set la valeur soeur
            set_valeur(current);

            // Appeler récursion sur current
            current->generateur(profondeur - 1);
        }
    }
}

void annexe(int profondeur, ListeCoups coupsPossibles) //+ Position pos)
{
    if (coupsPossibles.first != coupsPossibles.last)
    {
    }
    if ((profondeur != 0))
    {
        // créer fille, appeler annexe dessus (profondeur -1)
    }
}

int Position::set_valeur()
{
    if ((*this).estGagnante())
    {
        return inf;
    }
    else
    {
        return 0;
    }
}

bool Position::estGagnante()
{
    actualisePlateau(plateauRef, coupsPrecedents);

    // vérifier comme des bourrins TicTacToe (le dernier coup est decisif)
    Coup *dernierCoup = coupsPrecedents.last;
    bool is_coup_gagne = is_coup_gagnant_TTT(plateauRef, *dernierCoup);

    // On réinitialise le plateau
    resetPlateau(plateauRef, coupsPrecedents);
    return is_coup_gagne;
}


Coup coup_min_max(Position position){
    // ARRANGER LES "." ET "->", COMPLETEMENT HASARDEUX
    position.generateur(k); //je ne sais pas appeler cette méthode
    MinMax(position); // à coder
    Position *current = position->fille;
    Coup coup = (current->coupsPrecedents).last;
    while(current->soeur != NULL){ // Parcours de la génération fille
        if(position.joueur){
            if(current.valeurMinMax > (current->soeur).valeurMinMax){
                coup = ((current->soeur)->coupsPrecedents).last;
            }
        }
        else{
            if(current.valeurMinMax < (current->soeur).valeurMinMax){
                coup = ((current->soeur)->coupsPrecedents).last;
            }
        }
        current = current.soeur;
    }
    return coup

}

void MinMax(Position position){
    // Si position terminale
    if(position.fille == NULL){
        position.valeurMinMax = position.valeurPosition;
    }
    else{
        // Si le joueur est le joueur en train de jouer
        
        Position current = position->fille; 
        MinMax(current);
        int temp = current.valeurMinMax;
        while(current->soeur != NULL){
            current = current->soeur;
            MinMax(current);
            
            if(position.joueur){
                // Si joueur 1, on cherche le max  
                // VERIFIER false OU true
                if(current.valeurMinMax > temp){
                    temp = current.valeurMinMax;
                }
            }
            else{
                // Si joueur 2, on cherche le min
                if(current.valeurMinMax < temp){
                    temp = current.valeurMinMax;
                }
            }
        }
        position.valeurMinMax = MinMax
    }
}