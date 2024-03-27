#ifndef JOUEUR
#define JOUEUR
#include <vector>
#include "Bateau.h"
#include "Carte.h"
#include <iostream>

#define M_NORMAL  1
#define M_SONDE   2
#define M_LIGNE   3
#define M_COLONNE 4
#define M_BOMBE   5
 
class Joueur {
    public:
        Joueur(int tailleEnX, int tailleEnY);
        ~Joueur();
        bool aPerdu();
        int nBateau();
        int tirer(Coordonnee position, Joueur* adversaire);
        int sonder(Coordonnee position, Joueur* adversaire);
        bool positionBateau(int x, int y, bool horizontal, int taille);
        bool ajouterBateau(int x, int y, bool horizontal, int taille);
        int getChargement();
        void setChargement(int charge);
        int getTypeMissile();
        bool setTypeMissile(int type);
        Coordonnee getCordAttente();
        void setCordAttente(Coordonnee);
        void afficherHistoriqueTir(std::ostream& s);
        void afficherCartePreparation(std::ostream& s, Coordonnee pos, bool dir, int taille);
        void afficherCarteBateau(std::ostream& s);
        bool actualiseCarte();
        bool* getTypeAccepte();
    private:
        std::vector<Bateau*> bateau;
        Carte *carte;
        int chargement;
        int typeMissile;
        Coordonnee cordAttente;
        bool typeAccepte[5];
        int tweaksAffichage(int nombre);

};

#endif