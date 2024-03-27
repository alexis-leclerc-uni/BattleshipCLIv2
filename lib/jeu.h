#ifndef JEU
#define JEU

#define CONFIRMER 0
#define QUITTER 1
#define INCORRECT 2
#define ATTENTE 3
#define MODE_NORMAL 1
#define MODE_RAFALE 2
#define MODE_STRATEGIE 3

#define MIN_X 5
#define MIN_Y 5
#define MAX_X 15
#define MAX_Y 15

#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>
#include "Joueur.h"
#include "../external_libs/concurrent_queue.hpp"

using lime62::concurrent_queue;

class Jeu {
    public:
        Jeu(concurrent_queue<std::string>* q);
        Jeu();
        ~Jeu();
        bool afficherStartUp(std::ostream& sout);
        int menuStartUp(std::ostream& sout, std::istream& sin);
        bool afficherReglage(std::ostream& sout);
        bool afficherTailleEnX(std::ostream& sout);
        bool afficherTailleEnY(std::ostream& sout);
        bool afficherMode(std::ostream& sout);
        int menuReglage(std::ostream& sout, std::istream& sin);
        int menuJeuNormal(std::ostream& sout, std::istream& sin);
        int menuJeuRafale(std::ostream& sout, std::istream& sin);
        int menuJeuStrategique(std::ostream& sout, std::istream& sin);
        bool afficherInitJoueur(std::ostream& sout, Joueur *joueur);
        bool afficherInitTaille(std::ostream& sout, Joueur *joueur, int taille);
        int menuInitJoueur(std::ostream& sout, std::istream& sin,Joueur* joueur);
        bool afficherTir1(std::ostream& sout, Joueur *joueur, Joueur *adversaire);
        bool afficherTir2(std::ostream& sout, Joueur* joueur, Joueur* adversaire);
        bool afficherTir3(std::ostream& sout, Joueur* joueur, Joueur* adversaire);
        bool afficherTir4(std::ostream& sout, Joueur* joueur, Joueur* adversaire);
        int menuTir(std::ostream& sout, std::istream& sin,Joueur* joueur, Joueur* adversaire);
        bool afficherFin(std::ostream& sout);
        int menuFin(std::ostream& sout, std::istream& sin);
        void ajouterJoueur();
        Joueur* getJoueur(int index);
        int getMode();
        void sautDePage(std::ostream& sout);
    private:
        int valPot;
        int tailleEnX;
        int tailleEnY;
        int mode;
        concurrent_queue<std::string>* q;
        std::vector<Joueur*> vecJoueur;
};

#endif