#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo1.attach(2);
  myservo3.attach(3);
  myservo2.attach(4);
  myservo4.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  sudut1(pot1);
  sudut2(pot2);
  sudut3(pot3);
  //sudut4(pot4);
  //delay(500);
}

void sudut1(int deg) {
  int posisi1 = analogRead(deg);
  posisi1 = map(posisi1, 0, 1023, 0, 179);
  Serial.print("sudut 1: ");
    Serial.print(posisi1);
  Serial.println(" ");
  myservo1.write(posisi1);
}
void sudut2(int deg) {
  int posisi2 = analogRead(deg);
  posisi2 = map(posisi2, 0, 1023, 0, 179);
  Serial.print("sudut 2: ");
    Serial.print(posisi2);
  Serial.println(" ");
  myservo2.write(posisi2);
}
void sudut3(int deg) {
  int posisi3 = analogRead(deg);
  posisi3 = map(posisi3, 0, 1023, 0, 179);
  Serial.print("sudut 3: ");
    Serial.print(posisi3);
  Serial.println(" ");
  myservo3.write(posisi3);
}
void sudut4(int deg) {
  int posisi4 = analogRead(deg);
  posisi4 = map(posisi4, 0, 1023, 0, 179);
  Serial.print("sudut 4: ");
    Serial.print(posisi4);
  Serial.println(" ");
  myservo4.write(posisi4);
}