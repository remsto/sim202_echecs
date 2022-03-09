#include "echeccase.h"
#include "echecgrille.h"
#include "mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <string>

Piece *EchecCase::getPiece() const { return piece; }

void EchecCase::setPiece(Piece *newPiece) { piece = newPiece; }

const pair<int, int> &EchecCase::getCoor() const { return coor; }

void EchecCase::setCoor(const pair<int, int> &newCoor) { coor = newCoor; }

bool EchecCase::getCoup_possible() const { return coup_possible; }

void EchecCase::setCoup_possible(bool newCoup_possible) {
  coup_possible = newCoup_possible;
}

EchecCase::EchecCase() {
  selected = false;
  piece = nullptr;
}
void EchecCase::mousePressEvent(QMouseEvent *) {
  EchecGrille *grille = qobject_cast<EchecGrille *>(parent());
  if (coup_possible)
    emit sendArrCoor(coor);
  else if (piece == nullptr)
    emit grille->changeMessage("La case doit contenir une pièce !");
  else if (piece->isWhite != grille->getIs_white_courant())
    emit grille->changeMessage(
        "Cette pièce n'appartient pas au joueur courant");
  else {
    EchecCase *old_case = ((EchecGrille *)parentWidget())->getCase_selected();
    old_case->setSelected(false);
    old_case->update();
    ((EchecGrille *)parentWidget())->setCase_selected(this);
    setSelected(true);
    emit grille->changeMessage("La pièce est valable");
    emit sendDepCoor(coor);
    update();
  }
}

void EchecCase::paintEvent(QPaintEvent *) {
  QPixmap wood = this->pixmap(Qt::ReturnByValue);
  QPainter painter(this);
  painter.drawPixmap(rect(), wood);
  if (piece != nullptr) {
    QPixmap *echec_piece = new QPixmap(
        QString(":/ressources/") + QString(piece->isWhite ? "white" : "black") +
        QString("_") +
        QString::fromUtf8(piece->type.data(), int(piece->type.size())) +
        QString(".png"));
    // QPixmap *echec_piece = new QPixmap(":/ressources/black_Roi.png");
    QRect piece_rect(rect());
    piece_rect.setSize(rect().size() * (6.0 / 7.0));
    piece_rect.moveCenter(rect().center());
    painter.drawPixmap(piece_rect, *echec_piece);
    delete echec_piece;
  }
  if (coup_possible)
    painter.fillRect(rect(), QColor(0, 255, 0, 100));
  else if (selected)
    painter.fillRect(rect(), QColor(0, 0, 255, 100));
}
void EchecCase::setSelected(bool selected) { this->selected = selected; }
