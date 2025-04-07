#define touch 6
const int led1 = 3;
const int led2 = 4;
const int led3 = 5;
const int led4 = 13;
bool kondisi = false;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(touch, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(touch) == LOW) {
    count++;
    kondisi =!kondisi;
    Serial.println(kondisi);
    digitalWrite(led4, kondisi);
    delay(500);
  }

  /*
 switch(count){
   case 1:
    digitalWrite(led1,HIGH);
   break;
   case 2:
    digitalWrite(led2,HIGH);
   break;
   case 3:
    digitalWrite(led3,HIGH);
   break;
   case 4:
    digitalWrite(led4,HIGH);
   break;
   default:
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    count = 0;
   break;
 }*/
}