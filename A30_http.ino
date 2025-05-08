#include <ESP8266HTTPClient.h>

unsigned int localPort = 4000; 

void updateHttp(){
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String serverPath = String("https://manuelselch.de/Helmut/saveData.php?tempPump="+String(tempTank)+"&tempSolar="+String(tempSolar)+"&tempSecurity="+String(tempSecurity))+"&rel="+String(rel); 
    http.begin(client, serverPath.c_str()); //HTTP -- error 302
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    String httpRequestData = "tempPump=111&dif=222";           
    //int httpCode = http.POST(httpRequestData);
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
        String s = payload;
        // myString.substring(from, to)
        s.substring(0,1);
        Serial.print("udp = ");
        Serial.println(s);
        
        String s_dif = payload;
        s_dif = s_dif.substring(2,4); // Server file has to be changed: echo "udp;dif; ... ";   example: 10, 15, 20 ... not 1 or 100 -> 2 digits
        dif = s_dif.toInt();

        handleTime(payload);
      }else{
        const String& payload = http.getString();
        Serial.println("error received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
