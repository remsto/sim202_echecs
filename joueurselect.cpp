#include "joueurselect.h"
#include "ui_joueurselect.h"
#include <QDebug>

JoueurSelect::JoueurSelect(QWidget *parent)
    : QDialog(parent), ui(new Ui::JoueurSelect) {
  ui->setupUi(this);
  ui->joueurhumain_1->toggle();
  ui->joueurhumain_2->toggle();
  QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setJoueurs()));
}

void JoueurSelect::setJoueurs() {
  int joueur1, joueur2;
  if (ui->joueurhumain_1->isChecked())
    joueur1 = 1;
  else if (ui->ordialeatoire_1->isChecked())
    joueur1 = 2;
  else if (ui->ordiintelligent_1->isChecked())
    joueur1 = 3;
  else
    joueur1 = -1;
  if (ui->joueurhumain_2->isChecked())
    joueur2 = 1;
  else if (ui->ordialeatoire_2->isChecked())
    joueur2 = 2;
  else if (ui->ordiintelligent_2->isChecked())
    joueur2 = 3;
  else
    joueur2 = -1;
  emit sendJoueurs(joueur1, joueur2);
}

JoueurSelect::~JoueurSelect() { delete ui; }
