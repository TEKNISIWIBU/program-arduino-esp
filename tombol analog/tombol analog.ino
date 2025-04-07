int analogButton = A0;
int cntr = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(analogButton,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valpb = analogRead(analogButton);
  //Serial.println(valpb);
  if(valpb > 18 && valpb <20){
    Serial.println("tombol 1");
    Serial.println(cntr);
    cntr++;
    delay(300);
  }
   if(valpb > 15 && valpb <18){
    Serial.println("tombol 2");
    Serial.println(cntr);
    cntr--;
    delay(300);
  }
   if(valpb > 13 && valpb < 15){
    Serial.println("tombol 3");
    cntr = 3;
    Serial.println(cntr);
    delay(300);
  }
   if(valpb > 5 && valpb < 8){
    Serial.println("tombol 4");
    cntr = 8;
    Serial.println(cntr);
    delay(300);
  }
}
