#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"

// Declare a semaphore handle
SemaphoreHandle_t mySemaphore;

// Setup function runs once
void setup() {
  Serial.begin(9600);   // Start serial communication
  Serial.println("Inside setup");

  // Create a binary semaphore if not already created
  if (mySemaphore == NULL) {
    mySemaphore = xSemaphoreCreateBinary();  // Create a binary semaphore

    if (mySemaphore != NULL) {
      xSemaphoreGive(mySemaphore);  // Initially make it available
      Serial.println("Semaphore created and given");
    } else {
      Serial.println("Failed to create semaphore");
    }
  }

  // Create two FreeRTOS tasks
  xTaskCreate(TaskLed, "LedTask", 10000, NULL, 1, NULL);
  xTaskCreate(TaskBlink, "BlinkTask", 10000, NULL, 1, NULL);

  // Set LED pins LOW initially
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

// Empty loop because tasks handle everything
void loop() {}

// Task 1: Controls LED on pin 8
void TaskLed(void *pvParameters) {
  (void) pvParameters;
  Serial.println("Inside TaskLed");
  pinMode(8, OUTPUT);

  for (;;) {
    // Try to take semaphore (wait max 10 ticks)
    if (xSemaphoreTake(mySemaphore, (TickType_t)10) != pdTRUE) {
      Serial.println("TaskLed waiting for semaphore");
      digitalWrite(8, LOW);
    } else {
      Serial.println("Semaphore taken by TaskLed");
      digitalWrite(8, HIGH);   // Turn LED ON
      delay(5000);             // Hold for 5 sec

      // Release semaphore
      xSemaphoreGive(mySemaphore);
      Serial.println("Semaphore given by TaskLed");

      digitalWrite(8, LOW);
      delay(1000);  // Wait before retry
    }
  }
}

// Task 2: Controls LED on pin 7
void TaskBlink(void *pvParameters) {
  (void) pvParameters;
  Serial.println("Inside TaskBlink");
  pinMode(7, OUTPUT);

  for (;;) {
    // Try to take semaphore
    if (xSemaphoreTake(mySemaphore, (TickType_t)10) != pdTRUE) {
      Serial.println("TaskBlink waiting for semaphore");
      digitalWrite(7, LOW);
    } else {
      Serial.println("Semaphore taken by TaskBlink");
      digitalWrite(7, HIGH);   // Turn LED ON
      delay(5000);             // Hold for 5 sec

      // Release semaphore
      xSemaphoreGive(mySemaphore);
      Serial.println("Semaphore given by TaskBlink");

      digitalWrite(7, LOW);
      delay(1000);  // Wait before retry
    }
  }
}
