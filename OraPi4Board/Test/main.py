# 
# https://github.com/orangepi-xunlong/wiringOP
# https://github.com/orangepi-xunlong/wiringOP#orange-pi-44b4-lts
# https://github.com/orangepi-xunlong/wiringOP-Python
# 
# sudo apt-get install swig python3-dev python3-setuptools
# 
# git clone https://github.com/orangepi-xunlong/wiringOP.git
# cd wiringOP
# ./build clean
# ./build 
# 
# gpio readall 
# 
# git clone --recursive https://github.com/orangepi-xunlong/wiringOP-Python.git
# cd wiringOP-Python
# python3 generate-bindings.py > bindings.i
# sudo python3 setup.py install
#


import wiringpi
import time

def main(args):
    print("Hello!")
    wiringpi.wiringPiSetup()
    wiringpi.pinMode(6, 1)      # GPIO1_C2
    wiringpi.digitalWrite(6, 1)
    time.sleep(1)
    wiringpi.digitalWrite(6, 0)
    time.sleep(1)
    wiringpi.digitalWrite(6, 1)
    time.sleep(1)
    wiringpi.digitalWrite(6, 0)
    
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
