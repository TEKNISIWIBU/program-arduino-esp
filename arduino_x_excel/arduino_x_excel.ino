#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
#define DHTPIN 3 
#define DHTTYPE DHT11
const int MQ135 = A0;

LiquidCrystal_I2C lcd(0x3F,16,2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once
lcd.init();
lcd.backlight();
Serial.begin(9600);
dht.begin();
SPI.begin();
   Serial.println("CLEARSHEET");//membersihkan sheet
   Serial.println("LABEL,waktu,suhu,kelembapan,gas");//membuat label dan "data pada sheet"   
pinMode(MQ135,INPUT);
lcd.setCursor(2,0);
lcd.print("monitoring");
lcd.setCursor(1,1);
lcd.print("kualitas udara");
delay(1000);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
int   dataMQ = analogRead(MQ135);
float kelembapan = dht.readHumidity();
float suhu       = dht.readTemperature();

lcd.setCursor(0,0);
lcd.print("T:");
lcd.print(suhu);
lcd.print(" H:");
lcd.print(kelembapan);

lcd.setCursor(0,1);
lcd.print("gas: ");
lcd.print(dataMQ);

Serial.print("DATA,TIME,");
//Serial.print("gas MQ135: ");
Serial.print(dataMQ);
Serial.print(" ,");
//Serial.print("temperature: ");
Serial.print(suhu);
Serial.print(" ,");
//Serial.print("humidity: ");
Serial.print(kelembapan);
Serial.println(" ,");
delay(1000);
}
