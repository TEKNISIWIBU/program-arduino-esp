#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float setpoint = 0;
const int kipas = 12;
//mengautur variable ds18b20
const int oneWireBusPin = 10;
OneWire oneWire(oneWireBusPin);
DallasTemperature Sensor(&oneWire);
//fungsi waktu millis
unsigned long waktu_sebelum = millis();
long interval = 500;
// ----------------------------------------setting fungsi keypad-------------------------//
const byte ROWS = 4;
const byte COLS = 4;
byte data_count = 0;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//-----------------------------------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("pengatur silo");
  lcd.setCursor(0, 1);
  lcd.print("dengan keypad");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long waktuSekarang = millis();
  if (waktuSekarang - waktu_sebelum > interval) {
    lcd.print(setpoint);
    Sensor.requestTemperatures();
    int celsius = Sensor.getTempCByIndex(0);
    lcd.setCursor(8, 0);
    lcd.print(celsius);
    Serial.println(celsius);
    waktu_sebelum = waktuSekarang;        
  }
  char customeKey = customKeypad.getKey();
  if (customeKey) {
    Serial.println(customeKey);
    Data[data_count] = customeKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
    Serial.begin(customeKey);
    switch (customeKey) {
      case 'A':
        while (data_count != 0) {
          Data[data_count--] = 0;
          lcd.clear();
        }
        return;
        break;
      case 'B':
        Data[data_count] = 0;
        lcd.setCursor(0, 0);

        setpoint = atoi(Data);
        if (celsius >= setpoint) {
          digitalWrite(kipas, HIGH);
        } else {
          digitalWrite(kipas, LOW);
        }
        break;
    }
  }
}
