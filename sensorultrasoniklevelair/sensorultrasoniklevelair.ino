
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
int trig = 11;
int echo = 12;


int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
long durasi, jarak,jarakk;
long waktuu = 8;
long old_time = 0;
long waktu = 500;
long old_timee = 0;

int toggle = 1;
LiquidCrystal_I2C lcd(0x27,16,2);  
void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  Serial.begin(9600);
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Info Tenik");
 
  lcd.setCursor(0,1);
  lcd.print("Youtube");
  delay(2000);
  lcd.clear();

}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  durasi = pulseIn(echo, HIGH); 
  jarakk = (durasi / 2) / 29.1;
  Serial.println(jarakk); 
  delay(500); 
    if(jarakk == 1199){

      jarak = '0';
    }else{
      jarak = jarakk;
    }

  
   
  if ( millis() - old_time > waktu){ 
     
  
    lcd.setCursor(0,0); 
    lcd.print("Level Air ");   
    lcd.print(jarak);
    lcd.print(" cm   ");
    
     digitalWrite(led1, HIGH);
     if(jarak <= 7){
          digitalWrite(led2, HIGH);
          
     }else if(jarak > 7){

          digitalWrite(led2, LOW); 
     }

     if(jarak <= 6){
          digitalWrite(led3, HIGH);
      
     }else if(jarak > 6){

          digitalWrite(led3, LOW); 
     }

    if(jarak <= 5){
          digitalWrite(led4, HIGH);
      
     }else if(jarak > 5){

          digitalWrite(led4, LOW); 
     }
     if(jarak <= 4){
          digitalWrite(led5, HIGH);      
     }else if(jarak > 4){
          digitalWrite(led5, LOW); 
     }
     if(jarak <= 3){
          digitalWrite(led6, HIGH);      
     }else if(jarak > 3){
          digitalWrite(led6, LOW); 
     }
      if(jarak <= 2){
          digitalWrite(led7, HIGH);      
     }else if(jarak > 2){
          digitalWrite(led7, LOW); 
         
     }

    
   old_time= millis();

   
 }

}
