import RPi.GPIO as GPIO
import time

led = 2          # GPIO pin for LED
IRSensor = 4     # GPIO pin for IR sensor output

# Set pin numbering mode
GPIO.setmode(GPIO.BCM)

# Configure pin directions
GPIO.setup(led, GPIO.OUT)
GPIO.setup(IRSensor, GPIO.IN)

try:
    while True:
        if GPIO.input(IRSensor) == 0:   # Object detected (depends on sensor type)
            GPIO.output(led, GPIO.HIGH)  # Turn LED ON
            print("Object detected!")
        else:
            GPIO.output(led, GPIO.LOW)   # Turn LED OFF
            print("No object detected.")
        time.sleep(0.1)  # Small delay to avoid bouncing

except KeyboardInterrupt:
    print("Program stopped by user")

finally:
    GPIO.cleanup()  # Reset GPIO settings
