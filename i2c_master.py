#!/usr/bin/env python3
# Raspberry Pi I2C master -> Arduino slave example
from smbus import SMBus
import time
import sys

I2C_ADDR = 0x08        # Arduino slave address
BUS_NUM = 1            # Use I2C bus 1 on modern Raspberry Pi

def main():
    try:
        bus = SMBus(BUS_NUM)
    except Exception as e:
        print("Failed to open I2C bus:", e)
        sys.exit(1)

    print("Enter '1' to turn LED ON, '0' to turn LED OFF, 'q' to quit")
    try:
        while True:
            val = input(">>>> ").strip()
            if val == 'q':
                break
            elif val == '1':
                try:
                    bus.write_byte(I2C_ADDR, 0x1)
                    print("Sent: ON")
                except Exception as e:
                    print("I2C write failed:", e)
            elif val == '0':
                try:
                    bus.write_byte(I2C_ADDR, 0x0)
                    print("Sent: OFF")
                except Exception as e:
                    print("I2C write failed:", e)
            else:
                print("Unknown command. Use '1', '0', or 'q'.")
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nInterrupted by user")
    finally:
        try:
            bus.close()
        except:
            pass
        print("Exiting")

if __name__ == "__main__":
    main()
