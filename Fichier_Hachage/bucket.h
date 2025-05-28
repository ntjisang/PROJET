#include<iostream>
using namespace std;
struct maison{
    string cle;
    string type;
    string standing;
    int nb_chambres;
    int nb_toilettes;
    string photo;
    string description;
    
};
struct bucket{
    maison*m;
    bucket*suiv;
};