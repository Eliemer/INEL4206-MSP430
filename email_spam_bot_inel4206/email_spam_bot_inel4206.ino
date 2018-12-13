#include <SoftwareSerial.h>
#define pushButton P1_7


SoftwareSerial debug(P1_5, P2_0); // RX, TX
char str[40];
int i = 0;

void connect_wifi(char *cmd, char *res, int t)
{
  while (1)
  {
    for (i = 0; i< 40; i++){
      str[i] = NULL;
    }
    Serial.println(cmd);
    debug.print("-->");
    debug.println(cmd);
    debug.print("<--");
    delay(t);
    debugEvent1();
    debug.println(str);
   
    if (strstr(str, res))
      return;
      
    delay(1000);
  }
}

void setup()
{
  Serial.begin(74880);
  debug.begin(9600);
  pinMode(pushButton, INPUT);
  delay(2000);

  //connect_wifi("AT+CIOBAUD=57600", "OK", 1000);
  //connect_wifi("AT+RST", "OK", 1000);
  connect_wifi("AT", "OK", 1000);
  connect_wifi("ATE0", "OK", 1000);
  connect_wifi("AT+CWMODE=3", "OK", 1000);
  connect_wifi("AT+CWQAP", "OK", 1000);

  debug.println("Connecting Wifi....");
  connect_wifi("AT+CWJAP=\"Eliemer_Desktop\",\"password\"","OK", 7000);
  debug.println("Wifi Connected");
  Serial.println("AT+CIFSR");
  delay(5000);

}

void loop()
{

  if(!digitalRead(pushButton))
  {
    Serial.println("AT+CIPMUX=1");
    delay(1000);
    
    Serial.println("AT+CIPSERVER=1,80");
    delay(2000);
    
    Serial.println("AT+CIPSTART=4,\"TCP\",\"mail.smtp2go.com\",2525");
    delay(2000);
    
    Serial.println("AT+CIPSEND=4,180");
    delay(2000);
    
    Serial.println("EHLO 192.168.1.123");
    
    Serial.println("AUTH LOGIN");
    Serial.println("YXJuYWxkby5jb2xvbjVAdXByLmVkdQ=="); // email address in base 64 format
    Serial.println("TXIuUG9zdG1hbg=="); // password in base 64 format
    
    Serial.println("MAIL FROM:<arnaldo.colon5@upr.edu>");
    Serial.println("RCPT To:<eliemer.velez@upr.edu>");
    
    Serial.println("DATA");
    // Serial.println("Testing Success saddam.");
    Serial.println("Package has arrived");
    Serial.println(".");
    delay(2000);
    
    Serial.println("AT+CIPSEND=6");
    delay(1000);
    
    Serial.println("QUIT");
    delay(10000);
  }
  
}

void debugEvent1()
{
  int ln=Serial.available();
  if(ln>0)
  {
    for(int i=0;i<ln;i++)
    {
      char ch=Serial.read();
      str[i]=ch;
      delay(1);
      
    }
    debug.println(str);
  }
}
