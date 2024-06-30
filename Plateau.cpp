#include <iostream>
#include "Plateau.h"
#include <cmath>
#include <vector>


using namespace std;

Plateau::Plateau()
{
    for(int i=0; i<lignes; i++) for(int j=0; j<colonnes; j++) tableau[i][j]=0;
    tour =1;
}

Plateau::Plateau(const  Plateau& pla)  // constructeur qui construit un  plateau a partir d'un autre plateau
{
    for(int i=0; i<lignes; i++) for(int j=0; j<colonnes; j++) tableau[i][j] = pla.tableau[i][j];
    tour = pla.tour;
}

int Plateau::getTour()
{
    return tour;
}

void Plateau::setTour(int newtour)
{
    tour = newtour;
}

void Plateau::copyTablePlateau(int t[6][7])
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            t[i][j]=tableau[i][j];
        }
    }
}

void Plateau::setTablePlateau(int t[lignes][colonnes])
{
    int i,j;
    for(i=0; i<lignes; i++)
    {
        for(j=0; j<colonnes; j++)
        {
            tableau[i][j]=t[i][j];
        }
    }
}

int  Plateau::putPion(Joueur j,int colonne)     //fonction qui place un pion pour le joueur en parametres et qui retourne la ligne correspondante
{
    int indice = 0;
    for(int i=lignes-1; i>=0; i--)
    {
        if(tableau[i][colonne] == 0)
        {
            tableau[i][colonne] = j.getCouleur();
            indice =1;
            return i;
        }
    }
    while(indice == 0) // si la colonne choisie est pleine donnez la main au joueur pour jouer une autre fois
    {
        cout<<"la colonne est pleine (..).Veillez donner une autre colonne"<<endl;
        int choixcolonne= j.takeposition();
        return putPion(j,choixcolonne);
    }
}

int Plateau::nombrePionJoueurVerticale(int joueurCouleur,int ligne,int colonne) //fonction qui calcule le nombre de pions adjacents
//virticalement du joueur a partir de la position qu'il a jouee
{
    int contour=1;
    int bas ;
    int haut ;
    for(bas=ligne+1; bas<lignes; bas++)
    {
        if(tableau[bas][colonne] == joueurCouleur && contour<4)
        {
            contour++;
        }
        else
        {
            break;
        }
    }
    for(haut=ligne-1; haut>=0; haut--)
    {
        if(tableau[haut][colonne] == joueurCouleur && contour<4)
        {
            contour++;
        }
        else
        {
            break;
        }
    }
    return contour;
}

int Plateau::nombrePionJoueurHorizontale(int joueurCouleur,int ligne,int colonne) //fonction qui calcule le nombre de pions adjacents
//horizontalement du joueur a partir de la position qu'il a jouee
{
    int contour=1;
    int droite ;
    int gauche ;
    for(droite=colonne+1; droite<colonnes; droite++)
    {
        if(tableau[ligne][droite] == joueurCouleur && contour<4)
        {
            contour++;
        }
        else
        {
            break;
        }
    }
    for(gauche=colonne-1; gauche>=0; gauche--)
    {
        if(tableau[ligne][gauche] ==joueurCouleur && contour<4)
        {
            contour++;
        }
        else
        {
            break;
        }
    }
    return contour;
}

int Plateau::nombrePionJoueurDiagonale1(int joueurCouleur,int ligne,int colonne) //fonction qui calcule le nombre de pions adjacents
//sur la diagonale 1 du joueur a partir de la position qu'il a jouee
{
    int contour=1;
    int haut = ligne-1;
    int bas =ligne +1 ;
    int droite =colonne+1;
    int gauche =colonne-1;
    while(droite<colonnes && haut>=0)
    {
        if(tableau[haut][droite] == joueurCouleur && contour < 4)
        {
            contour++;
            haut--;
            droite++;
        }
        else
        {
            break;
        }
    }
    while(gauche>=0 && bas<lignes)
    {
        if(tableau[bas][gauche] == joueurCouleur && contour < 4)
        {
            contour++;
            bas++;
            gauche--;
        }
        else
        {
            break;
        }
    }
    return contour;
}

int Plateau::nombrePionJoueurDiagonale2(int joueurCouleur,int ligne,int colonne) //fonction qui calcule le nombre de pions adjacents
//sur la diagonale 2 du joueur a partir de la position qu'il a jouee
{
    int contour=1;
    int haut = ligne-1;
    int bas =ligne +1 ;
    int droite =colonne+1;
    int gauche =colonne-1;
    while(droite<colonnes && bas<lignes)
    {
        if(tableau[bas][droite] == joueurCouleur && contour < 4)
        {
            contour++;
            bas++;
            droite++;
        }
        else
        {
            break;
        }
    }
    while(gauche>=0 && haut>=0)
    {
        if(tableau[haut][gauche] == joueurCouleur && contour < 4)
        {
            contour++;
            haut--;
            gauche--;
        }
        else
        {
            break;
        }
    }
    return contour;
}

