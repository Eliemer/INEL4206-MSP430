#include <SoftwareSerial.h>

SoftwareSerial debug(P1_5, P2_0); // RX, TX

void setup()
{
  debug.begin(9600);
  Serial.begin(9600);
}
 
void loop()
{
  while(debug.available()>0)
    Serial.write(debug.read());
  while(Serial.available()>0){
    debug.write(Serial.read());
  }
}
