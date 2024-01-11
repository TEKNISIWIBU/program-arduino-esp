int saklar = 3;
int bell =  2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(saklar,INPUT);
pinMode(bell,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(saklar) == HIGH){
   Serial.print(saklar);
   digitalWrite(bell,HIGH);
}else{
   Serial.print(saklar);
   digitalWrite(bell,LOW);
 }
}
