#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#define lignes 6
#define colonnes 7
#include "Joueur.h"
class Plateau{
private:
    int tableau[lignes][colonnes];
    int tour;
public:
    Plateau();
    Plateau(const Plateau& pla);
    ~Plateau(){};
    int getTour();
    void setTour(int newtour);
    void copyTablePlateau(int t[6][7]);
    void setTablePlateau(int t[lignes][colonnes]);
    int putPion(Joueur j, int colonne);
    int nombrePionJoueurVerticale(int joueurCouleur, int ligne, int colonne);
    int nombrePionJoueurHorizontale(int joueurCouleur, int ligne, int colonne);
    int nombrePionJoueurDiagonale1(int joueurCouleur, int ligne, int colonne);
    int nombrePionJoueurDiagonale2(int joueurCouleur, int ligne, int colonne);
    bool gagner(int joueurCouleur, int ligne, int colonne);
    void annoncerGagnant(int joueurCouleur);
    void afficherToi();
    int evaluatePosition(int joueurCouleur);
    bool colonneValable(int col);
    int placer(int col, int couleur);
friend class Joueur;

};

#endif // PLATEAU_H_INCLUDED