bool Plateau::gagner(int joueurCouleur,int ligne,int colonne) //fonction qui determine si un joueur a gagne ou non
{
    return(nombrePionJoueurVerticale(joueurCouleur,ligne,colonne) == 4 || nombrePionJoueurHorizontale(joueurCouleur,ligne,colonne) == 4 || nombrePionJoueurDiagonale1(joueurCouleur,ligne,colonne) == 4 || nombrePionJoueurDiagonale2(joueurCouleur,ligne,colonne) == 4 );
}

void Plateau::annoncerGagnant(int joueurCouleur)
{
    cout<<"le joueur "<<joueurCouleur<<" qui gagne(..)"<<endl;
}

void Plateau::afficherToi()
{
    cout<<"\t\t\t\t";
    cout<<"-----0--------1--------2--------3--------4--------5--------6----"<<endl;
    for(int i=0; i<lignes; i++)
    {
        cout<<"\t\t\t\t";
        cout<<"|        |        |        |        |        |        |        |"<<endl;
        cout<<"\t\t\t\t";
        for(int j=0; j<colonnes; j++)
        {
            cout<<"|   ";
            char joueurCaractere = (tableau[i][j] == 0)? ' ':(tableau[i][j] == 1)? 'O':'X';
            cout<<joueurCaractere;
            cout<<"    ";
        }
        cout<<"|"<<endl;
        cout<<"\t\t\t\t";
        cout<<"|        |        |        |        |        |        |        |"<<endl;
        cout<<"\t\t\t\t";
        cout<<"----------------------------------------------------------------"<<endl;
    }
}

