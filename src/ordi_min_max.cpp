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
        this->set_valeur(); // à coder pour les échecs
        ListeCoups *coupsPossibles = coupsPossiblesTTT(plateauRef, joueur, num_tour_de_jeu + 1); 
    
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
            (*current).set_valeur();

            // Appeler récursion sur current
            current->generateur(profondeur - 1);
        }
    }
}

int Position::set_valeur()
{
    if (this->estGagnante())
    {
        return inf;
    }
    else
    {
        return 0;
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


Coup coup_min_max(Position position, int profondeur){
    // ARRANGER LES "." ET "->", COMPLETEMENT HASARDEUX
    position.generateur(profondeur); //je ne sais pas appeler cette méthode
    position.MinMax(); // à coder
    Position *current = position.fille;
    Coup coup = *(current->coupsPrecedents).last;
    while(current->soeur != NULL){ // Parcours de la génération fille
        if(position.joueur){
            if(current->valeurMinMax > (current->soeur)->valeurMinMax){
                coup = *((current->soeur)->coupsPrecedents).last;
            }
        }
        else{
            if(current->valeurMinMax < (current->soeur)->valeurMinMax){
                coup = *((current->soeur)->coupsPrecedents).last;
            }
        }
        current = current->soeur;
    }
    return coup;
}

void Position::MinMax(){
    // Si position terminale
    if(this->fille == NULL){
        this->valeurMinMax = this->valeurPosition;
    }
    else{
        // Si le joueur est le joueur en train de jouer
        
        Position *current = this->fille; 
        current->MinMax();
        int temp = current->valeurMinMax;
        while(current->soeur != NULL){
            current = current->soeur;
            current->MinMax();
            
            if(this->joueur){
                // Si joueur 1, on cherche le max  
                // VERIFIER false OU true
                if(current->valeurMinMax > temp){
                    temp = current->valeurMinMax;
                }
            }
            else{
                // Si joueur 2, on cherche le min
                if(current->valeurMinMax < temp){
                    temp = current->valeurMinMax;
                }
            }
        }
        this->valeurMinMax = temp;
    }
}