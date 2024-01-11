const int ledM = 5;
const int ledH = 6;
int tombol = 3;
int logika = 0;
//fungsi waktu millis
unsigned long waktu_sebelum1 = millis();
unsigned long waktu_sebelum2 = millis();
//interval
long interval1 = 100;
long interval2 = 3000;

void setup() {
  // put your setup code here, to run once:
pinMode(ledM,OUTPUT);
pinMode(ledH,OUTPUT);
pinMode(tombol,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long waktuSekarang = millis();
//task 1 
 if(waktuSekarang - waktu_sebelum1 > interval1){
  logika = !logika;
  digitalWrite(ledM,logika);
  waktu_sebelum1 = waktuSekarang;
 }
//task 2
if(digitalRead(tombol) == HIGH){
   digitalWrite(ledH,HIGH);
 }else{
   digitalWrite(ledH,LOW);
 }
}
