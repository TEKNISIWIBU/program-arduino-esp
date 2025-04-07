#include "max6675.h"
#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("thermocuple K");
  lcd.setCursor(0,1);
  lcd.print("MAX6675 test");
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(1000);
  lcd.clear();
}

void loop() {
  // basic readout test, just print the current temp
  float celsius = thermocouple.readCelsius();
  float farenhait = thermocouple.readFahrenheit();
  lcd.setCursor(0,0);
  lcd.print("C:");
  lcd.print(celsius);
  lcd.setCursor(0,1);
  lcd.print("F:");
  lcd.print(farenhait);

  Serial.print("C = "); 
  Serial.println(celsius);
  Serial.print("F = ");
  Serial.println(farenhait);
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}