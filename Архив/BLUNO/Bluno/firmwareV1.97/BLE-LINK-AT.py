import serial
import unittest
import time

def atcmd(cmd):
    print cmd,
    n = com.write(cmd);
    str=com.readline();
    print str,
    return str
class BLunoTestCls(unittest.TestCase):
    def runTest(self):
        self.assertEqual("OK\r\n",atcmd("AT\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+SETTING=DEFAULT\r\n"));
        self.assertEqual("FSM_TRANS_USB_COM_BLE\r\n",atcmd("AT+FSM=?\r\n"));
        self.assertEqual("ROLE_PERIPHERAL\r\n",atcmd("AT+ROLE=?\r\n"));
        self.assertEqual("ANYONE\r\n",atcmd("AT+CMODE=?\r\n"));
        self.assertEqual("115200,8,N,1\r\n",atcmd("AT+UART=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+UART=115200\r\n"));
        self.assertEqual("UNKNOWN\r\n",atcmd("AT+SETTING=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+ROLE=ROLE_CENTRAL\r\n"));
        self.assertEqual("ROLE_CENTRAL\r\n",atcmd("AT+ROLE=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+ROLE=ROLE_PERIPHERAL\r\n"));
        self.assertEqual("ROLE_PERIPHERAL\r\n",atcmd("AT+ROLE=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+CMODE=UNIQUE\r\n"));
        self.assertEqual("UNIQUE\r\n",atcmd("AT+CMODE=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+CMODE=ANYONE\r\n"));
        self.assertEqual("ANYONE\r\n",atcmd("AT+CMODE=?\r\n"));        
        self.assertEqual("OK\r\n",atcmd("AT+USBDEBUG=ON\r\n"));
        self.assertEqual("ON\r\n",atcmd("AT+USBDEBUG=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+USBDEBUG=OFF\r\n"));
        self.assertEqual("OFF\r\n",atcmd("AT+USBDEBUG=?\r\n")); 
        self.assertEqual("OK\r\n",atcmd("AT+BLUNODEBUG=ON\r\n"));
        self.assertEqual("ON\r\n",atcmd("AT+BLUNODEBUG=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+BLUNODEBUG=OFF\r\n"));
        self.assertEqual("OFF\r\n",atcmd("AT+BLUNODEBUG=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+SETTING=DEFCENTRAL\r\n"));
        self.assertEqual("DEFCENTRAL\r\n",atcmd("AT+SETTING=?\r\n"));
        self.assertEqual("ROLE_CENTRAL\r\n",atcmd("AT+ROLE=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+SETTING=DEFPERIPHERAL\r\n"));        
        self.assertEqual("DEFPERIPHERAL\r\n",atcmd("AT+SETTING=?\r\n"));  
        self.assertEqual("ROLE_PERIPHERAL\r\n",atcmd("AT+ROLE=?\r\n"));
        self.assertEqual("00000\r\n",atcmd("AT+MAJOR=?\r\n"));
        self.assertEqual("00000\r\n",atcmd("AT+MINOR=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+MAJOR=1\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+MINOR=2\r\n"));
        self.assertEqual("00001\r\n",atcmd("AT+MAJOR=?\r\n"));
        self.assertEqual("00002\r\n",atcmd("AT+MINOR=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+MAJOR=4000\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+MINOR=50\r\n"));
        self.assertEqual("04000\r\n",atcmd("AT+MAJOR=?\r\n"));
        self.assertEqual("00050\r\n",atcmd("AT+MINOR=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+NAME=zhangsan\r\n"));
        self.assertEqual("zhangsan\r\n",atcmd("AT+NAME=?\r\n"));
        self.assertEqual("000\r\n",atcmd("AT+TXPOWER=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+TXPOWER=-6\r\n"));
        self.assertEqual("-06\r\n",atcmd("AT+TXPOWER=?\r\n"));
        self.assertEqual("ON\r\n",atcmd("AT+IBEACONS=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+IBEACONS=OFF\r\n"));
        self.assertEqual("OFF\r\n",atcmd("AT+IBEACONS=?\r\n"));
        self.assertEqual("OK\r\n",atcmd("AT+SETTING=DEFAULT\r\n"));
        self.assertEqual("DEFPERIPHERAL\r\n",atcmd("AT+SETTING=?\r\n"));
        self.assertEqual("BLE-Link\r\n",atcmd("AT+NAME=?\r\n"));
        self.assertEqual("000\r\n",atcmd("AT+TXPOWER=?\r\n"));
        self.assertEqual("ON\r\n",atcmd("AT+IBEACONS=?\r\n"));
        self.assertEqual("V1.97\r\n",atcmd("AT+VERSION=?\r\n"));
        
        return
try:
    com=serial.Serial('com32',115200,timeout=20)
    time.sleep(1)
    com.write("+++");
    str=""
    str = com.readline();
    while str != "OK\r\n":
        com.write("AT\r\n");
        str = com.readline();
    unittest.main(exit=False);
finally:
    com.close()

