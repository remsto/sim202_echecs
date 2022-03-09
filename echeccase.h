#ifndef ECHECCASE_H
#define ECHECCASE_H
#include "include/environnement.hpp"
#include <QLabel>
#include <utility>

class EchecCase : public QLabel {
  Q_OBJECT
private:
  int lettre;
  int chiffre;
  bool selected;
  bool coup_possible = false;
  Piece *piece = nullptr;
  pair<int, int> coor;

signals:
  void sendDepCoor(pair<int, int>);
  void sendArrCoor(pair<int, int>);

public:
  using QLabel::QLabel;
  EchecCase();
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void setSelected(bool selected);
  Piece *getPiece() const;
  void setPiece(Piece *newPiece);
  const pair<int, int> &getCoor() const;
  void setCoor(const pair<int, int> &newCoor);
  bool getCoup_possible() const;
  void setCoup_possible(bool newCoup_possible);
};

#endif // ECHECCASE_H
