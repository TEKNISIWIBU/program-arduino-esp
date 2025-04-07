#define LED1  2
#define LED2  3
#define LED3  4
#define LED4  5
#define LED5  6

int sensorPin = A0;
int sensorVlue = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(LED1,OUTPUT);
pinMode(LED2,OUTPUT);
pinMode(LED3,OUTPUT);
pinMode(LED4,OUTPUT);
pinMode(LED5,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorVlue =analogRead(sensorPin);
int lama = map(sensorVlue,0,1023,0,255);
Serial.print("nilai potensio = ");
Serial.println(sensorVlue);
Serial.print("waktu = ");
Serial.println(lama);
//led 1
digitalWrite(LED1,HIGH);
digitalWrite(LED2,LOW);
digitalWrite(LED3,LOW);
digitalWrite(LED4,LOW);
digitalWrite(LED5,LOW);
delay(lama);
digitalWrite(LED1,LOW);
digitalWrite(LED2,HIGH);
digitalWrite(LED3,LOW);
digitalWrite(LED4,LOW);
digitalWrite(LED5,LOW);
delay(lama);
digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED3,HIGH);
digitalWrite(LED4,LOW);
digitalWrite(LED5,LOW);
delay(lama);
digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED3,LOW);
digitalWrite(LED4,HIGH);
digitalWrite(LED5,LOW);
delay(lama);
digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED3,LOW);
digitalWrite(LED4,LOW);
digitalWrite(LED5,HIGH);
delay(lama);
}
