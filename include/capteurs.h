#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <Arduino.h>
#include <DHT.h>

class Capteurs {
  private:
    int pinDHT;
    int pinMQ7;

    DHT dht;

  public:
    Capteurs(int pinDHT, int pinMQ7);
    void init();
    float lireTemperature();
    float lireHumidite();
    float detecterGaz();
};

#endif 