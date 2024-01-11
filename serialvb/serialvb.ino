#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 3 
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27 , 16,2); 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
 
 int input = analogRead(A0);
 Serial.println(input);
 delay(100);
 float kelembapan = dht.readHumidity();
 float suhu       = dht.readTemperature();
 lcd.setCursor(0,0);
 lcd.print("gas:");
 lcd.print(input);
 lcd.setCursor(10,0);
 lcd.print("T:");
 lcd.print(suhu);
 
 Serial.println(suhu);
 Serial.println(kelembapan);
 delay(1000);
}
