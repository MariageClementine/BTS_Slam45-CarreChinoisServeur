#include "qjoueur.h"
#include <QDebug>

QJoueur::QJoueur(QString couleur, QWidget *parent) :
    QLabel(parent)
{
    setNbJetons(3);
    coul=couleur;

    QPixmap image(":/images/"+coul);
    setPixmap(image);
    curseurNormal=new QCursor(image);

    QPixmap imageOk(":/images/ok"+coul);
    curseurOk = new QCursor(imageOk);
    QPixmap imagePOk(":/images/pok"+coul);
    curseurPOk = new QCursor(imagePOk);

}

void QJoueur::setNbJetons(int nb)
{
    nbJetons=nb;
}

int QJoueur::getNbJetons()
{
    return nbJetons;
}

void QJoueur::enleveJetons()
{
    nbJetons--;
}

QString QJoueur::getCoul()
{
    return coul;
}

QCursor* QJoueur::getSonCurseur(QString quelCurseur)
{
    if(quelCurseur=="normal")
    {
        return curseurNormal;
    }
    else
    {
        if(quelCurseur=="pok")
        {
            return curseurPOk;
        }
        else
        {
            if(quelCurseur=="ok")
            {
                return curseurOk;
            }
        }
    }
}
