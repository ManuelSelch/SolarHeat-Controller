#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

unsigned int localPort = 4000; 

void updateHttp(){
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClientSecure client;
    client.setInsecure(); // Accept all certificates (for self-signed HTTPS)

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String serverPath = String("https://solar-heat.manuelselch.de/temperatures"); 
    http.begin(client, serverPath.c_str()); //HTTP -- error 302
    http.addHeader("Content-Type", "application/json");

    String payload = "{";
    payload += "\"pump\":" + String(tempTank) + ",";
    payload += "\"solar\":" + String(tempSolar) + ",";
    payload += "\"security\":" + String(tempSecurity) + ",";
    payload += "\"rel\":" + String(rel);
    payload += "}";

    Serial.println("[HTTP] POST with JSON:");
    Serial.println(payload);

    // start connection and send HTTP header and body
    String httpRequestData = "tempPump=111&dif=222";           
    //int httpCode = http.POST(httpRequestData);
    int httpCode = http.POST(payload);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_CREATED) {
        const String& response = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(response);
        Serial.println(">>");

        // Allocate a JSON document 
        StaticJsonDocument<200> doc;
        DeserializationError jsonError = deserializeJson(doc, response);

        if (!jsonError) {
          int difVal = doc["dif"];
          const char* timestamp = doc["timestamp"];  // example key

          Serial.print("dif = ");
          Serial.println(difVal);

          // Use values
          dif = difVal;
          handleTime(String(timestamp));
        } else {
          Serial.print("Failed to parse JSON: ");
          Serial.println(jsonError.c_str());
        }
      } else{
        const String& response = http.getString();
        Serial.println("error invalid status, received:\n<<");
        Serial.println(response);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
