#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//KONFIGURASI DAN VARIABLE GY-BMP280
Adafruit_BMP280 bmp;
#define BMP_SCK     (13)
#define BMP_MISO    (12)
#define BMP_MOSI    (11)
#define BMP_CS      (10)
 float pressure;
 float temperature;
//KONFIGURASI SENSOR MQ4
#define gas A0
int nilaigas; 
//KONFIGURASI SENSOR ULTRASONIK
#define triggerPin  D8
#define echoPin     D7
#define batas 9
int buzz = D0;
//--------------------------------------------------------------------------//
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "vivo 1819"
#define WIFI_PASSWORD "zadidilmi"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCYhRQ7y860g1xOcAqrZEp9HOsGP0Usfe0"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://biogas-wp-de651-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//unsigned long sendDataPrevMillis = 0;
//int count = 0;
bool signupOK = false;

void setup(){
  pinMode(gas, INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (!bmp.begin(0x76))
      {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        while (1);
      }
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
    digitalWrite(buzz,HIGH);
    delay(1000);
    digitalWrite(buzz,LOW);
  //bagian serial
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
 delay(1000);
  pressure = bmp.readPressure()/100000;
  temperature = bmp.readTemperature();
  //pembacaan sensor mq4
  nilaigas = analogRead(gas);
  //pembacaan sensor ultrasonik
  long duration, jarak;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = (duration/2) / 29.1;
  if(jarak <= batas){
    digitalWrite(buzz,HIGH);
    delay(1000);
    digitalWrite(buzz,LOW);
  }else{
    digitalWrite(buzz,LOW);
  }
  if (Firebase.ready() && signupOK ) {
    //memasukan data tekanan ke firebase 
    if (Firebase.RTDB.setFloat(&fbdo, "biogas/tekanan",pressure)){
//      Serial.println("PASSED");
       Serial.print("tekanan: ");
       Serial.print(pressure);
       Serial.println(" bar");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //memasukkan data temperature ke firebase 
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "biogas/suhu", temperature)){
//      Serial.println("PASSED");
       Serial.print("Suhu: ");
       Serial.print(temperature);
       Serial.println(" *C"); 
       //bagian lcd      
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //memasukkan data gas ke firebase 
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "biogas/GAS", nilaigas)){
//      Serial.println("PASSED");
       Serial.print("kadar: ");
       Serial.print(nilaigas);
       Serial.println(" %");

    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
   //memasukkan data level ke firebase 
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "biogas/level", jarak)){
//      Serial.println("PASSED");
       Serial.print("level: ");
       Serial.print(jarak);
       Serial.println(" cm");

    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  Serial.println("______________________________");
}
