#include "sanshachage.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>
SansHachage::SansHachage(int N)
{
    std::cout<<"appel du constructeur de SansHachage :"<<endl;
    nmax=N;
    tab=new bucket*[nmax];
    for(int i=0;i<nmax;i++)
        tab[i]=nullptr;
    tcourant=0;
}
//SansHachage::~SansHachage(){
//    std::cout<<"appel du destructeur pour l'obet :"<<endl;
//    if(tab){
//        for(int i=0;i<nmax;i++)
//            if(tab[i]) delete tab[i];
//    }
//}

SansHachage::~SansHachage() {
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

void SansHachage::insere(QString & mv,VOITURE *v){
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
    for(int i=0;i<nmax;i++){
    if(tab[i]==nullptr){
        tab[i]=m;
        tcourant++;
    }
    else{
        if(tab[i]->voiture->marque==mv){
        m->suivant=tab[i];
        tab[i]=m;
        }
        else{
            tcourant++;
        }
    }
  }
}
VOITURE* SansHachage::get_cle(QString& m, QString& cle){
    if(contient(m,cle)){
    for(int i=0;i<nmax && tab[i];i++){
        if(tab[i]->voiture->marque==m){
            bucket *c=tab[i];
            while(c!=NULL && c->voiture->cle_voiture!=cle)
                c=c->suivant;
            if(c)
                return c->voiture;
        }
    }
    }
    return nullptr;
}

bool SansHachage::contient(QString &m,QString &cle){
    int i=0;
    while(i<nmax && tab[i] && tab[i]->voiture->marque!=m){
        i++;
    }
    if(i<nmax){
        bucket *c=tab[i];
        while(c!=NULL && c->voiture->cle_voiture!=cle)
            c=c->suivant;
        if(c)
            return true;
        else
            return false;
    }
    else
        return false;
}

void SansHachage::supprimeS(QString &mv,QString& cle){
    if(contient(mv,cle)){
        int i=0;

        while(i<nmax &&tab[i]->voiture->marque!=mv){
            i++;
        }
        bucket*c=tab[i],*d;
        if(c->voiture->cle_voiture==cle){
            d=c;
            c=c->suivant;
            delete d->voiture;
            delete d;
        }
        while (c &&c->voiture->cle_voiture!=cle){
            d=c;
            c=c->suivant;
        }
        if(c){
        d->suivant=c->suivant;
        delete c->voiture;
        delete c;
        }
    }
}

int SansHachage::taillemax(){return nmax; }

bucket *SansHachage::Tab(int i){
    return tab[i];
}
void SansHachage::affiche(){
        for(int i=0;i<nmax;i++){
            if(tab[i]){
                bucket *c=tab[i];
                while(c!=NULL){
                    std::cout << "Clé: " << c->voiture->cle_voiture.toStdString() << ", "
                              << "Marque: " << c->voiture->marque.toStdString() << ", "
                              << "Gamme: " << c->voiture->gamme.toStdString() << ", "
                              << "Modèle: " << c->voiture->modele.toStdString() << ", "
                              << "Année: " << c->voiture->annee << ", "
                              << "Photo: " <<c-> voiture->photo.toStdString() << ", "
                              << "Présentation: " << c->voiture->presentation.toStdString() << std::endl;
                    c = c->suivant;
                }
            }
        }
    }


void SansHachage::charge() {
    QSqlQuery query("SELECT cle_voiture, marque, gamme, modele, annee, image_vh, presentation FROM tabvoitures");
    while (query.next()) if(query.value(1).toString()=="Tesla"){
        VOITURE* voiture = new VOITURE();
        voiture->cle_voiture = query.value(0).toString();
        voiture->marque = query.value(1).toString();
        voiture->gamme = query.value(2).toString();
        voiture->modele = query.value(3).toString();
        voiture->annee = query.value(4).toInt();
        voiture->photo = query.value(5).toString();
        voiture->presentation = query.value(6).toString();

        QString cle = voiture->marque;
        insere(cle, voiture);
    }
}

int SansHachage::size()
{
    return (tcourant);
}
void SansHachage::sauvegarder() {
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
