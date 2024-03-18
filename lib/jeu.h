#ifndef JEU
#define JEU

#define CONFIRMER 0
#define QUITTER 1
#define INCORRECT 2
#define MODE_NORMAL 1
#define MODE_RAFALE 2
#define MODE_STRATEGIE 3

#include <iostream>
#include "Joueur.h"

class Jeu {
    public:
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
        int menuTir(std::ostream& sout, std::istream& sin,Joueur* joueur, Joueur* adversaire);
        bool afficherFin(std::ostream& sout);
        int menuFin(std::ostream& sout, std::istream& sin);
        void ajouterJoueur();
        Joueur* getJoueur(int index);
        int getMode();
    private:
        int tailleEnX;
        int tailleEnY;
        int mode;
        std::vector<Joueur*> vecJoueur;
};

#endif