#include "Carte.h"
//Description : Constructeur de Carte. Créer une carte 2D d'une taille choisie
//Entrée : La taille en X et en Y est en entier (int)
//Sortie : Ne retourne rien
Carte::Carte(int tailleEnX1, int tailleEnY1)
{
    tailleEnX = tailleEnX1;
    tailleEnY = tailleEnY1;
    tableau = new int* [tailleEnX];
    for (int x = 0; x < tailleEnX; x++)
    {
        tableau[x] = new int[tailleEnY];
        for (int y = 0; y < tailleEnY; y++)
            tableau[x][y] = 0;
    }
    nbBateau = 0;
}
//Description : Déconstructeur de Carte. supprime le tableau aloué dynamiquement
//Entrée : Aucune entrée
//Sortie : Aucune Sortie
Carte::~Carte()
{
    for (int i = 0; i < tailleEnX; i++)
    {
        delete[] tableau[i];
    }
    delete[] tableau;
}
//Description : Ajoute les bateaux sur la carte (Système numérique)
//Entrée : Aucune entrée
//Sortie : Retourne vrai si l'opération réussie
bool Carte::initialiserBateau(std::vector<Bateau*> bateau)
{
    for (int i = nbBateau; i < bateau.size(); i++)
    {
        for (int j = 0; j < bateau[i]->getTaille(); j++)
        {
            if (bateau[i]->getOrientation()) //On retranscrit le bateau sur la carte (Carte ne le sait pas => donné brut sans objet)
            {
                tableau[bateau[i]->getCoordonnee().x + j][bateau[i]->getCoordonnee().y] = i + 4;
            }
            else {
                tableau[bateau[i]->getCoordonnee().x][bateau[i]->getCoordonnee().y + j] = i + 4;
            }
        }
    }
    nbBateau = bateau.size();
    return true;
}
//Description : Retourne la taille en Y de la carte
//Entrée : Aucune entrée
//Sortie : Retourne la taille en Y de la carte
int Carte::tirer(Coordonnee position)
{
    if (position.x < 0 || position.x >= tailleEnX || position.y < 0 || position.y >= tailleEnY)
        return OUTOFBOUND;

    if (dejaTirer(position))
        return DEJATIRER;

    int etatCase = tableau[position.x][position.y];
    if (etatCase == MISS)
    {
        tableau[position.x][position.y] = RIEN;
        return MISS; //renvoie un MISS
    }
    tableau[position.x][position.y] = TOUCHEE;
    return etatCase; //renvoie un HIT avec l'index du bateau + 4
}
//Description : Retourne la taille en Y de la carte
//Entrée : Aucune entrée
//Sortie : Retourne la taille en Y de la carte
int Carte::sonder(Coordonnee position)
{
    if (position.x < 0 || position.x >= tailleEnX || position.y < 0 || position.y >= tailleEnY)
        return OUTOFBOUND;

    if (dejaTirer(position))
        return DEJATIRER;

    int etatCase = tableau[position.x][position.y];
    if (etatCase == MISS)
    {
        tableau[position.x][position.y] = RIEN;
        return MISS; //renvoie un MISS
    }
    tableau[position.x][position.y] = SONDEE;
    return etatCase; //renvoie un HIT avec l'index du bateau + 4
}
//Description : Vérifie si le tire a déjà été fait
//Entrée : Prend la position du tir
//Sortie : Retourne Vrai si c'est déjà tirer, sinon faux
bool Carte::dejaTirer(Coordonnee position)
{
    return (tableau[position.x][position.y] == 1 || tableau[position.x][position.y] == 2);
}
//Description : Retourne la taille en x de la carte
//Entrée : Aucune entrée
//Sortie : Retourne la taille en X de la carte
int Carte::getTailleEnX()
{
    return tailleEnX;
}
//Description : Retourne la taille en Y de la carte
//Entrée : Aucune entrée
//Sortie : Retourne la taille en Y de la carte
int Carte::getTailleEnY()
{
    return tailleEnY;
}
//Description : Affiche la carte à l'écran
//Entrée : Aucune entrée
//Sortie : Retourne vrai si l'opération à réussie
bool Carte::afficher()
{
    return false;
}

int Carte::getPositionTableau(int y, int x) {
    if (y <= tailleEnY && x <=tailleEnX)
    {
        return tableau[x][y];
    }
    return 0;
}