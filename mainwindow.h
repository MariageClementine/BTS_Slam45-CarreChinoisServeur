#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCursor>
#include <QMainWindow>
#include "qemplacement.h"
#include "qjoueur.h"
#include "qemplacement.h"
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}
class QEmplacement;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJoueur * joueurHumain;
    QJoueur * joueurOrdi;
    QJoueur * joueurActif;
    QPixmap pixmapVide;
    QEmplacement * emplacementDeplace;

    bool partieFinie;

    int compteurOrdi;
    int compteurHumain;

    void setEmplacementDeplace(QEmplacement *e) {emplacementDeplace=e;}
    void changeJoueurActif();
    void resetCurseur();
    void majCompteur();
    void initJeu();

    void traiterDonnees(QString donnees);
    void envoyerAuClient(int posVieuxX,int posVieuxY, int posNouvX, int posNouvY);
    void envoyerAuClient(int pionX, int pionY);

    //les fonctions qui vont determiner une partie gagnée
    bool ligne(int noL);
    bool colonne(int noC);
    bool diagonale(int noD);
    bool gagne(QJoueur * joueur);

public slots:
    void setCurseur(QCursor & curseur);

private slots:

    void on_pushButtonNouvellePartie_clicked();
    void debutPartie();
    void recupDonnees();

private:
    Ui::MainWindow *ui;
    QCursor normal;
    QEmplacement * tab[3][3];

    //connexion au client
    QTcpServer * socketServeur;
    QTcpSocket * laSocketDuClient;
};

#endif // MAINWINDOW_H


