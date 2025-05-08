#include <ESP8266WiFiMulti.h> 
#include <ESP8266WiFi.h>

char ssid[] = "Manuela"; //"FRITZ!Box 7490"; //"Stefan112"; //"FRITZ!Box 7490"; //"Manuela"; 
char pass[] = "397549+23567&3406"; //"10078481327560957864"; //"LTAHDKD6ZEUM"; //"10078481327560957864"; //"397549+23567&3406";//"397549+23567&3406";  192.168.178.46 // 10078481327560957864

void setupWifi() {
  WiFi.mode(WIFI_AP_STA); // wifi mode 
  Serial.println("starting softAP");
  
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