int Plateau::evaluatePosition(int player)
{
    /*int score = 0;

    // Comptez les jetons alignés horizontalement.
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes - 3; j++)
        {
            int count_player = 0, count_opponent = 0;
            for (int k = 0; k < 4; k++)
            {
                if (tableau[i][j+k] == player)
                {
                    count_player++;
                }
                else if (tableau[i][j+k] == 3-player)
                {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0)
            {
                switch(count_player)
                {
                case 3:
                    score += pow(15, count_player+2);
                    break;
                case 2:
                    score += pow(10, count_player+1);
                    break;
                case 1:
                    score += pow(5, count_player);
                    break;
                }
            }
            else if (count_opponent > 0 && count_player == 0)
            {
                switch(count_opponent)
                {
                case 3:
                    score -= pow(15, count_opponent+2);
                    break;
                case 2:
                    score -= pow(10, count_opponent+1);
                    break;
                case 1:
                    score -= pow(5, count_opponent);
                    break;
                }
            }
        }
    }

    // Comptez les jetons alignés verticalement.
    for (int i = 0; i < lignes - 3; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            int count_player = 0, count_opponent = 0;
            for (int k = 0; k < 4; k++)
            {
                if (tableau[i+k][j] == player)
                {
                    count_player++;
                }
                else if (tableau[i+k][j] == 3-player)
                {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0)
            {
                switch(count_player)
                {
                case 3:
                    score += pow(15, count_player+2);
                    break;
                case 2:
                    score += pow(10, count_player+1);
                    break;
                case 1:
                    score += pow(5, count_player);
                    break;
                }
            }
            else if (count_opponent > 0 && count_player == 0)
            {
                switch(count_opponent)
                {
                case 3:
                    score -= pow(20, count_opponent+2);
                    break;
                case 2:
                    score -= pow(10, count_opponent+1);
                    break;
                case 1:
                    score -= pow(5, count_opponent);
                    break;
                }
            }
        }
    }

    // Comptez les jetons alignés en diagonale (de haut en bas).
    for (int i = 0; i < lignes - 3; i++)
    {
        for (int j = 0; j < colonnes - 3; j++)
        {
            int count_player = 0, count_opponent = 0;
            for (int k = 0; k < 4; k++)
            {
                if (tableau[i+k][j+k] == player)
                {
                    count_player++;
                }
                else if (tableau[i+k][j+k] == 3-player)
                {
                    count_opponent++;
                }
            }
           if (count_player > 0 && count_opponent == 0)
            {
                switch(count_player)
                {
                case 3:
                    score += pow(15, count_player+2);
                    break;
                case 2:
                    score += pow(10, count_player+1);
                    break;
                case 1:
                    score += pow(5, count_player);
                    break;
                }
            }
            else if (count_opponent > 0 && count_player == 0)
            {
                switch(count_opponent)
                {
                case 3:
                    score -= pow(20, count_opponent+2);
                    break;
                case 2:
                    score -= pow(10, count_opponent+1);
                    break;
                case 1:
                    score -= pow(5, count_opponent);
                    break;
                }
            }
        }
    }

// Comptez les jetons alignés en diagonale (de bas en haut).
    for (int i = 3; i < lignes; i++)
    {
        for (int j = 0; j < colonnes - 3; j++)
        {
            int count_player = 0, count_opponent = 0;
            for (int k = 0; k < 4; k++)
            {
                if (tableau[i-k][j+k] == player)
                {
                    count_player++;
                }
                else if (tableau[i-k][j+k] == 3-player)
                {
                    count_opponent++;
                }

            }
             if (count_player > 0 && count_opponent == 0)
            {
                switch(count_player)
                {
                case 3:
                    score += pow(20, count_player+2);
                    break;
                case 2:
                    score += pow(10, count_player+1);
                    break;
                case 1:
                    score += pow(5, count_player);
                    break;
                }
            }
            else if (count_opponent > 0 && count_player == 0)
            {
                switch(count_opponent)
                {
                case 3:
                    score -= pow(20, count_opponent+2);
                    break;
                case 2:
                    score -= pow(10, count_opponent+1);
                    break;
                case 1:
                    score -= pow(5, count_opponent);
                    break;
                }
            }
        }
    }

    return score;*/
    int score = 0;
    // Évaluation des séquences horizontales
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            int count_player = 0;
            int count_opponent = 0;
            for (int k = 0; k < 4; k++) {
                if (tableau[i][j+k] == player) {
                    count_player++;
                } else if (tableau[i][j+k] != 0) {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0) {
                    if(count_player ==3)
                         score += 100;
                    if(count_player == 2)
                         score += 10;
                    else{score+=2;}
            }
           else if (count_opponent > 0 && count_player == 0) {
                    if(count_opponent ==3)
                         score -=90;
                    if(count_opponent == 2)
                         score -=10;
                    else{score-=2;}
            }

        }
    }

    // Évaluation des séquences verticales
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            int count_player = 0;
            int count_opponent = 0;
            for (int k = 0; k < 4; k++) {
                if (tableau[i+k][j] == player) {
                    count_player++;
                } else if (tableau[i+k][j] != 0) {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0) {
                    if(count_player ==3)
                         score += 100;
                    if(count_player == 2)
                         score += 10;
                    else{score+=2;}
            }
           else if (count_opponent > 0 && count_player == 0) {
                    if(count_opponent ==3)
                         score -=90;
                    if(count_opponent == 2)
                         score -=10;
                    else{score-=2;}
            }

        }
    }

    // Évaluation des séquences diagonales /
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int count_player = 0;
            int count_opponent = 0;
            for (int k = 0; k < 4; k++) {
                if (tableau[i+k][j+k] == player) {
                    count_player++;
                } else if (tableau[i+k][j+k] != 0) {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0) {
                    if(count_player ==3)
                         score += 100;
                    if(count_player == 2)
                         score += 10;
                    else{score+=2;}
            }
           else if (count_opponent > 0 && count_player == 0) {
                    if(count_opponent ==3)
                         score -=90;
                    if(count_opponent == 2)
                         score -=10;
                    else{score-=2;}
            }

        }
    }
    // Évaluation des séquences diagonales
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 7; j++) {
            int count_player = 0;
            int count_opponent = 0;
            for (int k = 0; k < 4; k++) {
                if (tableau[i+k][j-k] == player) {
                    count_player++;
                } else if (tableau[i+k][j-k] != 0) {
                    count_opponent++;
                }
            }
            if (count_player > 0 && count_opponent == 0) {
                    if(count_player ==3)
                         score += 100;
                    if(count_player == 2)
                         score += 10;
                    else{score+=2;}
            }
           else if (count_opponent > 0 && count_player == 0) {
                    if(count_opponent ==3)
                         score -=90;
                    if(count_opponent == 2)
                         score -=10;
                    else{score-=2;}
            }

        }
    }

    return score;
}


bool Plateau::colonneValable(int col)
{
    for(int i=5; i>=0; i--)
    {
        if(tableau[i][col] == 0)
        {
            return true;
        }
    }
    return false;
}

int  Plateau::placer(int col,int couleur)
{
    for(int i=5; i>=0; i--)
    {
        if(tableau[i][col] == 0)
        {
            tableau[i][col] =couleur;
            return i;
        }
    }
}
