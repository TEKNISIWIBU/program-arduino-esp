    /***************************

    Cara Mengakses dan Pemrograman Sensor BMP280 Menggunakan Arduino Uno

    Oleh : Arduino Indonesia
    Website : www.arduinoindonesia.id
    Toko Online : www.workshopelectronics3in1.com
    Blog : www.edukasielektronika.com

    Copyright @2020

    ****************************/ 

     

    #include <Wire.h>
    #include <SPI.h>
    #include <Adafruit_BMP280.h>

    Adafruit_BMP280 bmp; // I2C

    void setup() {
      Serial.begin(9600);
      Serial.println(F("BMP280 test"));

      if (!bmp.begin(0x76))
      {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        while (1);
      }

      bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                      Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                      Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                      Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                      Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    }

    void loop()
    {
        Serial.print(F("Temperature = "));
        Serial.print(bmp.readTemperature());
        Serial.println(" *C");

        Serial.print(F("Pressure = "));
        Serial.print(bmp.readPressure());
        Serial.println(" Pa");
        
        Serial.println();
        delay(2000);
    }