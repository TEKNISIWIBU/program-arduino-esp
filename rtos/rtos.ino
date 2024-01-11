TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(17,OUTPUT);
  xTaskCreatePinnedToCore(Task1code, "Task1", 1000, NULL, 2, &Task1, 0);
  delay(500);
  xTaskCreatePinnedToCore(Task2code, "Task2", 1000, NULL, 1, &Task2, 1);
  delay(500);
  xTaskCreatePinnedToCore(Task3code, "Task3", 1000, NULL, 1, &Task2, 0);
  delay(500);
}
void Task1code(void* pvParameters) {
  Serial.print("task running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    digitalWrite(2, 1);
    delay(100);
    digitalWrite(2, 0);
    delay(100);
  }
}
void Task2code(void* pvParameters) {
    Serial.print("task running on core ");
    Serial.println(xPortGetCoreID());
    for (;;) {
      digitalWrite(4, 1);
      delay(1000);
      digitalWrite(4, 0);
      delay(1000);
    }
}
void Task3code(void* pvParameters) {
    Serial.print("task running on core ");
    Serial.println(xPortGetCoreID());
    for (;;) {
      digitalWrite(17, 1);
      delay(2000);
      digitalWrite(17, 0);
      delay(2000);
    }
}
  void loop() {
    // put your main code here, to run repeatedly:
  }
