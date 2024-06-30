#ifndef JOUEURINTELLIGENT_H_INCLUDED
#define JOUEURINTELLIGENT_H_INCLUDED
#include "Joueur.h"
#include "Plateau.h"

class JoueurIntelligent: public Joueur{
private:
    int nombreNoeudsExplores;
    int profondeurLimite;
public:
    JoueurIntelligent(int nombre):Joueur(nombre){
        nombreNoeudsExplores=0;
        profondeurLimite=7;
    }
    int getNoeuds();
    int Minimax(Plateau pla, int profondeur, bool MaxQuiJoue, int lig, int col);
    int AlphaBeta(Plateau pla, int profondeur, bool MaxQuiJoue, int lig, int col, int alpha, int beta);

};

#endif // JOUEURINTELLIGENT_H_INCLUDED
