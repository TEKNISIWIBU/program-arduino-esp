#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
LiquidCrystal_I2C lcd (0x27,16,2);
const int oneWireBusPin = 4;

OneWire oneWire(oneWireBusPin);
DallasTemperature Sensors(&oneWire);

void setup(){
  Serial.begin(9600);
  Sensors.begin();
  lcd.init();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("sensor ds18b20");
   lcd.setCursor(0,1);
   lcd.print("m zadid ilmi");
   delay(1000);
   lcd.clear();
}
void loop(){
  //Sensors.setResolution(9);//resolusi dengan kelipatan 0.5 derajat celcius
  //Sensors.setResolution(10);//resolusi dengan kelipatan 0.25 derajat celsius
  //Sensors.setResolution(11);//resolusi dengan kelipatan 0.125 derajat celsius
  //Sensors.setResolution(12);//resolusi dengan kelipatan 0.0625 derajat celsius
  Sensors.requestTemperatures();
float celsius = Sensors.getTempCByIndex(0);
float Farenhait = Sensors.toFahrenheit(celsius);

lcd.setCursor(0,0);
lcd.print("celcius:");
lcd.print(celsius);
lcd.print((char)223); 

lcd.setCursor(0,1);
lcd.print("faren :");
lcd.print(Farenhait); 
lcd.print("F");

//Serial.println(celsius,1);
Serial.println(celsius,3);
//Serial.println(celsius,3);
//Serial.println(celsius,4);
}