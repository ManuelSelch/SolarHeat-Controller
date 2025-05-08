#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#define ONE_WIRE_BUS D5
#define TEMPERATURE_PRECISION 9 // Lower resolution

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices; // Number of temperature devices found
DeviceAddress sensorPump, sensorSolar, sensorSecurity;

// ***** pins *****
int relay = D8; // relay pin for pump
int sensorPumpPin = D7; //pin to enable pump sensor
int sensorSolarPin = D6; //pin to enable pump sensor
int sensorSecurityPin = D4; //pin to enable security sensor
int sda = D2;
int scl = D1;
// ***** end pins *****

void setupSensors(){
  Wire.begin(sda, scl); // set Data & Clock (SDA,SCL)

  pinMode(relay, OUTPUT);
  pinMode(sensorPumpPin, OUTPUT);
  pinMode(sensorSolarPin, OUTPUT);
  pinMode(sensorSecurityPin, OUTPUT);
  digitalWrite(sensorPumpPin, HIGH); //enable pump sensor
  digitalWrite(sensorSolarPin, HIGH); //enable solar sensor
  digitalWrite(sensorSecurityPin, HIGH); //enable security sensor
  
  sensors.begin();

  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  
  if (!sensors.getAddress(sensorPump, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(sensorSolar, 1)) Serial.println("Unable to find address for Device 1");
  if (!sensors.getAddress(sensorSecurity, 2)) Serial.println("Unable to find address for Device 1");

  sensors.setResolution(sensorPump, TEMPERATURE_PRECISION);
  sensors.setResolution(sensorSolar, TEMPERATURE_PRECISION);
  sensors.setResolution(sensorSecurity, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(sensorPump), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(sensorSolar), DEC);
  Serial.println();
  
}



void updateSensors(){
  tempTank = getSensorTemp(sensorPump);
  tempSolar = getSensorTemp(sensorSolar);
  tempSecurity = getSensorTemp(sensorSecurity);

  if(tempTank != 0 and tempSolar != 0){
    if(tempSolar-tempTank >= dif){
      Serial.println("enable tank!");
      digitalWrite(relay, HIGH);
      rel = 1;
    }else if(tempSolar-tempTank+2 <= dif){
      digitalWrite(relay, LOW);
      rel = 0;
    }
  }else{
    digitalWrite(relay, LOW);
    rel = 0;
  }
}

String get_temp(){
  String str = String("t:")+tempTank+";"+tempSolar+";"+dif+";"+tempSecurity;
  return str;
}

int getSensorTemp(DeviceAddress deviceAddress) 
{
  sensors.requestTemperatures();
  delay(500);
  
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return 0;
  }
  Serial.print("Temp C: ");
  Serial.println(tempC);
  return tempC;
}