#include "echeccase.h"
#include "echecgrille.h"
#include "mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

EchecCase::EchecCase() { selected = false; }
void EchecCase::mousePressEvent(QMouseEvent *) {
  EchecCase *old_case = ((EchecGrille *)parentWidget())->getCase_selected();
  old_case->setSelected(false);
  old_case->update();
  ((EchecGrille *)parentWidget())->setCase_selected(this);
  setSelected(true);
  update();
}

void EchecCase::paintEvent(QPaintEvent *) {
  QPixmap wood = this->pixmap(Qt::ReturnByValue);
  QPainter painter(this);
  painter.drawPixmap(rect(), wood);
  if (selected) {
    QPixmap *echec_piece = new QPixmap(":/ressources/white_king.png");
    //*echec_piece = echec_piece->scaled(10, 10);
    QRect piece_rect(rect());
    piece_rect.setSize(rect().size() * (6.0 / 7.0));
    piece_rect.moveCenter(rect().center());
    painter.drawPixmap(piece_rect, *echec_piece);
    painter.fillRect(rect(), QColor(0, 0, 255, 100));
  }
}
void EchecCase::setSelected(bool selected) { this->selected = selected; }
