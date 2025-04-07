#include "ESP8266WiFi.h"
//#include "Hash.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"


// Replace with your network credentials
const char* ssid = "Salavcell";
const char* password = "sembarang";

const int analogInput = A0;
float vout =0.0;
float vin =0.0;
float R1 =3900;//nilai resistansi R1
float R2 =560;//nilai resistansi R2

int value = 0;/*
unsigned long previousMillis = 0;   
const long interval = 100;
*/  
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">VOLT</span> 
    <span id="VOLT">%VOLT%</span>
    <sup class="units">&deg;C</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("VOLT").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/VOLT", true);
  xhttp.send();
}, 500 ) ;

</script>
</html>)rawliteral";
 String processor(const String& var){
   if(var == "VOLT"){
     return String(vin);
   }
   return String();
 }
void setup(){
  pinMode(analogInput,INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/VOLT", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain",String(vin).c_str());
  });

  server.begin();
}
 
void loop(){
  
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1023.0; // see text
   vin = vout /(R2/(R1+R2)); 
   delay(100);
  
   /*
   Serial.print(" \t Voltage = ");
   Serial.print(vin);
   Serial.println(" VOLT");
  */
  
}

