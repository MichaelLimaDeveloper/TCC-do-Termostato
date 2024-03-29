//inclusão de bibliotecas
#include "WiFi.h"
#include "PubSubClient.h"
#include "ESPmDNS.h"
#include "heltec.h"
#include "DHTesp.h"
#define BAND    915E6  //Escolha a frequência
DHTesp dht;
String packet ;
float currentTemp;
float currentHumidity;
/* Protótipo da função */
void getTemp();
void getHumidity();
void sendPacket();
/*
  Nome da função: getTemp
  objetivo: ler a temperatura e atibiu a variável currentTemp.
*/
void getTemp()
{
  float temperature = dht.getTemperature();
 
  if (temperature != currentTemp) { //Verifica se houve mudança na temperatura
    currentTemp = temperature;
    digitalWrite(LED, HIGH);   // Liga o LED
    delay(500);                // Espera 500 milissegundos
    digitalWrite(LED, LOW);    // Desliiga o LED
    delay(500);                // Espera 500 milissegundos
  }
  delay(1000);
}
/*
  Nome da função: sendPacket
  objetivo: envia a temperatura via LoRa armazenada na variável currentTemp.
*/

void getHumidity()
{
  float humidity = dht.getHumidity();
 
  if (humidity != currentHumidity) { //Verifica se houve mudança na temperatura
    currentHumidity = humidity;
    digitalWrite(LED, HIGH);   // Liga o LED
    delay(500);                // Espera 500 milissegundos
    digitalWrite(LED, LOW);    // Desliiga o LED
    delay(500);                // Espera 500 milissegundos
  }
  delay(1000);
}

void sendPacket()
{
  LoRa.beginPacket();
  LoRa.print("Temperatura: ");
  LoRa.print(currentTemp);
  LoRa.endPacket();
}
/******************* função principal (setup) *********************/
void setup()
{
  pinMode(LED,OUTPUT); //inicializa o LED
  
  Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/, BAND /*Frequência BAND*/);
 
  Heltec.display->init();
  //Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->clear();
  Heltec.display->drawString(33, 5, "Iniciado");
  Heltec.display->drawString(10, 30, "com Sucesso!");
  Heltec.display->display();
  delay(1000);
  
  dht.setup(25, DHTesp::DHT22); //inicializa o DHT no pino 17
   
  currentTemp = dht.getTemperature();
  currentHumidity = dht.getHumidity();
}
/******************* função em loop (loop) *********************/
void loop()
{
  getTemp(); //Ler temperatura
  getHumidity();
  
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_16);
  
  Heltec.display->drawString(30, 5, "Temperatura"); //"Enviando"
  Heltec.display->drawString(33, 30, (String)currentTemp);
  Heltec.display->drawString(78, 30, "°C");
  Heltec.display->display();

  //Monitor Serial
  Serial.println("Temp: " + (String)currentTemp + "°C");
  Serial.println("Humidity: " + (String)currentHumidity + "%");
  Serial.println("---");
  
  sendPacket(); //Envia temperatura
}
