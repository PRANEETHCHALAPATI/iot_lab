#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandle1, xHandle2;

#define rled 4   // Red LED pin
#define gled 5   // Green LED pin

void taskOne(void *parameter);
void taskTwo(void *parameter);

void setup() {
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  Serial.begin(9600);
  Serial.println("\nInside setup");

  // Create Task 1
  xTaskCreate(taskOne, "TaskOne", 10000, NULL, 1, &xHandle1);
}

void loop() {
  delay(1000);  // Loop does nothing, tasks handle everything
}

void taskOne(void *parameter) {
  int i = 0;
  Serial.println("\nHello from Task 1");

  while (i < 4) {
    Serial.print("Task 1: ");
    if (i == 2) {
      // Create Task 2 when i == 2
      xTaskCreate(taskTwo, "TaskTwo", 10000, NULL, 2, &xHandle2);
    }

    digitalWrite(rled, HIGH);
    digitalWrite(gled, LOW);
    Serial.println(i);

    vTaskDelay(pdMS_TO_TICKS(5000));  // Delay for 5 seconds
    i++;
  }

  Serial.println("Ending Task 1");
  vTaskDelete(NULL);  // Delete this task when done
}

void taskTwo(void *parameter) {
  int i = 0;
  Serial.println("\nHello from Task 2");

  while (i < 4) {
    Serial.print("Task 2: ");
    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
    Serial.println(i);

    vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
    i++;
  }

  Serial.println("Ending Task 2");
  vTaskDelete(NULL);  // Delete this task when done
}
