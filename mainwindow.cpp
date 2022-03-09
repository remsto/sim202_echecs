#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->echecGrille->fillList_case();
  QObject::connect(ui->actionNouvelle_partie, SIGNAL(triggered(bool)),
                   ui->echecGrille, SLOT(nouvellePartie()));
  QObject::connect(ui->echecGrille, SIGNAL(changeMessage(QString)),
                   ui->messageDisplayer, SLOT(setText(QString)));
}

void MainWindow::nouvellePartie() {
  // TODO doit lancer une nouvelle partie
  qDebug() << "Pas encore implémenté !!";
}

MainWindow::~MainWindow() { delete ui; }
