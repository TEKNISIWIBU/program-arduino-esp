float AktualTemp;
float AktualTemp_1;
float tempSet;
float Awal;
float tempC1;
float pinLM35 = A0;
int Ts = 10;
void setup() {
  Serial.begin(9600);
  pinMode(pinLM35, INPUT);
  AktualTemp_1 = getTemperatureCel(pinLM35);
}
void loop() {
  float celcius = getTemperatureCel(pinLM35);
  //=================RUMUS LPF DIGITAL======================//
  AktualTemp = (0.97*AktualTemp_1)+(0.03*celcius);
  //======================AKHIR RUMUS=======================//
  Serial.print(celcius,1);
  Serial.print("  ");
  Serial.print(AktualTemp,1);
  Serial.println("  ");
  AktualTemp_1 = AktualTemp;
  delay(Ts);//memberikan delay yang digunakan untuk sampling
}
int getTemperatureCel(int pin) {
  float baca = analogRead(pin);
  float cel = (5.0 * baca * 100) / 1024;
  return (cel);
}
/*
int celsius_to_farenhait(float cel){
  float farh = (cel*9) / 5 + 32;
  return(farh);
  }*/