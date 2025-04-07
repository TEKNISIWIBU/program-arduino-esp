#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "Salavcell";
const char* password = "sembarang";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);
  // Config Static IP
  IPAddress local_IP(192, 168, 0, 10);//ip harus satu dengan router
  IPAddress gateway(192, 168, 0, 111);//ip untuk wifi atau ruter yang ada di rumah
  IPAddress subnet(255, 255, 255, 0);
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World!");
    Serial.println("New client!");
  });
  // Start server
  server.begin();
}
void loop(){
}
