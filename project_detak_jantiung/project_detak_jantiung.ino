#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PULSE_SENSOR_PIN = 0;
const int LED_PIN = 13;
int THRESHOLD = 550;

PulseSensorPlayground pulseSensor;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();

 pulseSensor.analogInput(PULSE_SENSOR_PIN);
 pulseSensor.blinkOnPulse(LED_PIN);
 pulseSensor.setThreshold(THRESHOLD);

  if (pulseSensor.begin())
  {
    Serial.println("PulseSensor object created successfully!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("♥ Heart Rate");

int currentBPM = pulseSensor.getBeatsPerMinute();
  
if (pulseSensor.sawStartOfBeat())
  {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(currentBPM);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    lcd.print(currentBPM);
  }
  //delay(20);
}
