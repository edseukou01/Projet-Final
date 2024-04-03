#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
#include "capteurs.h"
#include <Adafruit_Sensor.h>

const char *ssid = "UNIFI_IDO1";  // Nom du réseau WiFi
const char *password = "41Bidules!";  // Mot de passe du réseau WiFi
int status = WL_IDLE_STATUS; // Statut du module WiFi

WiFiServer server(80);
Capteurs capteurs(4, A0); // Exemple de broches, ajustez selon votre configuration

void setup() {
  Serial.begin(9600);
  capteurs.init();

  // Connexion au réseau WiFi
  while (status != WL_CONNECTED) { // Tant que la connexion n'est pas établie
    Serial.print("Tentative de connexion au réseau WiFi : ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password); // Tenter de se connecter au réseau avec le nom d'utilisateur et le mot de passe fournis
    delay(10000); // Attendre 10 secondes avant de réessayer
  }

  // Afficher l'adresse IP du module WiFi
  IPAddress ip = WiFi.localIP(); // Récupérer l'adresse IP locale
  Serial.print("Adresse IP : ");
  Serial.println(ip);
  
  // Démarrez le serveur web
  server.begin();
  Serial.println("Serveur demarre !");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    // Attendre les données du client
    while (client.connected() && !client.available()) {
      delay(1);
    }
    // Lire la requête
    String request = client.readStringUntil('\r');
    client.flush();
    // Envoyer la réponse
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><title>Capteurs</title>");
    client.println("<link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.15.4/css/all.css'>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background-image: url('https://www.silvertouchtech.co.uk/wp-content/uploads/2020/05/iot-banner-1568x625.jpg'); background-size: cover; }");
    client.println("h1 { color: #333; }");
    client.println("p { color: #333; }");
    client.println(".temp-icon { color: orange; }"); // Couleur orange pour l'icône de température
    client.println(".humidity-icon { color: blue; }"); // Couleur bleue pour l'icône d'humidité
    client.println(".gas-icon { color: yellow; }"); // Couleur jaune pour l'icône de gaz
    client.println(".data { display: inline-block; text-align: left; width: 200px; }"); // Alignement des données
    client.println("</style>");
    client.println("</head><body>");
    client.println("<div style='display: flex; justify-content: center; align-items: center; height: 100vh;'>");
    client.println("<div>");
    client.println("<h1>Donnees des capteurs:</h1>");
    client.println("<div class='data'>");
    client.print("<p><i class='fas fa-thermometer-half icon temp-icon'></i> Temperature: ");
    client.print(capteurs.lireTemperature());
    client.println(" °C</p>");
    client.print("<p><i class='fas fa-tint icon humidity-icon'></i> Humidite: ");
    client.print(capteurs.lireHumidite());
    client.println(" %</p>");
    client.print("<p><i class='fas fa-fire icon gas-icon'></i> Niveau de Gaz: ");
    client.print(capteurs.detecterGaz());
    client.println(" %</p>");
    client.println("</div>");
    client.println("</div>");
    client.println("</div>");
    client.println("</body></html>");

    client.stop();
    Serial.println("Client deconnecte");
  }
}