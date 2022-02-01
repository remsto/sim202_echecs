using namespace std;
#include <vector>
#include <iostream>
#include "environnement.hpp"


/* 
CLASSE ET FONCTIONS GENERIQUES AU TTT et ECHECS
*/

//class TypePiece 

TypePiece::TypePiece(string type)
{
    this->type=type;
    this->deplac_relatif=vector<pair<int,int>>();
    this->valeur=1;
}

//class Piece




//class Echiquier 

void Echiquier::affiche () const 
{
    cout << "  A  B  C\n"
    for (int i=1; i<=taille*taille; i++) {
        Piece* piece=plateau[i];
        if (i%taille==0) {
            cout <<i/taille << " "; 
        }
            cout<<"\n";
        if (piece==0) { 
            cout<<"  ";
        } else {
            cout << piece->type[0] ; // P ou D ou R ou ...
            if (piece->isWhite) {
                cout << "b";
            } else {
                cout <<"n";
            }
        cout <<" ";
        //ajout des retours à la ligne
        if (i%taille==taille-1)
            cout<<"\n";
        }
    }
}

