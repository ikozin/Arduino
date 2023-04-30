#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 
# https://github.com/orangepi-xunlong/wiringOP
# https://github.com/orangepi-xunlong/wiringOP#orange-pi-44b4-lts
# https://github.com/orangepi-xunlong/wiringOP-Python
# https://github.com/rm-hull/bme280
# 
# sudo apt-get install swig python3-dev python3-setuptools
# sudo apt-get install python3-smbus
# 
# pip3 install smbus2 RPi.bme280
#
# git clone https://github.com/orangepi-xunlong/wiringOP.git
# cd wiringOP
# ./build clean
# ./build 
# 
# gpio readall
# 
# orangepi4-lts:~:# gpio readall                      
#  +------+-----+----------+------+---+OPi 4 LTS +---+---+--+----------+-----+------+
#  | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
#  +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
#  |      |     |     3.3V |      |   |  1 || 2  |   |      | 5V       |     |      |
#  |   64 |   0 | I2C8_SDA | ALT2 | 1 |  3 || 4  |   |      | 5V       |     |      |
#  |   65 |   1 | I2C8_SCL | ALT2 | 1 |  5 || 6  |   |      | GND      |     |      |
#  |  150 |   2 |     PWM1 | ALT2 | 1 |  7 || 8  | 1 | ALT2 | I2C3_SCL | 3   | 145  |
#  |      |     |      GND |      |   |  9 || 10 | 1 | ALT2 | I2C3_SDA | 4   | 144  |
#  |   33 |   5 | GPIO1_A1 |   IN | 0 | 11 || 12 | 0 | OUT  | GPIO1_C2 | 6   | 50   |
#  |   35 |   7 | GPIO1_A3 |  OUT | 1 | 13 || 14 |   |      | GND      |     |      |
#  |   92 |   8 | GPIO2_D4 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO1_C6 | 9   | 54   |
#  |      |     |     3.3V |      |   | 17 || 18 | 0 | IN   | GPIO1_C7 | 10  | 55   |
#  |   40 |  11 | SPI1_TXD | ALT3 | 0 | 19 || 20 |   |      | GND      |     |      |
#  |   39 |  12 | SPI1_RXD | ALT3 | 1 | 21 || 22 | 0 | IN   | GPIO1_D0 | 13  | 56   |
#  |   41 |  14 | SPI1_CLK | ALT3 | 1 | 23 || 24 | 1 | ALT3 | SPI1_CS  | 15  | 42   |
#  |      |     |      GND |      |   | 25 || 26 | 0 | IN   | GPIO4_C5 | 16  | 149  |
#  +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
#  | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
#  +------+-----+----------+------+---+OPi 4 LTS +---+---+--+----------+-----+------+
# orangepi4-lts:~:# 
#  
# git clone --recursive https://github.com/orangepi-xunlong/wiringOP-Python.git
# cd wiringOP-Python
# python3 generate-bindings.py > bindings.i
# sudo python3 setup.py install
#
# armbian-config        # system->hardware->i2c8
#
# sudo i2cdetect -y 8   # i2c8
#
# orangepi4-lts:~:# i2cdetect -y 8         
#      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
# 00:                         -- -- -- -- -- -- -- -- 
# 10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 70: -- -- -- -- -- -- 76 --                         
#


import wiringpi
import time
import smbus2
import bme280

def gpio_callback():
    wiringpi.digitalWrite(6, wiringpi.digitalRead(9))
    return

def main(args):
    try:
        print("Hello!")
        wiringpi.wiringPiSetup()
        wiringpi.pinMode(6, 1)      # GPIO1_C2
        wiringpi.pinMode(9, 0)      # GPIO1_C6
        wiringpi.digitalWrite(6, 1)
        time.sleep(1)
        wiringpi.digitalWrite(6, 0)
        time.sleep(1)
        wiringpi.digitalWrite(6, 1)
        time.sleep(1)
        wiringpi.digitalWrite(6, 0)

        address = 0x76
        bus = smbus2.SMBus(8)
        calibration_params = bme280.load_calibration_params(bus, address)
        time.sleep(2)
        data = bme280.sample(bus, address, calibration_params)
        print("Температура={0:.0f}, Влажность={1:.0f}, Давление={2:.0f}".format(data.temperature, data.humidity, data.pressure * 0.750062))

        time.sleep(2)
        data = bme280.sample(bus, address, calibration_params)
        print("Температура={0:.0f}, Влажность={1:.0f}, Давление={2:.0f}".format(data.temperature, data.humidity, data.pressure * 0.750062))

        wiringpi.wiringPiISR(9, wiringpi.INT_EDGE_BOTH, gpio_callback)
        print("\nPress Ctrl+C to exit\n")
        time.sleep(60)
        return 0
    except KeyboardInterrupt:
        print("\nExit")
        return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
