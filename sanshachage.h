#ifndef SANSHACHAGE_H
#define SANSHACHAGE_H
#include "buckets.h"
#include <QDebug>


class SansHachage
{
private :
    bucket **tab;
    int nmax;
    int tcourant;
public:
    SansHachage(int);
    ~SansHachage();
    void insere(QString &,VOITURE *);
    void charge();
    void supprimeS(QString &,QString&);
    VOITURE* get_cle(QString& , QString&);
    bool contient(QString& ,QString&);
     int taillemax();
      bucket* Tab(int);
    int size();
    bool Est_vide();
    void charger();
    void affiche();
    void sauvegarder();
};

#endif // SANSHACHAGE_H
