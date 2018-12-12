#include <SoftwareSerial.h>
#define pushButton P1_7


SoftwareSerial ESP(P1_3, P1_4); // RX, TX
char str[40];

void connect_wifi(char *cmd, char *res, int t)
{
  while (1)
  {
    str[0] = '\0';
    ESP.println(cmd);
    Serial.print("-->");
    Serial.println(cmd);
    Serial.print("<--");
    delay(t);
    serialEvent1();
    Serial.println(str);
   
    if (strstr(str, res))
      return;
      
    delay(1000);
  }
}

void setup()
{
  ESP.begin(9600);
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  delay(2000);
  
  connect_wifi("AT", "OK", 1000);
  connect_wifi("ATE0", "OK", 1000);
  connect_wifi("AT+CWMODE=3", "OK", 1000);
  connect_wifi("AT+CWQAP", "OK", 1000);

  Serial.println("Connecting Wifi....");
  connect_wifi("AT+CWJAP=\"Eliemer_Desktop\",\"password\"","OK", 7000);
  Serial.println("Wifi Connected");
  ESP.println("AT+CIFSR");
  delay(5000);

}

void loop()
{

  if(!digitalRead(pushButton))
  {
    ESP.println("AT+CIPMUX=1");
    delay(1000);
    
    ESP.println("AT+CIPSERVER=1,80");
    delay(2000);
    
    ESP.println("AT+CIPSTART=4,\"TCP\",\"mail.smtp2go.com\",2525");
    delay(2000);
    
    ESP.println("AT+CIPSEND=4,180");
    delay(2000);
    
    ESP.println("EHLO 192.168.1.123");
    
    ESP.println("AUTH LOGIN");
    ESP.println("YXJuYWxkby5jb2xvbjVAdXByLmVkdQ=="); // email address in base 64 format
    ESP.println("TXIuUG9zdG1hbg=="); // password in base 64 format
    
    ESP.println("MAIL FROM:<arnaldo.colon5@upr.edu>");
    ESP.println("RCPT To:<eliemer.velez@upr.edu>");
    
    ESP.println("DATA");
    // ESP.println("Testing Success saddam.");
    ESP.println("Package has arrived");
    ESP.println(".");
    delay(2000);
    
    ESP.println("AT+CIPSEND=6");
    delay(1000);
    
    ESP.println("QUIT");
    delay(10000);
  }
  
}

void serialEvent1()
{
  int ln=ESP.available();
  if(ln>0)
  {
    for(int i=0;i<ln;i++)
    {
      char ch=ESP.read();
      str[i]=ch;
      Serial.print(ch);
      delay(1);
      
    }
  }
}
