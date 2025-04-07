#include <Wire.h> 
#include "RotaryEncoder.h"
#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
#include <PID_v1.h>
LiquidCrystal_I2C lcd(0x27,16,2);
BigNumbers_I2C bigNum(&lcd);
byte x = 6;
byte y = 0;

#define tempSensor A0
#define iron 10
#define LED 12
#define ENC_CLK_PIN        11


#define fast        10 // [ms] rotary speed fast
#define slow       1 // [ms] rotary speed slow
#define ROTARY_FAST        3 // [ms] rotary speed fast
#define ROTARY_SLOW       150 // [ms] rotary speed slow
byte increment;
byte enc_clk,    enc_clk_old;
unsigned long enc_rotated_time;


int knob = 100;
void RotaryChanged(); //we need to declare the func above so Rotary goes to the one below


RotaryEncoder Rotary(&RotaryChanged, 2, 3, 4); // Pins 2 (DT), 3 (CLK), 4 (SW)


int
minTemp = 28,       
maxTemp = 500,     
minADC  = 0,    
maxADC  = 290,     

maxPWM    = 255,   
avgCounts = 10,     
lcdInterval = 80, 
  

pwm = 0,            
tempRAW = 0,      
counter = 0,       
setTemp = 0,      
setTempAVG = 0,    
currentTempAVG = 0,
previousMillis = 0,
ledState = LOW;

int bt = 4;
int btstate = 0;
int curbtstate = 0;
int lastbtstate = 0;
int LEDOFF = 8;

float 
currentTemp = 0.0,  
knobStore = 0.0,
store = 0.0;      



//==========================================================================
double Setpoint, Input, Output;
double consKp=2, consKi=0.01, consKd=0.02;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
//==========================================================================



void setup(){

  TCCR1A = (1 << WGM11) | (1 << WGM10); // Set Fast PWM mode
  TCCR1B = (1 << WGM13) | (1 << WGM12); // Set Fast PWM mode
  TCCR1B |= (1 << CS11); // Set prescaler to 8, you can adjust this as needed

  // Enable PWM on OC1A (pin 10 for Arduino Uno)
  TCCR1A |= (1 << COM1A1);  

  enc_clk_old    = digitalRead(ENC_CLK_PIN);
  Serial.begin(9600);
  Rotary.setup(); 
  pinMode(tempSensor,INPUT);
  pinMode(iron,OUTPUT);     
  pinMode(LED,OUTPUT);     
  pinMode(4, INPUT_PULLUP);
  pinMode(LEDOFF, OUTPUT);
  
Input = currentTemp;
Setpoint = knob;
myPID.SetMode(AUTOMATIC);

  
  lcd.backlight();
  lcd.init();
  lcd.clear();
  bigNum.begin();
  lcd.setCursor(1,0);lcd.print("SET");
  digitalWrite(LEDOFF, HIGH);  
}



void RotaryChanged()
{
 
  const unsigned int state = Rotary.GetState();
  
  if (state & DIR_CW && digitalRead(LEDOFF) == LOW)
  knob+=increment;
    
    
  if (state & DIR_CCW && digitalRead(LEDOFF) == LOW)
  knob-=increment;

  if (knob < 100)
  knob = 100;

  if (knob >500)
  knob = 500;
       
}

void loop(){

  enc_clk = digitalRead(3);
  if((enc_clk == 1) && (enc_clk_old == 0)) { // 0->1 transition
    if((millis() - enc_rotated_time) > ROTARY_SLOW) {
      increment = slow;  
    }
    else if((millis() - enc_rotated_time) > ROTARY_FAST) {
      increment = fast;  
    }
    else {
      
      increment = 0;  
    }
    enc_rotated_time = millis();
  }
  enc_clk_old = enc_clk;
  //Serial.println(increment);



  tempRAW = analogRead(tempSensor); 
  currentTemp = map(analogRead(tempSensor),minADC,maxADC,minTemp,maxTemp); 
  
  if(counter<avgCounts){
    store = store+currentTemp;
    knobStore = knobStore+setTemp;
    counter++;
  }
  else{
    currentTempAVG = (store/avgCounts)-1;
    setTempAVG = (knobStore/avgCounts);
    knobStore=0;
    store=0;
    counter=0;
  }
  
  btstate = digitalRead(bt);
      if (btstate != lastbtstate) 
      { 
      lastbtstate = btstate;      
      if(btstate == LOW)
      {
    digitalWrite(LEDOFF, !digitalRead(LEDOFF));
      }      
      }

  Input = currentTemp;
  Setpoint = knob;

myPID.SetTunings(consKp, consKi, consKd);
 
  if(digitalRead(LEDOFF) == LOW){
    myPID.Compute();
    analogWrite(iron, Output);
  }
  else{
    analogWrite(iron, 0);
  }
//==================================================
  if (currentTemp<=0.95*knob && digitalRead(LEDOFF) == LOW){
  digitalWrite(LED,LOW);
  delay (40);
  digitalWrite(LED,HIGH);}
  if (digitalRead(LEDOFF) == HIGH){digitalWrite(LED,LOW);}
  else{digitalWrite(LED,HIGH);}
 
//==================================================
  Serial.print(Setpoint);
  Serial.print("/t");
  Serial.print(Output);
  Serial.print("/t");
  Serial.print(Input);
  Serial.println();  
      
  /*if(currentTemp<=knob && digitalRead(LEDOFF) == LOW){
    pwm=maxPWM;
    digitalWrite(LED,HIGH);
  }
  else{
    pwm=0;
    digitalWrite(LED,LOW);
        
    
  }
  analogWrite(iron,pwm);
  Serial.println(pwm);

*/
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= lcdInterval){
    previousMillis = currentMillis;
 
      
       
    if (digitalRead(LEDOFF) == HIGH){
      lcd.setCursor(1,0);lcd.print("OFF  ");
      lcd.setCursor(0,1);lcd.print("---");lcd.print((char)223);lcd.print("C ");      
    }
    else{
      lcd.setCursor(1,0);lcd.print("SET");
      lcd.setCursor(0,1);lcd.print(knob);lcd.print((char)223);lcd.print("C ");
    }
    
    bigNum.displayLargeInt(currentTempAVG, 6,0,3,false);
    lcd.setCursor(15,0);
    lcd.print("o");
      
  } 
}

