#include "NHachage.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>
using namespace std;
NotreTableHache::NotreTableHache(int n)
{
    nmax = n;
    tab = new bucket*[n];
    for(int i=0;i<n;i++)
        tab[i]=nullptr;
    taille_courant=0;
}

int NotreTableHache::taillemax(){return nmax; }

bucket *NotreTableHache::Tab(int i){
    return tab[i];
}

void NotreTableHache::insertion(QString& valeur ,VOITURE *v)
{
    unsigned int i=Hach1(valeur);
    bucket* m=new bucket;
    m->voiture=new VOITURE;
    m->voiture->cle_voiture=v->cle_voiture;
    m->voiture->annee=v->annee;
    m->voiture->gamme=v->gamme;
    m->voiture->marque=v->marque;
    m->voiture->modele=v->modele;
    m->voiture->photo=v->photo;
    m->voiture->presentation=v->presentation;
    m->suivant=nullptr;
    m->suivant=tab[i];
    tab[i]=m;
   taille_courant++;
}


VOITURE* NotreTableHache::get_voiture(QString& Mv , QString& cle)
{ unsigned int h =Hach1(Mv);
    if(tab[h]==nullptr)
        return nullptr;
    bucket* tmp=tab[h];
    while(tmp && tmp->voiture->cle_voiture!=cle)
        tmp=tmp->suivant;
    if(tmp)
        return tmp->voiture;
    return nullptr;
}

void NotreTableHache::suppression(QString& Mv ,QString& cle)
{unsigned int h=Hach1(Mv);
    if(contient(Mv))
    { bucket* tmp=tab[h] , *p;
        if(tab[h]->voiture->cle_voiture==cle)
           {tab[h]=tab[h]->suivant;
            delete tmp->voiture;
            delete tmp;
           }
       else
       {
        while(tmp && tmp->voiture->cle_voiture!=cle)
        {  p=tmp;
            tmp=tmp->suivant;}
        if(tmp)
          {  p->suivant=tmp->suivant;
             delete tmp->voiture;
            delete tmp; }
       }
        taille_courant--;
    }
}

bool NotreTableHache::contient(QString& Mv)
{ unsigned int h=Hach1(Mv);
    return (tab[h]!=nullptr);
}

long NotreTableHache::size()
{
    return (taille_courant);
}



void NotreTableHache::affiche() {
    for (int i = 0; i < nmax; ++i) {
         if(tab[i]!=nullptr){
        bucket *current = tab[i];
        while (current != nullptr) {
            VOITURE *voiture = current->voiture;
            std::cout << "Clé: " << voiture->cle_voiture.toStdString() << ", "
                      << "Marque: " << voiture->marque.toStdString() << ", "
                      << "Gamme: " << voiture->gamme.toStdString() << ", "
                      << "Modèle: " << voiture->modele.toStdString() << ", "
                      << "Année: " << voiture->annee << ", "
                      << "Photo: " << voiture->photo.toStdString() << ", "
                      << "Présentation: " << voiture->presentation.toStdString() << std::endl;
            current = current->suivant;
        }
         }
    }
}




// Méthode pour charger les données depuis la base de données
void NotreTableHache::charger() {
    QSqlQuery query("SELECT cle_voiture, marque, gamme, modele, annee, image_vh, presentation FROM tabvoitures");
    while (query.next()) if(query.value(1).toString()=="Toyota"){
        VOITURE* voiture = new VOITURE();
        voiture->cle_voiture = query.value(0).toString();
        voiture->marque = query.value(1).toString();
        voiture->gamme = query.value(2).toString();
        voiture->modele = query.value(3).toString();
        voiture->annee = query.value(4).toInt();
        voiture->photo = query.value(5).toString();
        voiture->presentation = query.value(6).toString();

        QString cle = voiture->marque;
        insertion(cle, voiture);
    }
}



NotreTableHache::~NotreTableHache() {
    for (int i = 0; i < nmax; ++i) {
        bucket *current = tab[i];
        while (current != nullptr) {
            bucket *next = current->suivant;
            delete current->voiture;
            delete current;
            current = next;
        }
    }
    delete[] tab;
}


// Méthode pour sauvegarder les données dans la base de données
void NotreTableHache::sauvegarder() {
    QSqlQuery query;
    for (int i = 0; i < nmax; ++i) {
        bucket *current = tab[i];
        while (current != nullptr) {
            VOITURE* voiture = current->voiture;

            query.prepare("REPLACE INTO tabvoitures (cle_voiture, marque, gamme, modele, annee, image_vh, presentation) "
                          "VALUES (:cle_voiture, :marque, :gamme, :modele, :annee, :image_vh, :presentation)");
            query.bindValue(":cle_voiture", voiture->cle_voiture);
            query.bindValue(":marque", voiture->marque);
            query.bindValue(":gamme", voiture->gamme);
            query.bindValue(":modele", voiture->modele);
            query.bindValue(":annee", voiture->annee);
            query.bindValue(":image_vh", voiture->photo);
            query.bindValue(":presentation", voiture->presentation);

            if (!query.exec()) {
                std::cerr << "Erreur lors de la sauvegarde: " << query.lastError().text().toStdString() << std::endl;
            }
            current = current->suivant;
        }
    }
}

unsigned int NotreTableHache::Hach1(QString &cle) {
    unsigned int hash = 0;
    for (int i = 0; i < cle.length(); ++i) {
        hash = 31 * hash + cle[i].unicode();
    }
    return hash % nmax;
}

unsigned int NotreTableHache::Hach2(QString &cle) {
    unsigned int hash = 0;
    for (int i = 0; i < cle.length(); ++i) {
        hash = 65599 * hash + cle[i].unicode();
    }
    return hash % nmax;
}

unsigned int NotreTableHache::Hach3(QString &cle) {
    unsigned int hash = 0;
    for (int i = 0; i < cle.length(); ++i) {
        hash = hash ^ ((hash << 5) + cle[i].unicode() + (hash >> 2));
    }
    return hash % nmax;
}



