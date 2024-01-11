#include <ThingerESP8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

//konfigurasi Thinger .io
#define USERNAME "zadidilmi"
#define DEVICE_ID "Biogas_Wpjuara"
#define DEVICE_CREDENTIAL "ZcByQ03lbe1CJ&8Y"

#define LED_PIN D5

//VARIABLE UNTUK LIBRARY
Adafruit_BMP280 bmp;
ThingerESP8266 thing(USERNAME,DEVICE_ID,DEVICE_CREDENTIAL);
 float pressure;
 float temperature;
//KONFIGURASI WIFI
const char*ssid = "Salavcell";
const char*pass = "sembarang";
void setup() {
  // put your setup code here, to run once:
 pinMode(LED_PIN,OUTPUT);
 Serial.begin(115200);
 WiFi.begin(ssid,pass);
//konfigurasi sensor bmp280
if (!bmp.begin(0x76))
      {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        while (1);
      }

 while(WiFi.status() != WL_CONNECTED){
   digitalWrite(LED_PIN,LOW);
   Serial.print("menghubungkan nodemcu dengan: ");
   Serial.println(ssid);    
   delay(500);
 }
//bila esp8266 terhubung dengan internet  
  Serial.print("berhasil terhubung......");
  digitalWrite(LED_PIN,HIGH);
//MENGHUBUNGKAN ESP8266 DENGAN THINGER.IO
 thing.add_wifi(ssid,pass);
//menggirim nilai sensor ke thinger io 

thing["sensor"] >> [](pson & out){
   out["persure"] = pressure;
   out["temperature"] = temperature;  
 };
 
}

void loop() {
  // put your main code here, to run repeatedly:
 thing.handle();
 //pembacaan sensor bmp280
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
        Serial.print(F("Temperature = "));
        Serial.print(temperature);
        Serial.println(" *C");

        Serial.print(F("Pressure = "));
        Serial.print(pressure);
        Serial.println(" Pa");
        
        Serial.println();
        delay(2000);
}
