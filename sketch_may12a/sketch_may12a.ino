#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 


#define CLK 10
#define DT 9
#define SW 8

#include "GyverEncoder.h"
#include "TimerOne.h"
Encoder enc1(CLK, DT, SW);  

#define rain_sensor 5

#define moisture_limit 800




#define r1 2
#define r2 3
#define r3 4
#define r4 5


int val_1;
int val_2;
int val_3;
int val_4;


int s1;
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

enc1.setType(TYPE2);

Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("t(C)=    h(%)=");
  Timer1.initialize(1000);            // установка таймера на каждые 1000 микросекунд (= 1 мс)
  Timer1.attachInterrupt(timerIsr);   // запуск таймера
}
void timerIsr() {   // прерывание таймера
  enc1.tick();     // отработка теперь находится здесь
}
void loop() {
  

   

  
  lcd.setCursor(5, 0);
  lcd.print(temp);
  lcd.setCursor(14, 0);
  lcd.print(hum);

  
  s1 = analogRead(A0);
  s2 = analogRead(A1);
  s3 = analogRead(A2);
  s4 = analogRead(A3);

  
if(s1 >= moisture_limit){
  digitalWrite(r1, 1);
}
if(s2 >= moisture_limit){
  digitalWrite(r2, 1);
}
if(s3 >= moisture_limit){
  digitalWrite(r3, 1);
}
if(s4 >= moisture_limit){
  digitalWrite(r4, 1);
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
}
