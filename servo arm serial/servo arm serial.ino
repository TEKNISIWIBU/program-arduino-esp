#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

unsigned int sudut;
String inString = "", temstr;
char str;
unsigned int nomor, l, i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);

  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  Serial.println("ROBOT ARM SERIAL CONTROL");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    str = Serial.read();
    if (str!= '\n') 
    {
      inString += (char)str;
    } 
    else if (str == '\n') 
    {
      temstr = inString.substring(0, 1);
      nomor = temstr.toInt();
      temstr = inString.substring(2);
      sudut = temstr.toInt();
      Serial.print(nomor);
      Serial.print(" : ");
      Serial.println(sudut);

      switch (nomor) {
        case 1: myservo1.write(sudut); break;
        case 2: myservo2.write(sudut); break;
        case 3: myservo3.write(sudut); break;
        case 4: myservo4.write(sudut); break;
      }
      inString = "";
    }
  }
}