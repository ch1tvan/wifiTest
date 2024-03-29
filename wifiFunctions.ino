

void scan4Wifi() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      if(WiFi.SSID(i) == NW_NAME) {
        WiFi.disconnect();
        WiFi.begin(NW_NAME,PWD);
        Serial.print("Connecting to ");
        Serial.println(WiFi.SSID(i));
        delay(1000); // Wait for connection
        return;
      }
      delay(10);
    }
  }
  Serial.println("");
}


bool UDP_handshake() {
  if(wifiCon) {
    return(wifiCon);
  }
  _udp.begin(UDP_PORT);
  // Put the handshake code here
  send2Server("Hello");
  wifiCon = true;
  return(wifiCon);
}

void readFromUDP() {
  _udp.parsePacket();
  int packetSize = _udp.read(packetBuffer, 255);
  Serial.println(packetSize);
  if (packetSize) {
    packetBuffer[packetSize] = 0;
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    // Serial.print("From ");
    // Serial.print(_udp.remoteIP());
    // Serial.print(", port ");
    // Serial.println(_udp.remotePort());
    Serial.print("Contents: ");
    Serial.println(packetBuffer);
    send2Server("Hello Back");
  }
}

void send2Server(char * str) {
  _udp.beginPacket(IPServer, UDP_PORT);
  _udp.write((uint8_t *)str,strlen(str));
  _udp.endPacket();
}
// void connect2Network() {
//   Serial.println("Trying to connect to current network");
//   WiFi.begin(NW_NAME,PWD);
//   Serial.println("Checking if connection to server possible");
//   if(WiFi.status() != WL_CONNECTED) {
//     Serial.println("Could not connect to network");
//     WiFi.disconnect();
//   }
// }
