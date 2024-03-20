/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include "manette.h"

/*-------------------------- Librairies externes ----------------------------*/

/*------------------------------ Constantes ---------------------------------*/




/*---------------------------- Variables globales ---------------------------*/

/*----------------------------- Fonction "Main" -----------------------------*/
Manette::Manette(const std::string& port){
    std::string raw_msg;

    // Initialisation du port de communication
    std::string com;
    //cin >> com;
    this->arduino = new SerialPort("\\\\.\\COM3", BAUD);
    
    //const char com = "\\\\.\\COM3";
    //SerialPort arduino = SerialPort("\\\\.\\COM3");
    if(!arduino->isConnected()){
        std::cerr << "Impossible de se connecter au port "<< std::string(com) <<". Fermeture du programme!" <<std::endl;
        exit(1);
    }
    
    // Structure de donnees JSON pour envoie et reception
    int led_state = 1;
    json j_msg_send, parsed_received_msg;

    // Boucle pour tester la communication bidirectionnelle Arduino-PC
    for(int i=0; i<10000; i++){
        // Envoie message Arduino
        j_msg_send["led"] = led_state;
        if(!SendToSerial(j_msg_send)){
            std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
        }
        // Reception message Arduino
        parsed_received_msg.clear(); // effacer le message precedent
        if(!RcvFromSerial(raw_msg)){
            std::cerr << "Erreur lors de la reception du message. " << std::endl;
        }
        
        // Impression du message de l'Arduino si valide
        if(raw_msg.size()>0){
            //cout << "raw_msg: " << raw_msg << std::endl;  // debug
            // Transfert du message en json
            //parsed_received_msg = json::parse(raw_msg);
            std::cout << "Message de l'Arduino: " << raw_msg << std::endl;
        }
        
        //Changement de l'etat led
        led_state = !led_state;

        // Bloquer le fil pour environ 1 sec
        Sleep(10); // 1000ms
    }
}



/*---------------------------Definition de fonctions ------------------------*/
bool Manette::SendToSerial(json j_msg){
    // Return 0 if error
    std::string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


bool Manette::RcvFromSerial(std::string &msg){
    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear std::string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio
    // Version fonctionnelle dans VScode et Visual Studio
    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    //msg.pop_back(); //remove '/n' from std::string

    return true;
}