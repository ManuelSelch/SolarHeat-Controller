#include <OneWire.h>
#include <DallasTemperature.h>
#include "Simpletimer.h"

Simpletimer timer{};

// *** sensor data ***
int dif = 10; // Differenz 
int tempTank; // current temperature 1
int tempSolar = 0; // current temperature 2
int tempSecurity = 0; // current temperature 3
int rel;

// *** flash ***
String serverHour = "00";

void setup() {
  Serial.begin(115200);
  Serial.println("start Temperatur Control -- Pumpe");
 
  setupWifi();
  setupOTA();
  setupDisplay();
  setupFlashMemory();
  setupSensors();
  
  Serial.println("setup finish");
}

void loop() {
  updateOTA();
  updateSensors();
  updateDisplay();

  if (timer.timer(60000)) {
    updateHttp();
  }
}

