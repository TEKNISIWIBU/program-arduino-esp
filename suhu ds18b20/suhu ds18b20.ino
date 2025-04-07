#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

const int rs = 12, enable =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,enable,d4,d5,d6,d7);

OneWire wiring(6);
DallasTemperature sensor(&wiring);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.begin();
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
 sensor.setResolution(9);
 sensor.requestTemperatures(); //konversi suhu
 float dataSuhu =sensor.getTempCByIndex(0);
 Serial.println(dataSuhu);
 
 lcd.setCursor(3,0);
 lcd.print("Temperature");
 lcd.setCursor(6,1);
 lcd.print(dataSuhu,1);
 lcd.print((char)223);
 lcd.print("C");
 delay(500);
}
