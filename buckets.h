#ifndef BUCKETS_H
#define BUCKETS_H

#include <iostream>
 #include <QString>

using namespace std;

struct VOITURE{
    QString cle_voiture;
    QString marque;
    QString gamme;
    QString modele;
    int annee;
    QString photo;
    QString presentation;
};

struct bucket{
    VOITURE * voiture;
    bucket *suivant;
};

#endif // BUCKETS_H
