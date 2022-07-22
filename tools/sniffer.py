import serial

def main():
    ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=0.04)

    while True:
        res = ser.read(256)
        if res:
            print(res.hex())

main()
