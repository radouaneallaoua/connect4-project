#include <iostream>
#include "JoueurIntelligent.h"
using namespace std;
int menu()
{
    int choix;
    int algorithme;
    again2:
    cout << "\t\t\t\t\tMENU - Puissance 4" << endl;
    cout << "\t\t\t\t\t-------------------" << endl;
    cout << "\t\t\t\t\t1. Jouer une partie" << endl;
    cout << "\t\t\t\t\t2. Afficher les regles du jeu" << endl;
    cout << "\t\t\t\t\t3. Quitter" << endl;
    cout << "\t\t\t\t\t-------------------" << endl<<endl;
    cout << "\t\t\t\t\tVotre choix : ";
    cin >> choix;

    switch (choix) {
        again:
        case 1:
        {
            cout << "\t\t\t\tLancement d'une nouvelle partie..." << endl<<endl;
            int choix2;
            cout<<"\t\t\t-----------------------------------------------------"<<endl;
            cout<<"\t\t\t|                                                     |"<<endl;
            cout<<"\t\t\t|                  1\  Joueur VS Joueur                |"<<endl;
            cout<<"\t\t\t|                                                     |"<<endl;
            cout<<"\t\t\t-----------------------------------------------------"<<endl;
            cout<<"\t\t\t|                                                     |"<<endl;
            cout<<"\t\t\t|                  2\  Joueur VS Machine               |"<<endl;
            cout<<"\t\t\t|                                                     |"<<endl;
            cout<<"\t\t\t-----------------------------------------------------"<<endl;
            do{
            cout<<"\t\t\t Veuillez donner Votre Choix>>>\t";
            cin>>choix2;
            }while(choix2!= 1 && choix2 !=2);
            switch(choix2)
            {
                case 1:
                {
                    return 0;
                    break;
                }
                case 2:
                {
                    cout<<"\t\t\t-----------------------------------------------------"<<endl;
                    cout<<"\t\t\t|                                                     |"<<endl;
                    cout<<"\t\t\t|                  1\   MiniMax                        |"<<endl;
                    cout<<"\t\t\t|                                                     |"<<endl;
                    cout<<"\t\t\t-----------------------------------------------------"<<endl;
                    cout<<"\t\t\t|                                                     |"<<endl;
                    cout<<"\t\t\t|                  2\   AlphaBeta                      |"<<endl;
                    cout<<"\t\t\t|                                                     |"<<endl;
                    cout<<"\t\t\t-----------------------------------------------------"<<endl;
                    int choix3;
                    do{
                    cout<<"\t\t\t\t Veillez donner votre choix>>>\t";
                    cin>>choix3;
                    }while(choix3!=2 && choix3!=1);
                    switch(choix3)
                    {
                       case 1:{
                          return 1;
                           break;
                       }
                       case 2:{
                          return 2;
                           break;
                       }
                    }
                    break;
                }

            }
            break;
        }
        case 2:
        {
            int choix4;
            cout << "\t\t\tRegles du jeu : " << endl;
            cout << "\t\t\tLe but du jeu est d'aligner 4 pions de sa couleur horizontalement, verticalement ou en diagonale." << endl;
            cout << "\t\t\tLe joueur qui parvient a aligner 4 pions en premier remporte la partie." << endl;
            cout<<"\t\t\tSi vous Voulez revenir au Menu precedent . Appuyer sur 5 sinon si vous voules quitter Appuyer sur 0:)>>>\t";
            cin>>choix4;
            switch(choix4)
            {
            case 5:
                goto again2;
            case 0:
                exit(0);
            }
            break;
        }
        case 3:
        {
            cout << "\t\t\t\tMerci d'avoir joue !" << endl;
            exit(0);
            break;
        }
        default:
            cout << "\t\t\tChoix invalide. Veuillez choisir une option valide." << endl;
            goto again;
    }
}
int main()
{
    system("color 9");
    int algorithmeDuJeu=menu();
    system("cls");
    int gagnant = 0;
    Plateau plat;
    Joueur j1(plat.getTour());
    Joueur j2(plat.getTour()+1);
    JoueurIntelligent machine(plat.getTour()+1);
    bool lancementDuJeux = true;
    while(lancementDuJeux)
    {
        switch(plat.getTour())
        {
        case 1:
        {
            plat.afficherToi();
            int choixColonne = j1.takeposition();
            int ligneCorrespondante = plat.putPion(j1.getCouleur(),choixColonne);
            plat.afficherToi();
            if(plat.gagner(j1.getCouleur(),ligneCorrespondante,choixColonne))
            {
                gagnant =1;
                lancementDuJeux = false;
            }
            plat.setTour(2);
            system("cls");
            break;
        }
        case 2:
        {
            if(algorithmeDuJeu == 0) //partie joueur vs joueur
            {
                plat.afficherToi();
                int choixColonne = j2.takeposition();
                int ligneCorrespondante = plat.putPion(j2.getCouleur(),choixColonne);
                plat.afficherToi();
                if(plat.gagner(j2.getCouleur(),ligneCorrespondante,choixColonne))
                {
                    gagnant =1;
                    lancementDuJeux = false;
                }
                plat.setTour(1);
                system("cls");
                break;
            }
            if(algorithmeDuJeu == 1)
            {
                plat.afficherToi();
                cout<<"\t\t\t\tNombre de Noeuds explores>>"<<machine.getNoeuds()<<endl;
                Plateau copie(plat);
                int ColonneMachine = machine.Minimax(copie,0,true,0,0);
                cout<<"\t\t\t\tNombre de Noeuds explores>>"<<machine.getNoeuds()<<endl;
                int ligneCorrespondante = plat.placer(ColonneMachine,2);
                if(plat.gagner(2,ligneCorrespondante,ColonneMachine))
                {
                    gagnant = 2;
                    lancementDuJeux = false;
                }
                plat.setTour(1);
                system("pause");
                system("cls");
                break;
            }
            if(algorithmeDuJeu == 2)
            {
                plat.afficherToi();
                cout<<"\t\t\t\tNombre de Noeuds explores>>"<<machine.getNoeuds()<<endl;
                Plateau copie(plat);
                int ColonneMachine = machine.AlphaBeta(copie,0,true,0,0,-10000000,10000000);
                cout<<"\t\t\t\tNombre de Noeuds explores>>"<<machine.getNoeuds()<<endl;
                int ligneCorrespondante = plat.placer(ColonneMachine,2);
                if(plat.gagner(2,ligneCorrespondante,ColonneMachine))
                {
                    gagnant = 2;
                    lancementDuJeux = false;
                }
                plat.setTour(1);
                system("pause");
                system("cls");
                break;
            }
        }
    }}
    plat.afficherToi();
    plat.annoncerGagnant(gagnant);
    return 0;
}
