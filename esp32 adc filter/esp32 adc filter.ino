//membuat filter adc dengan smoothing reading
const int numReadings = 10;
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average
//---------------------------------------//
const int ldr = 12;   //insialisasi pin analog yang digunakan 
int adcVal;           //meyimpan nilai dari pin analog
float voltage;        //variabel flot yang menyimpan nilai konversi adc ke tegangan
//variabel untuk fungsi millis yang digunakan untuk sampling data
unsigned long nowtime, prevtime = 0; 
const int ts = 1000;

void setup() 
{
  Serial.begin(115200);
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  nowtime = millis();  //nilai dari fungsi millis untuk variabel waktu sekarang
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(ldr);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

 if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  if(nowtime - prevtime >= ts){
  average = total / numReadings;
  adcVal = average; // nilai adc yang diberi filter
 //adcVal = analogRead(ldr);  // nilai adc tanpa diberi filter
  voltage = (float(adcVal)/4095) * 3.3;
  Serial.println("ADC= " + String(adcVal)+ "\nTegangan= " + String(voltage));

  prevtime = nowtime;
  }
}