#include <SPI.h>
#include <SD.h>
uint32_t tmr1 = 0;
uint32_t tmr2 = 0;
int voltage;
int current;
File myFile;
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  float energy_mWh = 0;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");

}
void loop() {
 
    tmr1 = millis();
    tmr2++;
myFile = SD.open("test.txt", FILE_WRITE);
if (myFile) {
   shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  energy_mWh = energy_mWh + (power_mW*0.001);
  
myFile.print("Time: ");
myFile.print(tmr2);
myFile.print(" V: ");
myFile.print(busvoltage);
myFile.print(" mA: ");
myFile.print(current_mA);
myFile.print(" mW: ");
myFile.print(power_mW);
myFile.print(" mWH: ");
myFile.println(energy_mWh);

myFile.close();
Serial.print("Time: ");
Serial.print(tmr2);

Serial.print(" V: ");
Serial.print(busvoltage);
Serial.print(" mA: ");
Serial.print(current_mA);
Serial.print(" mW: ");
Serial.print(power_mW);
Serial.print(" mWH: ");
Serial.println(energy_mWh);


Serial.println("done");
}
delay(3600);
}
