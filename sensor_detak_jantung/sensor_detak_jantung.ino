int jantung;
int threshold = 550;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
jantung = analogRead(A0);
Serial.print("sensor = ");
Serial.println(jantung);

if(jantung > threshold){
 digitalWrite(LED_BUILTIN,HIGH);
}else{
  digitalWrite(LED_BUILTIN,LOW);
}
delay(50);
}
