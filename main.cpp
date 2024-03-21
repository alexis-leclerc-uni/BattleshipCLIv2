// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "lib/jeu.h"
#include "manette.h"
#include <fstream>
#include <thread> 

int lejeu();
int manetteFn();

int main()
{

    //il y aurait dequoi à patenter si on veut que les deux puisse print du serial, je le fais pas car c'est pas le but final du jeu
    std::thread t2(manetteFn);
    t2.join();
    std::thread t1(lejeu);
    t1.join();
    return 0;
}

int manetteFn(){
    const std::string &port = "COM3";
    Manette *manette = new Manette(port);
    return 0;
}


int lejeu()
{
    Jeu jeu;
    int reponse;
    while ((reponse = jeu.menuStartUp(std::cout, std::cin)) == INCORRECT) {}
    if (reponse == QUITTER)
        return 0;
    //Le joueur commence
    do {
        //jeu.menuReglage(std::cout, myFile);
        jeu.menuReglage(std::cout, std::cin);
        jeu.ajouterJoueur();
        jeu.ajouterJoueur();
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        switch (jeu.getMode()) {
        case MODE_NORMAL:
            jeu.menuJeuNormal(std::cout, std::cin);
            break;
        case MODE_RAFALE:
            jeu.menuJeuRafale(std::cout, std::cin);
            break;
        case MODE_STRATEGIE:
            jeu.menuJeuStrategique(std::cout, std::cin);
            break;
        }
        
        while ((reponse = jeu.menuFin(std::cout, std::cin)) == INCORRECT) {}
        if (reponse == QUITTER)
            return 0;
    } while (true);
    //myFile.close();
    //�crire la base
    
    return 0;
}