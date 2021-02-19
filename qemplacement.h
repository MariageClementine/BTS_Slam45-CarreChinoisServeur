#ifndef QEMPLACEMENT_H
#define QEMPLACEMENT_H

#include "mainwindow.h"
#include <QLabel>
#include "qjoueur.h"
#include <QMouseEvent>

class MainWindow;

class QEmplacement : public QLabel
{
    Q_OBJECT
private:
    MainWindow * mum;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

public:
    explicit QEmplacement(MainWindow * maman,QWidget *parent = 0);
    void posePion();
    int ligne;
    int col;
    QJoueur* leJoueur;

signals:

public slots:
    bool estVide();
    bool jouxte(QEmplacement * e);
    void setJoueur(QJoueur*);
    void vider();


};

#endif // QEMPLACEMENT_H
