#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "masukkan ssid anda";
const char* pass = "masukkan password anda";

ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

WiFi.begin(ssid,pass);
while(WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.println("CONNECTING TO WIFI>>>>>");
 } 
 Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
