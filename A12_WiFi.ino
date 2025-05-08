#include <ESP8266WiFiMulti.h> 
#include <ESP8266WiFi.h>

char ssid[] = "FRITZ!Box 7490";  // "Desigual19"; 
char pass[] = "10078481327560957864";  // "1409192034965811296634"; 

void setupWifi() {
  WiFi.mode(WIFI_AP_STA); // wifi mode 
  Serial.println("connecting...");
  
  bool result = WiFi.begin(ssid, pass); //WiFi.softAP(ssid, pass);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!"); 
  IPAddress myIP = WiFi.localIP();
  Serial.print("IP address: ");
  Serial.println(myIP);
  Serial.println(result);
}