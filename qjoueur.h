#ifndef QJOUEUR_H
#define QJOUEUR_H

#include <QLabel>

class QJoueur : public QLabel
{
    Q_OBJECT
public:
    explicit QJoueur(QString couleur, QWidget *parent = 0);
    void setNbJetons(int nb);
    int getNbJetons();
    void enleveJetons();    

    QString getCoul();
    QCursor* getSonCurseur(QString quelCurseur);

signals:

public slots:

private:
    QString coul;
    int nbJetons;
    QCursor * curseurNormal;
    QCursor * curseurOk;
    QCursor * curseurPOk;


};

#endif // QJOUEUR_H
