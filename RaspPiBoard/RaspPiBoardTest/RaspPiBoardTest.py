 #!/usr/bin/env python
# -*- coding: utf-8 -*-

import smbus
from gpiozero import *      # https://gpiozero.readthedocs.io/en/stable/recipes.html
from signal import pause
from time import sleep


def main():
  print('{0:board}'.format(pi_info()))
  print('{0:specs}'.format(pi_info()))

  print('--------------------------------------------')
  print('detecting i2c device')
  bus = smbus.SMBus(1) # 1 indicates /dev/i2c-1
  for device in range(128):
    try:
      bus.read_byte(device)
      print('address: {0}'.format(hex(device)))
    except: # exception if read_byte fails
      pass
  print('--------------------------------------------')
  print('Press Ctrl+C to exit')
  
  pir = MotionSensor(24)
  led = LED(25)
  
  try:
    while True:
      if pir.motion_detected:
        print('*', end='')
        led.on()
      else:
        print(' ', end='')
        led.off()
      sleep(1)
  except:
      pass
  
  pir.close()
  led.close()

if __name__ == '__main__':
  main()
