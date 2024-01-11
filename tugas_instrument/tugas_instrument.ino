#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
LiquidCrystal_I2C lcd (0x3F,16,2);
#define pinTriger 2
#define pinEcho 3
const int oneWireBusPin = 4;

OneWire oneWire(oneWireBusPin);
DallasTemperature Sensors(&oneWire);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   Sensors.begin();
   //MEMULAI KOMUNIKASI SERIAL DAN KONFIGURASI SENSOR 
   SPI.begin();
   Serial.println("CLEARSHEET");//membersihkan sheet
   Serial.println("LABEL,waktu,celsius,jarak");//membuat label dan "data pada sheet"   
   lcd.init();
   lcd.backlight();
   lcd.print("sensor instrument");
   lcd.setCursor(0,1);
   lcd.print("temper & level");
   delay(1000);
   lcd.clear();
   pinMode(pinTriger,OUTPUT);
   pinMode(pinEcho,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
// pengaturan nilai lm35
Sensors.requestTemperatures();
float celsius = Sensors.getTempCByIndex(0);
float Farenhait = Sensors.toFahrenheit(celsius);
//level indicator
long durasi,jarak;
digitalWrite(pinTriger,LOW);
delayMicroseconds(2);
digitalWrite(pinTriger,HIGH);
delayMicroseconds(10);
digitalWrite(pinTriger,LOW);
durasi = pulseIn(pinEcho,HIGH);
jarak = (durasi/2)/29;
//menampikan data suhu ke lcd dan serial 
lcd.setCursor(0,0);
lcd.print("celcius: ");
lcd.setCursor(9,0);
lcd.print(celsius); 
lcd.setCursor(14,0);
lcd.print(" C");
//menampilkan data water level ultrasonik ke lcd dan serial
lcd.setCursor(0,1);
lcd.print("jarak: ");
lcd.setCursor(6,1);
lcd.print(jarak);
lcd.setCursor(9,1);
lcd.print(" cm");
//komunikasi serial
Serial.print("DATA,TIME,");
//Serial.print("celsius,");
Serial.print(celsius);
Serial.print(" ,");
//Serial.print("jarak,");
Serial.print(jarak);
Serial.println(" ,");
delay(50);
}
