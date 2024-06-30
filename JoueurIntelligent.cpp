#include <iostream>
#include "JoueurIntelligent.h"
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
using namespace std;

int JoueurIntelligent::getNoeuds(){
    return nombreNoeudsExplores;
}

int JoueurIntelligent::Minimax(Plateau pla,int profondeur,bool MaxQuiJoue,int lig,int colon)
    {
        int sauvegarde[6][7];
        pla.copyTablePlateau(sauvegarde);
        if(pla.gagner(1,lig,colon) && MaxQuiJoue)
            return -10000;
        if(pla.gagner(2,lig,colon) && !MaxQuiJoue)
            return  10000;
        if(profondeur == profondeurLimite)
        {
            return pla.evaluatePosition(1);
        }
        int evaluation[7] = {};
        if(MaxQuiJoue)
        {
            list<int> successeurs;
            for(int col = 0; col<7; col++)
            {

                if(pla.colonneValable(col))
                {
                    int ligne = pla.placer(col,2);
                    int suivant = Minimax(pla,profondeur+1,false,ligne,col);
                    successeurs.push_front(suivant);
                    nombreNoeudsExplores++;
                    pla.setTablePlateau(sauvegarde);
                    evaluation[col]=suivant;
                }
            }
            for(int col=0;col<colonnes;col++){
                int plusGrand = *max_element(successeurs.begin(), successeurs.end());
                if (evaluation[col] == plusGrand)
                {
                    if (profondeur==0)
                          return col;
                    else
                        return evaluation[col];
                }
            }
        }
       else if(!MaxQuiJoue)
        {
           list<int> successeurs;
            for(int col = 0; col<7; col++)
            {
                if(pla.colonneValable(col))
                {
                    int ligne = pla.placer(col,1);
                    int suivant = Minimax(pla,profondeur+1,true,ligne,col);
                    successeurs.push_front(suivant);
                    nombreNoeudsExplores++;
                    pla.setTablePlateau(sauvegarde);
                    evaluation[col]=suivant;
                }
            }
            for(int col=0;col<colonnes;col++){
                int plusPetit = *min_element(successeurs.begin(), successeurs.end());
                if (evaluation[col] == plusPetit)
                {
                    if (profondeur == 0)
                          return col;
                    else
                        return evaluation[col];
                }
            }
        }
    }

int JoueurIntelligent::AlphaBeta(Plateau pla,int profondeur,bool MaxQuiJoue,int lig,int colon,int alpha,int beta)
    {
        int sauvegarde[6][7];
        pla.copyTablePlateau(sauvegarde);
        if(pla.gagner(1,lig,colon))
            return -10000;
        if(pla.gagner(2,lig,colon))
            return  10000;
        if(profondeur == profondeurLimite)
        {
            return pla.evaluatePosition(1);
        }
        int evaluation[7] = {0};
        if(MaxQuiJoue)
        {
            int moinsInfini=-100000000;
            list<int> successeurs;
            for(int col = 0; col<7; col++)
            {
                if(pla.colonneValable(col))
                {
                    int ligne = pla.placer(col,2);
                    int suivant = AlphaBeta(pla,profondeur+1,false,ligne,col,alpha,beta);
                    successeurs.push_front(suivant);
                    nombreNoeudsExplores++;
                    pla.setTablePlateau(sauvegarde);
                    evaluation[col]=suivant;
                    moinsInfini = max( moinsInfini, suivant);
                    alpha = max( alpha,moinsInfini);
                    if (beta<alpha) //elagage des branches expoles inutilement
                        break;
                }
            }
            for(int col=0;col<colonnes;col++){
                int plusGrand = *max_element(successeurs.begin(), successeurs.end());
                if (evaluation[col] == plusGrand)
                {
                    if (profondeur == 0)
                          return col;
                    else
                        return evaluation[col];
                }
            }
        }
        else if(!MaxQuiJoue)
        {
            int plusInfini=100000000;
            list<int> successeurs;
            for(int col = 0; col<7; col++)
            {
                if(pla.colonneValable(col))
                {
                    int ligne = pla.placer(col,1);
                    int suivant = AlphaBeta(pla,profondeur+1,true,ligne,col,alpha,beta);
                    successeurs.push_front(suivant);
                    nombreNoeudsExplores++;
                    pla.setTablePlateau(sauvegarde);
                    evaluation[col]=suivant;
                    plusInfini = min( plusInfini, suivant);
                    beta = min( beta,plusInfini);
                    if (beta<alpha)  //elagage des branches expoles inutilement
                        break;
                }
            }
            for(int col=0;col<colonnes;col++){
                int plusPetit = *min_element(successeurs.begin(), successeurs.end());
                if (evaluation[col] == plusPetit)
                {
                    if (profondeur == 0)
                          return col;
                    else
                        return evaluation[col];
                }
            }
        }
    }
