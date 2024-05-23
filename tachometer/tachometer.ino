#define sensor 2
int rpm = 0;
unsigned long millissebelum;
volatile int objects;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

attachInterrupt(digitalPinToInterrupt(sensor), count, FALLING);
delay(2000);
pinMode(sensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (millis() - millissebelum > 1000) {
   rpm = (objects / 3.0)*60;
   objects = 0;
   millissebelum = millis();
}
delay(100);
Serial.print("RPM: ");
Serial.println(rpm);
Serial.print("sensor:");
Serial.println(objects);

}

void count(){
  objects++;
}
