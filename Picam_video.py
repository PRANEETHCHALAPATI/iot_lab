from libcamera import Transform
from picamera2 import Picamera2, Preview
from picamera2.encoders import H264Encoder
import RPi.GPIO as GPIO
from time import sleep

# Initialize camera
picam2 = Picamera2()

# GPIO setup
sensor_pin = 11  # Physical pin number (BOARD mode)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)  # Using physical pin numbering
GPIO.setup(sensor_pin, GPIO.IN)

# Configure camera for video recording
video_config = picam2.create_video_configuration()
picam2.configure(video_config)

print("System ready. Waiting for object detection...")

try:
    while True:
        if GPIO.input(sensor_pin) == 0:
            print("Object detected! Recording video...")

            encoder = H264Encoder(10000000)
            picam2.start_preview(Preview.QTGL, transform=Transform(hflip=True, vflip=True))
            picam2.start_recording(encoder, "myvideo.h264")

            sleep(5)  # Record for 5 seconds

            picam2.stop_recording()
            picam2.stop_preview()
            print("Video saved as myvideo.h264")

        else:
            print("No object detected")
        sleep(2)

except KeyboardInterrupt:
    print("Program stopped by user")

finally:
    GPIO.cleanup()
    picam2.close()
