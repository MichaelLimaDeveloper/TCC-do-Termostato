#include "Arduino.h"
#include "heltec.h"

void setup() {
  // put your setup code here, to run once:
   Heltec.begin(true, false, true);
 
   Heltec.display->setContrast(255);
   Heltec.display->clear();
    
   Heltec.display->setFont(ArialMT_Plain_24);
   Heltec.display->drawString(0, 0, "Termostato");
    
   Heltec.display->setFont(ArialMT_Plain_16);
   Heltec.display->drawString(0, 25, "Projeto Final I");
    
   Heltec.display->setFont(ArialMT_Plain_10);
   Heltec.display->drawString(0, 45, "By Gaab, Michael and Miryan :D");
   
   Heltec.display->display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
