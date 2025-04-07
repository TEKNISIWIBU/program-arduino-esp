const int pinAnalog = A0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print("sensor= ");
 Serial.println(analogRead(pinAnalog));
 delay(100);
}
