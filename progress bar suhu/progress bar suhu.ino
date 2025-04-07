#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define pinDHT 3
LiquidCrystal_I2C lcd (0x27,16,2);
SimpleDHT11 dht11(pinDHT);
int progresBar = 0;
byte bar1[]={
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin();
lcd.createChar(0,bar1);
lcd.setCursor(0,0);
lcd.print("suhu");
}

void loop() {
  // put your main code here, to run repeatedly:
byte temperature =0;
byte humidity =0;
int err = SimpleDHTErrSuccess;
if((err = dht11.read(&temperature,&humidity,NULL))!= SimpleDHTErrSuccess){
  Serial.print("read failed");
  Serial.println(err);
  delay(1000);
  return;
 }
progresBar  = map(temperature,0,1023,0,100);
 for(int i = 0;i<progresBar ;i++){
   lcd.setCursor(i,1);
   lcd.write(byte(0));
 }
 delay(200);
 Serial.print("sample ok:"); 
 Serial.print((int)temperature);
 Serial.print(" *C,");
 Serial.print((int)humidity);
 Serial.println("H");
 
 
 lcd.setCursor(0,0);
 lcd.print("temperature:"+ String((int)temperature)+" C");
 lcd.setCursor(0,1);
 //lcd.print("kelembapan: "+ String((int)humidity)+"H");

 delay(1000);
}
