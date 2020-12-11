#!/usr/bin/env python
# -*- coding: utf-8 -*-
import smbus
import OPi.GPIO as GPIO     # https://github.com/rm-hull/OPi.GPIO       https://opi-gpio.readthedocs.io/en/latest/api-documentation.html
from signal import pause
from time import sleep

PIR_PIN = 'PC4'  # PC4 - 18
LED_PIN = 'PL9'  # PL9 - 16


def main(): 
  print('Orange Pi Win Plus')
  print(' ----------- ---------- ---- ---- ---------- ----------- ')
  print('|       3V3 |          |  1 | 2  |          | 5V        |')
  print('|  TWI1-SDA |    [PH3] |  3 | 4  |          | 5V        |')
  print('|  TWI1-SCK |    [PH2] |  5 | 6  |          | GND       |')
  print('|     S_PWM |   [PL10] |  7 | 8  | [PL2]    | S_UART_TX |')
  print('|       GND |          |  9 | 10 | [PL3]    | S_UART_RX |')
  print('|  UART3_RX |    [PH5] | 11 | 12 | [PD4]    |           |')
  print('|  UART3_TX |    [PH4] | 13 | 14 |          | GND       |')
  print('| UART3_CTS |    [PH7] | 15 | 16 | [PL9]    |           |')
  print('|       3V3 |          | 17 | 18 | [PC4]    |           |')
  print('| SPI1_MOSI |    [PD2] | 19 | 20 |          | GND       |')
  print('| SPI1_MISO |    [PD3] | 21 | 22 | [PH6]    | UART3_RTS |')
  print('|  SPI1_CLK |    [PD1] | 23 | 24 | [PD0]    | SPI1_CS0  |')
  print('|       GND |          | 25 | 26 | [PD6]    |           |')
  print('|  TWI2-SDA |   [PE15] | 27 | 28 | [PE14]   | TWI2-SCK  |')
  print('|           |    [PB4] | 29 | 30 |          | GND       |')
  print('|           |    [PB5] | 31 | 32 | [PB2]    | UART2_RTS |')
  print('|           |    [PB6] | 33 | 34 |          | GND       |')
  print('|           |    [PB7] | 35 | 36 | [PB3]    | UART2_CTS |')
  print('|           |    [PD5] | 37 | 38 | [PB0]    | UART2_TX  |')
  print('|       GND |          | 39 | 40 | [PB1]    | UART2_RX  |')
  print(' ----------- ---------- ---- ---- ---------- ----------- ')
  print('---------------------')
  print('Detecting i2c device')
  bus = smbus.SMBus(1) # 1 indicates /dev/i2c-1
  for device in range(128):
    try:
      bus.read_byte(device)
      print('address: {0}'.format(hex(device))) 
    except: # exception if read_byte fails
      pass
  print('---------------------')
  print('Press Ctrl+C to exit')
  print('---------------------')
  print('PIR PC4 (+5V)')
  print('LED PL9')
  print('---------------------')
  GPIO.setmode(GPIO.SUNXI)
  GPIO.setwarnings(False)
  GPIO.setup(LED_PIN, GPIO.OUT)
  GPIO.setup(PIR_PIN, GPIO.IN)
  
  try:
    while True:
      if GPIO.input(PIR_PIN) == GPIO.HIGH:
        print('*** MOVE DETECTED ***', end='\r')
        GPIO.output(LED_PIN, 1) 
      else:
        print('                     ', end='\r')
        GPIO.output(LED_PIN, 0)
      sleep(1)
  except:
    pass
  
  print('\n---------------------')
  
if __name__ == '__main__':
  main()
