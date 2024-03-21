/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include "manette.h"


Manette::Manette(const std::string& port, concurrent_queue<std::string>* q){
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
    json j_msg_send, parsed_received_msg, old_received_msg;


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
            //std::cout << "raw_msg: " << raw_msg << std::endl;  // debug
            // Transfert du message en json
            parsed_received_msg = json::parse(raw_msg);
            for (auto it = parsed_received_msg.items().begin(); it != parsed_received_msg.items().end(); ++it) {
                std::string key = it.key();
                auto value = it.value();
                if(value != old_received_msg[key]){
                    if((key).find("Acc") && key.find("time") && key.find("pot")){
                        if(old_received_msg[key] == 0 && value == 1){
                            q->push(key);
                        }
                    }
                }

            }
            old_received_msg = parsed_received_msg;
            /*
            for(int i = 0; i <= sizeof(parsed_received_msg); i++){
                std::cout << i << std::endl;
                std::cout << parsed_received_msg[i];
            }
            */
        }
        
        //Changement de l'etat led
        led_state = !led_state;

        // Bloquer le fil pour environ 1 sec
        Sleep(35); // 1000ms
    }
}

bool Manette::try_parse_int(const std::string& str){
    try {
        std::stoi(str);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
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