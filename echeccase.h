#ifndef ECHECCASE_H
#define ECHECCASE_H
#include <QLabel>

class EchecCase : public QLabel {
  Q_OBJECT
private:
  int lettre;
  int chiffre;
  bool selected;

public:
  using QLabel::QLabel;
  EchecCase();
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void setSelected(bool selected);
};

#endif // ECHECCASE_H
