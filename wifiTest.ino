// Library Inclusions
#include <WiFi.h>

//    Communication Definitions
#define IPServer "192.168.1.80"
#define UDP_PORT 7394
#define NW_NAME "FCI_No_Internet_2.4"
#define PWD  "57381909"

// Variables used in communication
WiFiUDP _udp;

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
  int currMS = millis()%1000;
  if(prevMS > currMS) {
    if(WiFi.status() != WL_CONNECTED) {
      scan4Wifi();
    }
    else {
      Serial.print("Wifi local IP is ");
      Serial.println(WiFi.localIP());
      delay(2000);
    }
  }
  prevMS = currMS;

}
