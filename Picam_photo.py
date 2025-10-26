from picamera2 import Picamera2, Preview
from time import sleep
from libcamera import Transform

# Create camera object
picam2 = Picamera2()

# Ask user how many photos to capture
no = int(input("Enter the number of photos to take: "))

# Start the preview (flip image if camera is mounted upside down)
picam2.start_preview(Preview.QTGL, transform=Transform(hflip=True, vflip=True))

# Start the camera
picam2.start()

# Capture loop
for i in range(1, no + 1):
    # Capture and save each photo with unique name
    picam2.start_and_capture_file(f"/home/project/Pictures/new_image_{i}.jpg")
    print(f"Captured photo {i}")
    sleep(2)  # Wait 2 seconds between captures

# Stop preview and release the camera
picam2.stop_preview()
picam2.close()

print("All photos captured successfully!")
