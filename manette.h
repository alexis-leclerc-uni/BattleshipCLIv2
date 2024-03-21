#ifndef ARDUINO_COMMUNICATION_H
#define ARDUINO_COMMUNICATION_H

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
#include "external_libs/concurrent_queue.hpp"
#include "external_libs/serial/SerialPort.hpp"
#include "external_libs/nlohmann/json.hpp"

using json = nlohmann::json;
using lime62::concurrent_queue;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200  // Frequency of serial transmission
#define MSG_MAX_SIZE 1024 // Maximum length of a message

class Manette {
public:
  // Constructor to initialize the serial port
  Manette(const std::string& port, concurrent_queue<std::string>* q);

  // Function to send a JSON message to the Arduino
  bool SendToSerial(json j_msg);

  // Function to receive a message from the Arduino
  bool RcvFromSerial(std::string& msg);

  bool try_parse_int(const std::string& str);

private:
  SerialPort* arduino; // Serial port object
};

#endif /* ARDUINO_COMMUNICATION_H */
