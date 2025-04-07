#include<LiquidCrystal_I2C.h>
#include<Wire.h>

LiquidCrystal_I2C lcd (0x27,16,2);
const int sensor_tanah =2;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
Serial.begin(9600);
pinMode(sensor_tanah,INPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
int adc = analogRead(A0);
float hasil= adc * (5.0/1023.0);
  int status_sensor = digitalRead(sensor_tanah); 
  Serial.print("status:");
if(status_sensor == HIGH){
 Serial.println("kering");
 lcd.setCursor(6,0);
 lcd.print("Tanah");
 lcd.setCursor(6,1);
 lcd.print("kering");
 digitalWrite(3,HIGH);
 digitalWrite(4,LOW);
  }else{
 Serial.println("basah");
 lcd.setCursor(6,0);
 lcd.print("Tanah");
 lcd.setCursor(6,1);
 lcd.print("basah");
 digitalWrite(3,LOW);
 digitalWrite(4,HIGH);   
 }
 lcd.setCursor(0,0);
 lcd.print("Tanah");
 lcd.setCursor(0,1);
 lcd.print(hasil);

Serial.print("ADC: ");
Serial.print(adc);
Serial.print(" hasil ");
Serial.println(hasil);
delay(1000);
}
