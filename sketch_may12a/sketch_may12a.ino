#include <LiquidCrystal_I2C.h>    //incluir librería de la pantalla
LiquidCrystal_I2C lcd(0x27,16,2); 


#include <DHT.h>



#define DHTPIN 2
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

uint32_t tmr1;
uint32_t tmr2;
uint32_t tmr3;
uint32_t tmr4;
uint32_t tmr5;

int temperature;
int humidity;
String rain;
float power;
int battery;
int filled;

#define CLK 10              
#define DT 9
#define SW 8
#include "GyverEncoder.h"         //declarar variables para el encoder
#include "TimerOne.h"
Encoder enc1(CLK, DT, SW);  

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;




#define rain_sensor 5             //pin para sensor de lluvia

#define moisture_limit 400        //empezar a regar en este nivel de humedad




#define r1 2                      //declarar pines para los reles
#define r2 3
#define r3 4
#define r4 5


int val_1;                       //valores para los sensores
int val_2;
int val_3;
int val_4;


int s1;                         //valores para los sensores de humedad de tierra
int s2;
int s3;
int s4;

int temp;
int hum;

int page = 1;

void setup() {
  // declaración de reles
pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
pinMode(r3, OUTPUT);
pinMode(r4, OUTPUT);

pinMode(s1, INPUT);
pinMode(s2, INPUT);
pinMode(s3, INPUT);
pinMode(s4, INPUT);
enc1.setType(TYPE2);

digitalWrite(r1, 1);
digitalWrite(r2, 1);
digitalWrite(r3, 1);
digitalWrite(r4, 1);

dht.begin(); 

Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();


  uint32_t currentFrequency;
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("t(C)=    h(%)=");
  Timer1.initialize(1000);            
  Timer1.attachInterrupt(timerIsr);   

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
}
void timerIsr() {   
  enc1.tick();     
}
void loop() {
  
float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();
   

  
  lcd.setCursor(5, 0);
  lcd.print(temp);
  lcd.setCursor(14, 0);
  lcd.print(hum);

  
  s1 = analogRead(A0);
  s2 = analogRead(A1);
  s3 = analogRead(A2);
  s4 = analogRead(A3);

  
if((s1 >= moisture_limit) and (millis()-tmr1 >=10000)){
  tmr1 = millis();
  digitalWrite(r1, 0);
  delay(1500);
  digitalWrite(r1, 1);
}
if((s2 >= moisture_limit) and (millis()-tmr2 >=10000)){
  tmr2 = millis();
  digitalWrite(r2, 0);
  delay(1500);
  digitalWrite(r2, 1);
}
if((s3 >= moisture_limit) and (millis()-tmr3 >=10000)){
  tmr2 = millis();
  digitalWrite(r2, 0);
  delay(1500);
  digitalWrite(r2, 1);
}
if((s4 >= moisture_limit) and (millis()-tmr4 >=10000)){
  tmr2 = millis();
  digitalWrite(r2, 0);
  delay(1500);
  digitalWrite(r2, 1);
}

if(enc1.isRight()){
  page++;
if(page == 5){
  page = 1;
}
}
if(enc1.isLeft()){
  page--;
  if(page == 0){
  page = 4;
}
}

switch(page){
  case 1:
  lcd.setCursor(0,1);
  lcd.print("humedad1: ");
  
  lcd.print(s1);
  break;
    case 2:
    lcd.setCursor(0,1);
  lcd.print("humedad2: ");
  lcd.print(s2);
  break;
    case 3:
    lcd.setCursor(0,1);
  lcd.print("humedad3: ");
  lcd.print(s3);
  break;
    case 4:
    lcd.setCursor(0,1);

  lcd.print("humedad4: ");
  lcd.print(s4);
  break;
  
}
Serial.println(page);
if(millis()-tmr5 >=2000){
   float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  tmr5 = millis();
  Serial.print(s1);
    Serial.print(",");
    Serial.print(s2);
    Serial.print(",");
    Serial.print(s3);
    Serial.print(",");
    Serial.print(s4);

    Serial.print(",");
    Serial.print(temp);
    Serial.print(",");
    Serial.print(hum);
    Serial.print(",");
    Serial.print(rain);
    Serial.print(",");
    Serial.print(power_mW*1000);
    Serial.print(",");
    Serial.print(busvoltage);
    Serial.print(",");
    Serial.print(filled);
    Serial.print("\n");
}
}
