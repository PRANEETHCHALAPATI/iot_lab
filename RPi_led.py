import RPi.GPIO as GPIO
import time

led = 2  # GPIO pin number for LED

# Set pin numbering mode
GPIO.setmode(GPIO.BCM)  

# Set pin as output
GPIO.setup(led, GPIO.OUT)

try:
    while True:
        GPIO.output(led, GPIO.HIGH)  # Turn LED ON
        time.sleep(1)               # Wait 1 second
        GPIO.output(led, GPIO.LOW)   # Turn LED OFF
        time.sleep(1)               # Wait 1 second

except KeyboardInterrupt:
    print("Program stopped")

finally:
    GPIO.cleanup()  # Reset all GPIO pins