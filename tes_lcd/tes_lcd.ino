#
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//define I2C address......
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  lcd.begin();
  lcd.clear();
  lcd.backlight();

}

void loop() {
  lcd.setCursor(2,0);
  lcd.print("Hello World");
  delay(1000);
  lcd.setCursor(2,1);
  lcd.print("JehanKandy");
  delay(1000);
}