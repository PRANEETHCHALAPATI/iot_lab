import RPi.GPIO as GPIO
import time

led = 2          # GPIO pin for LED
IRSensor = 17    # GPIO pin for IR sensor
PIRSensor = 4    # GPIO pin for PIR sensor

GPIO.setmode(GPIO.BCM)
GPIO.setup(led, GPIO.OUT)
GPIO.setup(IRSensor, GPIO.IN)
GPIO.setup(PIRSensor, GPIO.IN)

try:
    while True:
        pir_value = GPIO.input(PIRSensor)
        ir_value = GPIO.input(IRSensor)

        if pir_value == 1 and ir_value == 0:
            GPIO.output(led, GPIO.HIGH)
            print("Person detected, height matched")
        elif pir_value == 1 and ir_value == 1:
            GPIO.output(led, GPIO.LOW)
            print("Person detected, height not matched")
        else:
            GPIO.output(led, GPIO.LOW)
            print("Person not detected")

        time.sleep(0.2)  # small delay to stabilize readings

except KeyboardInterrupt:
    print("Program stopped")

finally:
    GPIO.cleanup()  # Reset GPIO pins
