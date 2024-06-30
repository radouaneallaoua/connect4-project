#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Joueur{
    int couleur;
    int score;
public:
    Joueur(int nombre);
    int takeposition();
    int getCouleur()const;
    int getScore() const;
};

#endif // JOUEUR_H_INCLUDED
