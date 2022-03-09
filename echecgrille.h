#ifndef ECHECGRILLE_H
#define ECHECGRILLE_H

#include "echeccase.h"

#include <QWidget>

class EchecGrille : public QWidget {
  Q_OBJECT
private:
  QList<EchecCase *> list_case;
  EchecCase *case_selected;

public:
  using QWidget::QWidget;
  EchecGrille();
  void fillList_case();
  EchecCase *getCase_selected() const;
  void setCase_selected(EchecCase *newCase_selected);
};

#endif // ECHECGRILLE_H
