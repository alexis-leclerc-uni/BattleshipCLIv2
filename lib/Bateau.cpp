#include "Bateau.h"

//Description : Le constructeur permet la création de la classe Bateau
//Entrée : La position du bateau (en bas à gauche) en coordonnee x et y, l'orientation (horizontale et verticale) et la taille
//Sortie : Il n'y a pas de sortie
Bateau::Bateau(int x1, int y1, bool horizontal1, int taille1)
{
    coordonnee = { x1,y1 };
    horizontal = horizontal1;
    taille = taille1;
    cases = new bool[taille];
    for (int i = 0; i < taille; i++)
        cases[i] = true;
    coule = false;
}
//Description : Le déconstructeur permet de détruire l'instance. Détruit le tableau dynamique cases
//Entrée : Aucune entrée
//Sortie : Aucune sortie
Bateau::~Bateau()
{
    delete[] cases;
}
/*
//Description : Place le bateau sur la carte
//Entrée : Prend la position et l'orientation
//Sortie : Retourne si le bateau a été placé sur la carte
bool Bateau::placerBateau(Coordonnee position1, bool horizontal1)
{
    return false;
}
*/
//Description : Vérifie si le bateau est coule
//Entrée : Aucune entrée
//Sortie : Retourne un bool
bool Bateau::getCoule()
{
    return coule;
}
//Description : Endommage le bateau si le tir l'atteint bel et bien
//Entrée : Aucune entrée
//Sortie : Renvoie s'il a vraiment été touché
bool Bateau::endommagerBateau(Coordonnee position)
{
    if (horizontal && coordonnee.y == position.y && coordonnee.x <= position.x && position.x < coordonnee.x + taille)
    {
        cases[position.x - coordonnee.x] = false;
        coule = true;
        for (int i = 0; i < taille; i++)
        {
            if (cases[i])
            {
                coule = false;
                break;
            }
        }
        return true;
    }
    if (coordonnee.x == position.x && coordonnee.y <= position.y && position.y < coordonnee.y + taille)
    {
        cases[position.y - coordonnee.y] = false;
        coule = true;
        for (int i = 0; i < taille; i++)
        {
            if (cases[i])
            {
                coule = false;
                break;
            }
        }
        return true;
    }
    return false;
}
//Description : Renvoie la position (en bas à gauche) du bateau
//Entrée : Aucune entrée
//Sortie : Retourne la coordonnee
Coordonnee Bateau::getCoordonnee()
{
    return coordonnee;
}
//Description : Renvoie l'orientation du bateau
//Entrée : Aucune entrée
//Sortie : Retourne vrai si horizontale, faux si verticale
bool Bateau::getOrientation()
{
    return horizontal;
}
//Description : Renvoie la taille du bateau
//Entrée : Aucune entrée
//Sortie : Retourne la taille du bateau
int Bateau::getTaille()
{
    return taille;
}