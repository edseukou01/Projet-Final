#include "capteurs.h"

Capteurs::Capteurs(int pinDHT, int pinMQ7) : dht(pinDHT, DHT22) {
  this->pinDHT = pinDHT;
  this->pinMQ7 = pinMQ7;
}

void Capteurs::init() {
  pinMode(pinMQ7, INPUT);
  dht.begin();
}

float Capteurs::lireTemperature() {
  return dht.readTemperature();
}

float Capteurs::lireHumidite() {
  return dht.readHumidity();
}

float Capteurs::detecterGaz() {
  // Lire la valeur du capteur de gaz MQ7
  int valeurMQ7 = analogRead(pinMQ7);
  
  // Convertir la valeur en pourcentage de gaz
  // Vous devez ajuster ces valeurs en fonction de votre capteur
  float pourcentageGaz = map(valeurMQ7, 0, 1023, 0, 100);

  return pourcentageGaz;
}