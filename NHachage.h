#ifndef NHACHAGE_H
#define NHACHAGE_H
#include "buckets.h"
#include <QDebug>

class NotreTableHache
{
 protected:
    bucket ** tab;
    int nmax;
    int taille_courant;
 public:
    NotreTableHache(int );
    ~NotreTableHache();
    void insertion(QString& ,VOITURE *);
    VOITURE* get_voiture(QString& , QString&);
    void suppression(QString& ,QString&);
    bool contient(QString& );
    long size();
    bool Est_vide();
    void charger();
    int taillemax();
    void affiche();
    void sauvegarder();
    unsigned int Hach1(QString& );
    unsigned int Hach2(QString& );
    unsigned int Hach3(QString& );
  // friend void MainWindow::afficherVoitures();
    bucket* Tab(int);
};
#endif // NHACHAGE_H
//Le Bon