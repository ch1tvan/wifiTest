bool wifiCon = false;

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
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
      if(WiFi.SSID(i) == NW_NAME) {
        WiFi.disconnect();
        WiFi.begin(NW_NAME,PWD);
        Serial.print("Connecting to ");
        Serial.println(WiFi.SSID(i));
        delay(5000); // Wait for connection
      }
    }
    // WiFi.begin(NW_NAME,PWD);
    // connect2Network();
  }
  Serial.println("");

  // Wait a bit before scanning again
  // delay(5000);
}


bool UDP_handshake(int localPort) {
  if(wifiCon) {
    return(wifiCon);
  }
  _udp.begin(localPort);
  // Put the handshake code here
  return(true);
}

void readFromUDP() {
  int packetSize = _udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    Serial.print(_udp.remoteIP());
    Serial.print(", port ");
    Serial.println(_udp.remotePort());
    int len = _udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
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