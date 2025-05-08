


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void handleTime(String payload){
  String serverTime = getValue(payload,';',7); //clock: hour:min
  int splitIndex = serverTime.indexOf(':');
  String currentHour = serverTime.substring(0,splitIndex);
  String currentMin = serverTime.substring(splitIndex+1);

  Serial.print("payload: ");
  Serial.println(payload);

  Serial.print("payload time: ");
  Serial.println(serverTime);

  Serial.print("time: ");
  Serial.print(currentHour);
  Serial.print(";");
  Serial.println(currentMin);

  Serial.print("serverHour: ");
  Serial.println(serverHour);

  checkHour(currentHour, "9");
  checkHour(currentHour, "13");
  checkHour(currentHour, "15");
  checkHour(currentHour, "19");
}

void checkHour(String currentHour, String h){
  if(currentHour == h && serverHour != h){ //reboot only once per hour
    Serial.print(currentHour);
    Serial.print("==");
    Serial.println(h);
    
    serverHour = currentHour;
    reboot();
  }
}

void reboot(){
  writeToFlashMemory(); // save serverHour
  ESP.restart();
}


