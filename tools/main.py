#!/usr/bin/env python3
import minimalmodbus
import serial
import sys
import time


def setSerialNumber(port, slave_address):

    instrument = minimalmodbus.Instrument(port, slave_address)  # port name, slave address (in decimal)
    instrument.serial.baudrate = 115200         # Baud
    instrument.serial.bytesize = 8
    instrument.serial.parity   = serial.PARITY_NONE
    instrument.serial.stopbits = 1
    instrument.serial.timeout  = 0.1          # seconds

    for i in range(16):
        instrument.write_bit(i, 1)
        time.sleep(0.1)
        instrument.write_bit(i, 0)
        time.sleep(0.1)
    
if __name__ == "__main__":
    if len(sys.argv)<4:
        print(f"usage: {sys.argv[0]} porta indirizzo")
        exit(1)
    setSerialNumber(sys.argv[1], int(sys.argv[2]))
