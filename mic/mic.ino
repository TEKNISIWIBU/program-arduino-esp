const int mic = A0;
int sensor = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(mic,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
sensor = analogRead(mic);
Serial.println(sensor);
}
