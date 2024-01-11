#include <Wire.h>

#include <SPI.h>

#include <Adafruit_BMP280.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP280 bmp; // I2C

Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();

Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI

//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {

  Serial.begin(9600);

  lcd.begin();                      // initialize the lcd 
  // Print a message to the LCD.

  lcd.backlight();

  Serial.println(F("BMP280 test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {

  if (!bmp.begin(0x76)) {

    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "

                      "try a different address!"));

    while (1) delay(10);

  }

  /* Default settings from datasheet. */

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */

                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */

                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */

                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */

                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

                    bmp_temp->printSensorDetails();

}

void loop() {

    sensors_event_t temp_event, pressure_event;

    bmp_temp->getEvent(&temp_event);

    bmp_pressure->getEvent(&pressure_event);

    

    Serial.print(F("Temperature = "));

    Serial.print(bmp.readTemperature());

    Serial.println(" *C");

    Serial.print(F("Pressure = "));

    Serial.print(pressure_event.pressure);

    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));

    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */

    Serial.println(" m");

    Serial.println();

    lcd.setCursor(0,0);

    lcd.print("BMP 280 Live Monitor");

    lcd.setCursor(0,1);

    lcd.print("T (");

    lcd.print((char)223);

    lcd.print("C): ");

    lcd.print(bmp.readTemperature());

    lcd.print("  "); 

    lcd.setCursor(0,2);

    lcd.print("P(hPa): "); 

    lcd.print(pressure_event.pressure);

    lcd.print("  "); 

    lcd.setCursor(0,3);

    lcd.print("A  (m): "); 

    lcd.print(bmp.readAltitude(1013.25));

    lcd.print("  ");         

    delay(2000);

}