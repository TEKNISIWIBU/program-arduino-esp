int led = 11;
int pot = A1;
int output;
int duty;
int pwm_val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(pot, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  output = analogRead(pot);
  pwm_val = map(output, 0, 1023, 0, 255);
  duty = pwm_val/2.56;
  analogWrite(led, duty);
  Serial.print("potensiometer: ");
  Serial.print(pwm_val);
  Serial.print(" duty_cycle: ");
  Serial.print(duty);
  Serial.println();
  delay(500);
}
