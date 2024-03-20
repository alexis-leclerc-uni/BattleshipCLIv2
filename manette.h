#ifndef ARDUINO_COMMUNICATION_H
#define ARDUINO_COMMUNICATION_H

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
#include "external_libs/serial/SerialPort.hpp"
#include "external_libs/nlohmann/json.hpp"

using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 116200  // Frequency of serial transmission
#define MSG_MAX_SIZE 1024 // Maximum length of a message

class Manette {
public:
  // Constructor to initialize the serial port
  Manette(const std::string& port);

  // Function to send a JSON message to the Arduino
  bool SendToSerial(json j_msg);

  // Function to receive a message from the Arduino
  bool RcvFromSerial(std::string& msg);

private:
  SerialPort* arduino; // Serial port object
};

#endif /* ARDUINO_COMMUNICATION_H */
