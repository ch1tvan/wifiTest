// Library Inclusions
#include <WiFi.h>

//    Communication Definitions
#define IPServer "192.168.1.150"
#define UDP_PORT 7394
#define NW_NAME "FCI_No_Internet_2.4"
// #define NW_NAME "FCI_No_Internet_NotExist"
#define PWD  "57381909"

// Variables used in communication
WiFiUDP _udp;
char packetBuffer[255];
int wifiConnectionTime = 2000, prevMS = 0;
bool wifiCon = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Setup WiFi mode
  WiFi.mode(WIFI_STA);
  delay(100);

  Serial.println("Setup Done");
}

void loop() {
  int currMS = millis() % wifiConnectionTime;
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Wifi local IP is ");
    Serial.println(WiFi.localIP());
    if(UDP_handshake()) {
      readFromUDP();
      // send2UDP();
    }
    delay(500);
  }
  else if(prevMS>currMS) {
    wifiCon = false;
    scan4Wifi();
    // connect2Network();
  }
  prevMS = currMS;
}
