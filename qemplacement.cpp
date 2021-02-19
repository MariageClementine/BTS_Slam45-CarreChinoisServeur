#include "qemplacement.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPoint>

QEmplacement::QEmplacement(MainWindow * maman, QWidget *parent) :
    QLabel(parent)
{
    mum=maman;
    leJoueur=NULL;
    setPixmap(mum->pixmapVide); //debug
}

bool QEmplacement::estVide()
{
    if(leJoueur ==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void QEmplacement::mousePressEvent(QMouseEvent *ev)
{
    if(mum->joueurActif==mum->joueurOrdi)
    {
        if(!mum->partieFinie)
        {
            //si l'emplacement est libre
            if(this->estVide())
            {
                //si il a encore des pions a poser
                if(mum->joueurActif->getNbJetons()>0)
                {
                    //on met le pion du joueur
                    this->setJoueur(mum->joueurActif);

                    //on diminue le stock de jetons
                    mum->joueurActif->enleveJetons();

                    //on envoie au serveur
                    mum->envoyerAuClient(this->ligne,this->col);

                    if(!mum->gagne(mum->joueurActif))
                    {
                        //on switch de joueur actif
                        mum->changeJoueurActif();
                    }
                }
            }
            else//si l'emplacement est déjà occupé par un pion
            {
                //si c'est le bon joueur
                if(leJoueur==mum->joueurActif)
                {
                    //si le stock est bien vide
                    if(mum->joueurActif->getNbJetons()==0)
                    {
                        //on part sur un deplacement
                        mum->setCurseur(*mum->joueurActif->getSonCurseur("normal"));
                        //on mémorise le futur ancien emplacement du pion
                        mum->setEmplacementDeplace(this);
                    }

                }
            }
        }
    }
}

void QEmplacement::setJoueur(QJoueur * j)
{
    leJoueur=j;
    if(leJoueur!=NULL)
    {
        setPixmap(":/images/"+mum->joueurActif->getCoul());
    }
}

void QEmplacement::mouseMoveEvent(QMouseEvent *ev)
{
    if(mum->joueurActif==mum->joueurOrdi)
    {
        //si on a bien déplacé tel pion
        if(mum->emplacementDeplace!=NULL)
        {
            //en focntion de l'élément survolé on signale si on peut ou non relacher
            QPoint lePointSurvole = mapToParent(ev->pos());
            QEmplacement * emplacementSurvole=(QEmplacement*)mum->childAt(lePointSurvole);

            //si on survole
            //ET si ce qu'on survole est bien un emplacement
            //ET que le futur nouvel emplacement est vide
            if(emplacementSurvole!=NULL && emplacementSurvole->inherits("QEmplacement") && emplacementSurvole->estVide() && jouxte(emplacementSurvole))
            {
                mum->setCurseur(*mum->joueurActif->getSonCurseur("ok"));
            }
            else
            {
                if(emplacementSurvole!=NULL && emplacementSurvole->inherits("QEmplacement") && !emplacementSurvole->estVide())
                {
                    mum->setCurseur(*mum->joueurActif->getSonCurseur("pok"));
                }
                else
                {
                    mum->setCurseur(*mum->joueurActif->getSonCurseur("normal"));
                }
            }
        }
    }
}

void QEmplacement::mouseReleaseEvent(QMouseEvent *ev)
{
    if(mum->joueurActif==mum->joueurOrdi)
    {
        QPoint lePointSurvole= mapToParent(ev->pos());
        QEmplacement * emplacementRelache=(QEmplacement *)mum->childAt(lePointSurvole);

        if(emplacementRelache!=NULL && emplacementRelache->inherits("QEmplacement") && emplacementRelache->estVide() && jouxte(emplacementRelache))
        {
            if(mum->emplacementDeplace!=NULL)
            {
                //envoi au serveur
                int posDeplX = mum->emplacementDeplace->ligne;
                int posDeplY = mum->emplacementDeplace->col;
                int posRelX = emplacementRelache->ligne;
                int posRelY = emplacementRelache->col;
                mum->envoyerAuClient(posDeplX,posDeplY,posRelX,posRelY);

                emplacementRelache->setJoueur(mum->emplacementDeplace->leJoueur);
                mum->emplacementDeplace->vider();
                mum->emplacementDeplace=NULL;
                if(! mum->gagne(mum->joueurActif)) mum->changeJoueurActif();
            }
        }
        mum->resetCurseur();
    }
}

void QEmplacement::vider()
{
    setPixmap(mum->pixmapVide);
    leJoueur=NULL;
}

bool QEmplacement::jouxte(QEmplacement *e)
{
    bool resultat;
    resultat=(ligne==e->ligne && abs(col-e->col)==1) || (col==e->col && abs(ligne-e->ligne)==1) || (abs(col-e->col)==1 && abs(ligne-e->ligne)==1 && ((e->ligne==1 && e->col==1) || (col==1 && ligne==1)));
    return resultat;
}

void QEmplacement::posePion()
{
    if(!mum->partieFinie)
    {
        //si l'emplacement est libre
        if(this->estVide())
        {
            //si il a encore des pions a poser
            if(mum->joueurActif->getNbJetons()>0)
            {
                //on met le pion du joueur
                this->setJoueur(mum->joueurActif);

                //on diminue le stock de jetons
                mum->joueurActif->enleveJetons();

                if(!mum->gagne(mum->joueurActif))
                {
                    //on switch de joueur actif
                    mum->changeJoueurActif();
                }
            }
        }
        else//si l'emplacement est déjà occupé par un pion
        {
            //si c'est le bon joueur
            if(leJoueur==mum->joueurActif)
            {
                //s'il n'est pas coincé (a voir)
                //if(jouxte())
                //{
                //si le stock est bien vide
                if(mum->joueurActif->getNbJetons()==0)
                {
                    //on part sur un deplacement
                    mum->setCurseur(*mum->joueurActif->getSonCurseur("normal"));
                    //on mémorise le futur ancien emplacement du pion
                    mum->setEmplacementDeplace(this);
                }
                //}

            }
        }
    }
}
