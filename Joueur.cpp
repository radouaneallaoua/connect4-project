#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur(int nombre){
    couleur = nombre;
    score = 0;
}

int Joueur::takeposition(){
    int colonne;  //colonne choisie
    cout<<"Le joueur "<<couleur<<": Entrer une colonne\t";
    cin>>colonne;
    return colonne;
}

int Joueur::getCouleur()const{
    return couleur;
}

int Joueur::getScore()const{
    return score;
}
