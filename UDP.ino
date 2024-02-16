#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <String.h>

const char* ssid = "Galaxy M20F290";
const char* password = "7453812345";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

int speed = 255;
char myData[255];

int leftSignalState = 1;
int rightSignalState = 1;

void setup()
{
  setupPinMode();
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop()
{
  int packetSize = Udp.parsePacket();
  //Serial.printf("%s", myData);
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    strcpy(myData, incomingPacket);

    if(strcmp(myData, "A") == 0){
      Serial.printf("Signal left \n");
      leftSignalState = !leftSignalState;
    }
    else if(strcmp(myData, "K") == 0){
      Serial.printf("Signal right \n");
      rightSignalState = !rightSignalState;
    }
    else if(strcmp(myData, "C") == 0){
      HeadLight();
    }

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.endPacket();
  }

  SignalLeft(leftSignalState);
  SignalRight(rightSignalState);

  if(strcmp(myData, "F") == 0) Forward(speed);
  else if(strcmp(myData, "B") == 0) Back(speed);
  else if(strcmp(myData, "R") == 0) rightForward(speed);
  else if(strcmp(myData, "L") == 0) leftForward(speed);
  else if(strcmp(myData, "S") == 0) Stop();
}