#include "echecgrille.h"

EchecCase *EchecGrille::getCase_selected() const { return case_selected; }

void EchecGrille::setCase_selected(EchecCase *newCase_selected) {
  case_selected = newCase_selected;
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
    i++;
  }
  setCase_selected(list_case[0]);
  delete light_wood;
  delete dark_wood;
}
