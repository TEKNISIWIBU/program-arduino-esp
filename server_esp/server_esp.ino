#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "webpage.h"

const char* ssid ="Salavcell";
const char* pass ="sembarang"; 
ESP8266WebServer server(80);
//fungsi untuk mengirimkan webserver didalam esp8266
void handleRoot(){
  Serial.println("memanggil website");
  String web = MAIN_page;
  server.send(200,"text/html",web);
  }
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid,pass);

 while(WiFi.status() != WL_CONNECTED){
 delay(500);
 Serial.print(".."); 
 }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();   
  server.on("/",handleRoot);
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
