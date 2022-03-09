#include "echecgrille.h"
#include "include/environnement.hpp"
#include "include/ordi_aleatoire.hpp"
#include "include/pour_jouer.hpp"
#include "joueurselect.h"

#include <QDebug>

EchecCase *EchecGrille::getCase_selected() const { return case_selected; }

void EchecGrille::setCase_selected(EchecCase *newCase_selected) {
  case_selected = newCase_selected;
}

void EchecGrille::majEchecGraph(Echiquier *echi) {
  for (int i = 0; i < 64; i++) {
    list_case[i]->setPiece(echi->plateau[i]);
  }
  update();
}

EchecGrille::EchecGrille() {}

bool cmpObject(QObject *o1, QObject *o2) {
  return (o1->objectName() < o2->objectName());
}

void EchecGrille::fillList_case() {
  QPixmap *light_wood = new QPixmap(":/ressources/light_wood.jpg");
  *light_wood = light_wood->scaled(100, 100);
  QPixmap *dark_wood = new QPixmap(":/ressources/dark_wood.jpg");
  *dark_wood = dark_wood->scaled(100, 100);
  for (QObject *sah : children()) {
    list_case.append(qobject_cast<EchecCase *>(sah));
  }
  list_case.removeFirst();
  std::sort(list_case.begin(), list_case.end(), cmpObject);
  int i = 0;
  for (EchecCase *echecCase : list_case) {
    echecCase->setSelected(false);
    echecCase->setPixmap((i % 2 == 0 && (i / 8) % 2 == 0) ||
                                 (i % 2 == 1 && (i / 8) % 2 == 1)
                             ? *light_wood
                             : *dark_wood);
    echecCase->setCoor(pos_to_coor(i, 8));
    QObject::connect(echecCase, SIGNAL(sendDepCoor(pair<int, int>)), this,
                     SLOT(rcvDepCoor(pair<int, int>)));
    QObject::connect(echecCase, SIGNAL(sendArrCoor(pair<int, int>)), this,
                     SLOT(rcvArrCoor(pair<int, int>)));
    i++;
  }
  setCase_selected(list_case[0]);
  delete light_wood;
  delete dark_wood;
}

void EchecGrille::setJoueurs(int joueur1, int joueur2) {
  this->joueur1 = joueur1;
  this->joueur2 = joueur2;
}

void EchecGrille::rcvDepCoor(pair<int, int> coor) {
  for (int i = 0; i < 64; i++) {
    Deplac_rel *dep = new Deplac_rel(list_case[i]->getCoor() - coor);
    if (is_legal(*echi,
                 qobject_cast<EchecCase *>(QObject::sender())->getPiece(), dep,
                 num_tour))
      list_case[i]->setCoup_possible(true);
    else
      list_case[i]->setCoup_possible(false);
  }
  update();
}

void EchecGrille::rcvArrCoor(pair<int, int>) {
  qDebug() << "Ce coup est jouable !";
}

bool EchecGrille::getIs_white_courant() const { return is_white_courant; }

void EchecGrille::setIs_white_courant(bool newIs_white_courant) {
  is_white_courant = newIs_white_courant;
}

void EchecGrille::nouvellePartie() {
  is_fini = false;
  echi = new Echiquier(8);
  taillep = echi->taille;
  num_tour = 0;
  boucle_max = 1000;
  historique_coups = new ListeCoups();
  // mise en place des pièces
  mise_en_place_echec_piece(*echi);

  joueur1 = -1;
  joueur2 = -1;
  // Dialogue de selection des joueurs
  JoueurSelect *joueurselect = new JoueurSelect(this);
  QObject::connect(joueurselect, SIGNAL(sendJoueurs(int, int)), this,
                   SLOT(setJoueurs(int, int)));
  joueurselect->exec();
  qDebug() << joueur1 << joueur2;
  while (joueur1 == -1 || joueur2 == -1) {
    JoueurSelect *joueurselect = new JoueurSelect(this);
    QObject::connect(joueurselect, SIGNAL(sendJoueurs(int, int)), this,
                     SLOT(setJoueurs(int, int)));
    joueurselect->exec();
    qDebug() << joueur1 << joueur2;
  }
  majEchecGraph(echi);
  // A rajouter : tirage au sort
  is_tour_joueur1 = true;
  is_white_1 = is_tour_joueur1;
  setIs_white_courant(true);
}
