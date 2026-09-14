#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import smbus
from gpiozero import * #https://gpiozero.readthedocs.io/en/stable/recipes.html
from signal import pause
from time import sleep

PIR_PIN = 24
LED_PIN = 23


def main(): 
  print('{0:board}'.format(pi_info())) 
  print('{0:specs}'.format(pi_info())) 
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
  print('PIR {0} (+5V)'.format(PIR_PIN))
  print('LED {0}'.format(LED_PIN))
  print('---------------------')
  
  pir = MotionSensor(PIR_PIN)
  led = LED(LED_PIN) 

  try:
    while True:
      if pir.motion_detected:
        print('*** MOVE DETECTED ***', end='\r')
        led.on() 
      else:
        print('                     ', end='\r')
        led.off()
    sleep(0.5)
  except:
    pass

  print('\n---------------------')
  pir.close()
  led.close()

if __name__ == '__main__':
  main()
