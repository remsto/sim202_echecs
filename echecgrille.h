#ifndef ECHECGRILLE_H
#define ECHECGRILLE_H

#include "echeccase.h"
#include "include/environnement.hpp"
#include "include/pour_jouer.hpp"

#include <QWidget>

class EchecGrille : public QWidget {
  Q_OBJECT
private:
  QList<EchecCase *> list_case;
  EchecCase *case_selected;
  bool is_fini;
  Echiquier *echi;
  int taillep;
  int num_tour;
  int boucle_max;
  bool is_coups_correct;
  int joueur_courant;
  bool is_tour_joueur1;
  bool is_white_1;
  bool is_white_courant;
  Coup *coupjoue;
  Piece *piece_jouee;
  Deplac_rel *dep;
  ListeCoups *historique_coups;
  int joueur1;
  int joueur2;

public slots:
  void nouvellePartie();
  void setJoueurs(int joueur1, int joueur2);
  void rcvDepCoor(pair<int, int>);
  void rcvArrCoor(pair<int, int>);

signals:
  void changeMessage(QString message);

public:
  using QWidget::QWidget;
  EchecGrille();
  void fillList_case();
  EchecCase *getCase_selected() const;
  void setCase_selected(EchecCase *newCase_selected);
  void majEchecGraph(Echiquier *echi);
  bool getIs_white_courant() const;
  void setIs_white_courant(bool newIs_white_courant);
};

#endif // ECHECGRILLE_H
