#include <EEPROM.h>

char separator = '_';
int nextIndex = 0;

void setupFlashMemory(){
  EEPROM.begin(512);
  readFromFlashMemory();
}

void writeToFlashMemory() {
  delay(10);
  
  Serial.print("writeToFlash: ");
  printFlashMemoryData();
  
  nextIndex = 0;
  EEPROM.write(nextIndex, separator);
  nextIndex ++;
  
  writeAtNextIndex(serverHour);
  
  //result: "-<serverHour>"
  EEPROM.commit();
}

void writeAtNextIndex(String s){
  for (int i = 0; i < s.length(); i++) {
    EEPROM.write(nextIndex+i, s[i]);
  }
  nextIndex += s.length();
  EEPROM.write(nextIndex, separator);
  nextIndex ++;
}

void readFromFlashMemory(){
  Serial.print("readFromFlash: ");

  if(char(EEPROM.read(0)) != separator){ //check first char
    Serial.println("nothing stored yet");
    return;
  }

  nextIndex = 1; //skip first char '-'
  
  serverHour = readAddNextIndex();

  printFlashMemoryData();
}


String readAddNextIndex(){
  String output;
  char readChar;
  int i = 0; 
  while (readChar != separator) {
    readChar = char(EEPROM.read(nextIndex+i));
    delay(10);
    i++;

    if (readChar != separator) {
      output += readChar;
    }
  }
  nextIndex += i;
  return output;
}

void printFlashMemoryData(){
  Serial.print("stored serverHour:");
  Serial.println(serverHour);
}
