#include "jeu.h"

//Description : Construit le jeu
//Entrée : rien
//Sortie : rien
Jeu::Jeu()
{
    tailleEnX = 5;
    tailleEnY = 5;
}
//Description : Construit le jeu avec queue
//Entrée : rien
//Sortie : rien
Jeu::Jeu(concurrent_queue<std::string>* queue)
{
    this->q = queue;
}
//Description : Déconstruit le jeu (déallouer la mémoire des Joueur)
//Entrée : rien
//Sortie : rien
Jeu::~Jeu()
{
    for (int i = 0; i < vecJoueur.size(); i++)
        delete vecJoueur[i];
}
//Description : Afficher le menu de démarrage (Demande s'il veut commencer et le joueur doit répondre par y/n)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherStartUp(std::ostream& sout)
{
    sout << "Bienvenue au Battleship" << std::endl;
    sout << "Continuer? Appuyer sur le bouton gauche" << std::endl;
    sout << "Appuyer sur le bouton droite pour quitter" << std::endl;
    return false;
}
//Description : Demande au joueur s'il veut commencer une partie ou quitter
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer et 1 pour Quitter
int Jeu::menuStartUp(std::ostream& sout, std::istream& sin)
{
    std::string result = "";
    while(this->q->empty()){
        Sleep(100);
    };
    result = this->q->front();
    this->q->pop();
    if (result == "bouton2")
        return CONFIRMER;
    else if (result == "bouton4")
        return QUITTER;
    else if (result.substr(0,3) == "pot"){
        valPot = std::stoi(result.substr(3,3));
        std::cout << result << std::endl;
    }
    else if (result[0] == 'N' || result[0] == 'S' || result[0] == 'E' || result[0] == 'O')
        std::cout << result << std::endl;
    return INCORRECT;
}
//Description : Afficher le menu de réglage
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherReglage(std::ostream& sout)
{
    sout << "C'est le temps des reglages" << std::endl;
    return true;
}
//Description : Afficher le menu de réglage (demande la taille en X)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTailleEnX(std::ostream& sout)
{
    sout << "Choisir la taille en X" << std::endl;
    sout << "Utiliser le Joystick ou le bouton de gauche et de droite pour sélectionner la taille en X" << std::endl;
    return true;
}
//Description : Afficher le menu de réglage (demande la taille en Y)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTailleEnY(std::ostream& sout)
{
    sout << "Choisir la taille en Y" << std::endl;
    sout << "Utiliser le Joystick ou le bouton de gauche et de droite pour sélectionner la taille en Y" << std::endl;
    return true;
}
//Description : Afficher le menu de réglage (demande la taille en Y)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherMode(std::ostream& sout)
{
    sout << "Inscrivez le mode de jeu choisi :" << std::endl;
    sout << "Bouton gauche : Mode normal" << std::endl;
    sout << "Bouton haut : Mode rafale" << std::endl;
    sout << "Bouton droite : Mode stratégique" << std::endl;
    return true;
}
//Description : Demande au joueur la taille de la carte
//Entrée : un canal de communication
//Sortie : Renvoie CONFIRMER (0)
int Jeu::menuReglage(std::ostream& sout, std::istream& sin)
{
    afficherReglage(sout);
    afficherMode(sout);
    std::string result = "";
    
    /*  Bouton de gauche = mode normal
        Bouton de droite = mode strategie
        Bouton de haut = mode rafale
    */
    std::string result = "";
    while(this->q->empty()){
        Sleep(50);
    };
    result = this->q->front();
    this->q->pop();
    if (result == "bouton2")
        mode = MODE_NORMAL;
    else if (result == "bouton4")
        mode = MODE_STRATEGIE;
    else if (result == "bouton1")
        mode = MODE_RAFALE;
    else if (result.substr(0,3) == "pot"){
        valPot = std::stoi(result.substr(3,3));
        std::cout << result << std::endl;
    }

    afficherTailleEnX(sout);
    do {
        
        /*  Bouton de gauche, Joystick O SO S = baisse la taille
            Bouton de droite, Joystick N NE E = augmente la taille
            Bouton de haut = confirmer
        */
        
        while(this->q->empty()){ //Attente du joueur
            Sleep(50);
        };
        result = this->q->front();
        this->q->pop();
        if (result == "bouton2"){
            if (tailleEnX > MIN_X){
                --tailleEnX;
            }
        }
        else if (result == "bouton4"){
            if (tailleEnX < MAX_X){
                ++tailleEnX;
            }
        }
        else if (result == "N"){
            if (tailleEnX < MAX_X){
                ++tailleEnX;
            }
        }
        else if (result == "NE"){
            if (tailleEnX < MAX_X){
                ++tailleEnX;
            }
        }
        else if (result == "E"){
            if (tailleEnX < MAX_X){
                ++tailleEnX;
            }
        }
        else if (result == "S"){
            if (tailleEnX > MIN_X){
                --tailleEnX;
            }
        }
        else if (result == "SO"){
            if (tailleEnX > MIN_X){
                --tailleEnX;
            }
        }
        else if (result == "O"){
            if (tailleEnX > MIN_X){
                --tailleEnX;
            }
        }  
        else if (result.substr(0,3) == "pot"){
            valPot = std::stoi(result.substr(3,3));
        }
        sout << "taille en X : " << tailleEnY << std::endl;
    } while (result != "bouton1");
    afficherTailleEnY(sout);
    do {
        /*  Bouton de gauche, Joystick O SO S = baisse la taille
            Bouton de droite, Joystick N NE E = augmente la taille
            Bouton de haut = confirmer
        */
        
        while(this->q->empty()){ //Attente du joueur
            Sleep(50);
        };
        result = this->q->front();
        this->q->pop();
        if (result == "bouton2"){
            if (tailleEnY > MIN_Y){
                --tailleEnY;
            }
        }
        else if (result == "bouton4"){
            if (tailleEnY < MAX_Y){
                ++tailleEnY;
            }
        }
        else if (result == "N"){
            if (tailleEnY < MAX_Y){
                ++tailleEnY;
            }
        }
        else if (result == "NE"){
            if (tailleEnY < MAX_Y){
                ++tailleEnY;
            }
        }
        else if (result == "E"){
            if (tailleEnY < MAX_Y){
                ++tailleEnY;
            }
        }
        else if (result == "S"){
            if (tailleEnY > MAX_Y){
                --tailleEnY;
            }
        }
        else if (result == "SO"){
            if (tailleEnY > MIN_Y){
                --tailleEnY;
            }
        }
        else if (result == "O"){
            if (tailleEnY > MIN_Y){
                --tailleEnY;
            }
        }  
        else if (result.substr(0,3) == "pot"){
            valPot = std::stoi(result.substr(3,3));
        }
        sout << "taille en Y : " << tailleEnY << std::endl;
    } while (result == "bouton1");
    

    return CONFIRMER;
}
//Description : Afficher le menu pour que le joueur initialise ses bateaux
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherInitJoueur(std::ostream& sout, Joueur *joueur)
{
    sout << "Il faut placer les bateaux" << std::endl;
    return false;
}
//Description : Indique la taille du bateau
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherInitTaille(std::ostream& sout, Joueur *joueur, int taille)
{
    sout << "La taille est de " << taille << ". Placer le bateau avec le joystick." << std::endl;
    sout << "Utiliser le bouton bas pour changer la direction du bateau" << std::endl;
    return false;
}
//Description : Le joueur installe ses bateaux
//Entrée : un canal de communication et la taille du bateau
//Sortie : 0 pour Confirmer, 1 pour revenir en arrière
int Jeu::menuInitJoueur(std::ostream& sout, std::istream& sin,Joueur* joueur)
{
    afficherInitJoueur(sout, joueur);
    int tailleBateau[] = {5,4,3,3,2};
    int x = 0; int y = 0;
    bool horizontal = true;
    std::string result;
    for (int i = 0; i < 5; i++)
    {
        do {
            //Joystick contrôle la position
            //Le bouton bas contrôle la direction
            sautDePage(sout);
            afficherInitTaille(sout, joueur, tailleBateau[i]);
            joueur->afficherCartePreparation(sout, {x, y}, horizontal, tailleBateau[i]);
            
            while(this->q->empty()){ //Attente du joueur
                Sleep(50);
            };
            result = this->q->front();
            this->q->pop();
            if (result == "bouton3"){
                horizontal = !horizontal;
            }
            else if (result == "N"){
                y++;
            }
            else if (result == "NE"){
                y++; x++;
            }
            else if (result == "E"){
                x++;
            }
            else if (result == "SE"){
                y--; x++;
            }
            else if (result == "S"){
                y--;
            }
            else if (result == "SO"){
                x--; y--;
            }
            else if (result == "O"){
                x--;
            }
            else if (result == "NO"){
                x--; y++;
            }
            else if (result.substr(0,3) == "pot"){
                valPot = std::stoi(result.substr(3,3));
            }

        } while (!joueur->ajouterBateau(x,y,horizontal,tailleBateau[i]));
        
    }
    return CONFIRMER;
}
//Description : le jeu en mode normal
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer 
int Jeu::menuJeuNormal(std::ostream& sout, std::istream& sin)
{
    //On a droit a tous les types de missile au début (à pars la bombe), Une action à la fois
    for (int i = 0; i < 2; i++)
    {
        bool* type = vecJoueur[i]->getTypeAccepte();
        type[4] = false;
    }
    while (!vecJoueur[0]->aPerdu())
    {
        menuTir(sout, sin, vecJoueur[0], vecJoueur[1]);
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(0), jeu.getJoueur(1));
        if (vecJoueur[1]->aPerdu())
            break;
        menuTir(sout, sin, vecJoueur[1], vecJoueur[0]);
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(1), jeu.getJoueur(0));
    }
    return CONFIRMER;
}
//Description : le jeu en mode rafale
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer 
int Jeu::menuJeuRafale(std::ostream& sout, std::istream& sin)
{
    //On a droit seulement au missile normal, mais on en a plus au fil du jeu
    for (int i = 0; i < 2; i++)
    {
        bool* type = vecJoueur[i]->getTypeAccepte();
        type[1] = false; type[2] = false; type[3] = false; type[4] = false;
    }
    while (!vecJoueur[0]->aPerdu())
    {
        for (int i = 0; i < 6 - vecJoueur[0]->nBateau(); i++)
            menuTir(sout, sin, vecJoueur[0], vecJoueur[1]);
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(0), jeu.getJoueur(1));
            if (vecJoueur[1]->aPerdu())
                break;
        for (int i = 0; i < 6 - vecJoueur[1]->nBateau(); i++)
            menuTir(sout, sin, vecJoueur[1], vecJoueur[0]);
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(1), jeu.getJoueur(0));<
            if (vecJoueur[0]->aPerdu())
                break;
    }
    return CONFIRMER;
}
//Description : le jeu en mode rafale
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer 
int Jeu::menuJeuStrategique(std::ostream& sout, std::istream& sin)
{
    //Les missiles se débloquent et se perd au fur et à mesur du jeu
    /* Quand on a 5 bateau :
    *   - missile colonne/ligne (prend 3 tour pour charger) (longueur de 5 cases max)
    *   - missile normal
    *   - missile sonde
    *  Quand on perd le bateau à 5 case :
    *   - Perte du missile sonde pour le jeu
    *  Quand il nous reste 2 bateau :
    *   - missile bombe (3 tours pour charger)
    *  Quand il reste 1 bateau :
    *   - missile bombe (2 tours pour charger)
    *   - missile colonne/ligne (2 tours pour charger)
    
    */
    for (int i = 0; i < 2; i++)
    {
        bool* type = vecJoueur[i]->getTypeAccepte();
        type[4] = false;
    }
    while (!vecJoueur[0]->aPerdu())
    {        
        menuTir(sout, sin, vecJoueur[0], vecJoueur[1]);
        if (vecJoueur[0]->nBateau() == 2)
            vecJoueur[0]->getTypeAccepte()[4] = true;
        
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(0), jeu.getJoueur(1));
        if (vecJoueur[1]->aPerdu())
            break;
        menuTir(sout, sin, vecJoueur[1], vecJoueur[0]);
        if (vecJoueur[1]->nBateau() == 2)
            vecJoueur[1]->getTypeAccepte()[4] = true;
        //jeu.menuTir(std::cout, std::cin, jeu.getJoueur(1), jeu.getJoueur(0));
    }
    return CONFIRMER;
}
//Description : Afficher le menu pour que le joueur tir sur l'adversaire
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTir1(std::ostream& sout, Joueur *joueur, Joueur *adversaire)
{
    adversaire->afficherHistoriqueTir(sout);
    if (vecJoueur[0] == joueur)
        sout << "Joueur 1 : " << std::endl;
    else
        sout << "Joueur 2 : " << std::endl;
    sout << "Choix de missile :" << std::endl;
    bool* type = joueur->getTypeAccepte();
    if (type[0])
        sout << "1 : Missile normal (1 case) (prend 1 tour)" << std::endl;
    if (type[1])
        sout << "2 : Sonde géographique (5 cases en losange) (prend 1 tour) (ne cause pas de dommage)" << std::endl;
    if (type[2])
        sout << "3 : Missile ligne (5 cases en ligne droite HORIZONTALE) (prend 3 tour)" << std::endl;
    if (type[3])
        sout << "4 : Missile colonne (5 cases en ligne droite VERTICALE) (prend 3 tour)" << std::endl;
    if (type[4])
        sout << "5 : Missile Bombe (5 cases en losange) (prend 3 tour)" << std::endl;
    sout << "Choissisez le type de missile : ";
    return true;
}
//Description : Afficher le menu pour que le joueur tir sur l'adversaire
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTir2(std::ostream& sout, Joueur* joueur, Joueur* adversaire)
{
    sout << "Rentrer la position de votre missile (x y) : ";
    return true;
}
//Description : Le joueur tir sur son adversaire
//Entrée : un canal de communication
//Sortie : 0 si tout va bien
int Jeu::menuTir(std::ostream& sout, std::istream& sin,Joueur* joueur, Joueur* adversaire)
{
    Coordonnee cord = {-1,-1};
    int reponse = 0;
    do {
        if (joueur->getChargement() > 0)
        {
            joueur->setChargement(joueur->getChargement() - 1);
            if (joueur->getChargement() == 0) //Fin du chargement
            {
                cord = joueur->getCordAttente();
                switch (joueur->getTypeMissile())
                {
                case M_LIGNE:
                    //En ligne HORIZONTALE
                    for (int i = 0; i < 5; i++)
                    {
                        joueur->tirer(cord, adversaire);
                        ++cord.x;
                    }
                    break;
                case M_COLONNE:
                    //En ligne VERTICALE
                    for (int i = 0; i < 5; i++)
                    {
                        joueur->tirer(cord, adversaire);
                        ++cord.y;
                    }
                    break;
                case M_BOMBE:
                    // En losange
                    joueur->tirer(cord, adversaire);
                    --cord.x;
                    joueur->tirer(cord, adversaire);
                    ++cord.x; --cord.y;
                    joueur->tirer(cord, adversaire);
                    ++cord.x; ++cord.y;
                    joueur->tirer(cord, adversaire);
                    --cord.x; ++cord.y;
                    joueur->tirer(cord, adversaire);
                    break;
                    
                }
                break;
            }
            break;

        }
        //Déterminer le type de Missile
        int type;
        do {
            afficherTir1(sout, joueur, adversaire);
            sin >> type;
        } while (!joueur->setTypeMissile(type));
        afficherTir2(sout, joueur, adversaire);
        sin >> cord.x >> cord.y;
        switch (type)
        {
        case M_NORMAL:
            //Tire normal
            reponse = joueur->tirer(cord, adversaire);
            break;

        case M_SONDE:
            
            //La sonde géographique
            joueur->sonder(cord, adversaire);
            --cord.x;
            joueur->sonder(cord, adversaire);
            ++cord.x; --cord.y;
            joueur->sonder(cord, adversaire);
            ++cord.x; ++cord.y;
            joueur->sonder(cord, adversaire);
            --cord.x; ++cord.y;
            joueur->sonder(cord, adversaire);
            break;
        case M_LIGNE:
        case M_COLONNE:
        case M_BOMBE:
            if (joueur->nBateau() >= 2)
                joueur->setChargement(3);
            else
                joueur->setChargement(2);
            joueur->setCordAttente(cord);
            break;
        }
        
    } while (reponse == 1 || reponse == 2);
    return false;
}
//Description : Afficher le menu de fin
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherFin(std::ostream& sout)
{
    if (vecJoueur[1]->aPerdu())
        sout << "Le joueur 1 a gagné!!! ";
    else
        sout << "Le joueur 2 a gagné!!! ";
    sout << "Bravo, c'est la fin. Voulez-vous recommencer?" << std::endl;
    sout << "Appuyer sur le bouton haut pour recommancer" << std::endl;
    sout << "Appuyer sur le bouton bas pour quitter" << std::endl;
    return false;
}
//Description : Demande au joueur s'il veut continuer
//Entrée : un canal de communication
//Sortie : 0 si on recommence, 1 si on quitte
int Jeu::menuFin(std::ostream& sout, std::istream& sin)
{
    
    std::string result;
    while(this->q->empty()){ //Attente du joueur
        Sleep(50);
    };
    result = this->q->front();
    this->q->pop();
    if (result == "bouton1"){
        return CONFIRMER;
    }
    else if (result == "bouton3")
    {
        return QUITTER;
    }
    return INCORRECT;
}
//Description : Ajoute un joueur au vector
//Entrée : rien
//Sortie : rien
void Jeu::ajouterJoueur()
{
    vecJoueur.push_back(new Joueur(tailleEnX,tailleEnY));
    return;
}
//Description : renvoie le joueur sélectionné
//Entrée : rien
//Sortie : le pointeur du joueur sélectionné
Joueur* Jeu::getJoueur(int index)
{
    return vecJoueur[index];
}

int Jeu::getMode()
{
    return mode;
}
void Jeu::sautDePage(std::ostream& sout)
{
    sout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}