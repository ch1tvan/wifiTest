// Library Inclusions
#include <WiFi.h>

//    Communication Definitions
#define IPServer "192.168.1.80"
#define UDP_PORT 7394
#define NW_NAME "FCI_No_Internet_2.4"
// #define NW_NAME "FCI_No_Internet_NotExist"
#define PWD  "57381909"

// Variables used in communication
WiFiUDP _udp;
char packetBuffer[255];
char replyBuffer[255];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Setup WiFi mode
  WiFi.mode(WIFI_STA);
  delay(100);

  Serial.println("Setup Done");
}

void loop() {
  static int prevMS = 0;
  int currMS = millis()%5000;
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Wifi local IP is ");
    Serial.println(WiFi.localIP());
    if(UDP_handshake(UDP_PORT)) {
      readFromUDP();
      char replyPrefix [] = "Received: \0";
      strcpy(replyBuffer, replyPrefix);
      Serial.println(replyBuffer);
      strncat(replyBuffer,packetBuffer,255-strlen(replyPrefix));
      Serial.println(replyBuffer);
    }
    delay(1000);
  }
  else if(prevMS>currMS) {
    scan4Wifi();
    // connect2Network();
  }
  prevMS = currMS;
}
