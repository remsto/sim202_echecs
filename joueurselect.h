#ifndef JOUEURSELECT_H
#define JOUEURSELECT_H

#include <QDialog>

namespace Ui {
class JoueurSelect;
}

class JoueurSelect : public QDialog {
  Q_OBJECT

public:
  explicit JoueurSelect(QWidget *parent = nullptr);
  ~JoueurSelect();

public slots:
  void setJoueurs();

signals:
  void sendJoueurs(int joueur1, int joueur2);

private:
  Ui::JoueurSelect *ui;
};

#endif // JOUEURSELECT_H
