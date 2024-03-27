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
            //std::cout << raw_msg << std::endl;
            try
            {
                parsed_received_msg = json::parse(raw_msg);
            }
            catch(...){}
            for (auto it = parsed_received_msg.items().begin(); it != parsed_received_msg.items().end(); ++it) {
                std::string key = it.key();
                auto value = it.value();
                if(value != old_received_msg[key]){
                    if((key).find("AccX") && (key).find("AccY") && (key).find("AccZ") && key.find("time") && key.find("pot") && key.find("JoyX") && key.find("JoyY")){
                        if(old_received_msg[key] == 0 && value == 1){
                            q->push(key);
                        }
                    }
                }
            }
            if (old_received_msg["pot"] != nullptr)
            {
                try {
                    int new_pot = parsed_received_msg["pot"].get<int>();
                    int old_pot = old_received_msg["pot"].get<int>();

                    //Voie les changements pour le pot
                    //std::cout << new_pot << std::endl;
                    if (new_pot + 15 < old_pot || new_pot - 15 > old_pot) {
                        if (new_pot < 100)
                            q->push("pot0" + std::to_string(new_pot));
                        else
                            q->push("pot" + std::to_string(new_pot));
                    }
                } catch (...){}
            }
            //Voie si il y a eu un changement pour le joystick
            if (old_received_msg["JoyX"] != nullptr)
            {
                std::string old_joystick = "";
                std::string new_joystick = "";
                if (old_received_msg["JoyY"] <= 150) {
                    old_joystick += "S";
                } else if (old_received_msg["JoyY"] >= 900) {
                    old_joystick += "N";
                }
                if (old_received_msg["JoyX"] <= 150) {
                    old_joystick += "E";
                } else if (old_received_msg["JoyX"] >= 900) {
                    old_joystick += "O";
                }

                if (parsed_received_msg["JoyY"] <= 150) {
                    new_joystick += "S";
                } else if (parsed_received_msg["JoyY"] >= 900) {
                    new_joystick += "N";
                }
                if (parsed_received_msg["JoyX"] <= 150) {
                    new_joystick += "E";
                } else if (parsed_received_msg["JoyX"] >= 900) {
                    new_joystick += "O";
                }

                if (old_joystick != new_joystick && new_joystick != "")
                {
                    q->push(new_joystick);
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
        Sleep(40); // 1000ms
    }
}

bool Manette::try_parse_int(const std::string& str)
{
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