# For dht,(Ada fruit) . After typing code save the code in home/project and open terminal , type Exam/source/bin/activate Now Virtual Environment (Exam) will be activated. Then execute the command: python3 filename.py 
# Thus, output will be shown in the terminal.

import time
import adafruit_dht
import board

dht_device = adafruit_dht.DHT11(board.D17)

while True:
    try:
        temperature_c = dht_device.temperature
        temperature_f = temperature_c * (9 / 5) + 32

        humidity = dht_device.humidity

        print("Temp:{:.1f} C / {:.1f} F    Humidity: {}%".format(temperature_c, temperature_f, humidity))
    except RuntimeError as err:
        print(err.args[0])		

    time.sleep(2.0)
