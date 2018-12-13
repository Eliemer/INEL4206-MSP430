/*
  debugPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro,
  have one hardware debug port attached to Digital pins 0-1, and a
  separate USB debug port attached to the IDE debug Monitor.
  This means that the "debug passthrough" which is possible with
  the Arduino UNO (commonly used to interact with devices/shields that
  require configuration via debug AT commands) will not work by default.

  This sketch allows you to  emulate the debug passthrough behaviour.
  Any text you type in the IDE debug monitor will be written
  out to the debug port on Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "debug" refers to the USB debug port
  attached to the debug Monitor, and "debug" refers to the hardware
  debug port attached to pins 0 and 1. This sketch will emulate debug passthrough
  using those two debug ports on the boards mentioned above,
  but you can change these names to connect any two debug ports on a board
  that has multiple ports.

   Created 23 May 2016
   by Erik Nyquist
*/

#include <SoftwareSerial.h>
SoftwareSerial debug(7,8); // RX | TX

void setup() 
{
  debug.begin(9600);
  Serial.begin(115200);
  Serial.println("AT+IPR=9600");
  debug.write(Serial.read());
  delay(1000);
  Serial.end();
  
  // Start the software debug for communication with the ESP8266
  Serial.begin(9600);

  debug.println("Ready");
  Serial.println("AT+GMR");
}

void loop() 
{
    // listen for communication from the ESP8266 and then write it to the debug monitor
    if ( Serial.available() )   {  debug.write( Serial.read() );  }

    // listen for user input and send it to the ESP8266
    if ( debug.available() )       {  Serial.write( debug.read() );  }
}
