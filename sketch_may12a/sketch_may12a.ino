
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


void setup() {
  // declaración de reles
pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
pinMode(r3, OUTPUT);
pinMode(r4, OUTPUT);

Serial.begin(9600);

}

void loop() {
  
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
}
