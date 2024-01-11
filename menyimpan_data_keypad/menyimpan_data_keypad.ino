//dibuat oleh prima dionanda marris D4 teknik elektronika 
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
float Data = 0;
char hexaKeys[ROWS][COLS] = {
  { 'D', 'C', 'B', 'A' },
  { '#', '9', '6', '3' },
  { '0', '8', '5', '2' },
  { '*', '7', '4', '1' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("set:");
  lcd.print(Data);
}

void loop() {
  // put your main code here, to run repeatedly:
  char customeKey = customKeypad.getKey();
  if (customeKey) {
    if (customeKey >= '0' && customeKey <= '9') {
      Data = Data * 10 + (customeKey - '0');
      lcd.setCursor(0, 0);
      lcd.print("set:");
      lcd.print(Data);
    }
    //char untuk mereset
    if (customeKey == '*') {
      Data = 0;
      lcd.setCursor(0, 0);
      lcd.print("set:");
      lcd.print(Data);
    }
  }
}
