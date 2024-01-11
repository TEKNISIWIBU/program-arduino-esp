int pinPulseSensor = A0;
int pinLED = 13;

int Sinyal;
int Threshold = 500;

void setup()
{
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
}

void loop()
{
  Sinyal = analogRead(pinPulseSensor);
  Serial.println(Sinyal);

  if(Sinyal > Threshold)
  {
    digitalWrite(pinLED, HIGH);
  }
  else
  {
    digitalWrite(pinLED,LOW);
  }
  delay(10);
}