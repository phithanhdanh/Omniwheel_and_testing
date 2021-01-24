/**************************************************************
 * Arduino Dualshock 4 Controlling Library
 * by Phi Thanh Danh <phithanhdanh2001@gmail.com>
 * 
 * Bach Khoa Robocon Team - 2021
 * 
 * Library needed: USB Host Shield 2.0
 * ************************************************************/
#if 1
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB LibUsb;
//USBHub Hub1(&LibUsb); // Some dongles have a hub inside
BTD BluetoothDevice(&LibUsb); // You have to create the Bluetooth Dongle instance like so

//Ket noi lan dau bang cach nhan nut share và nut PS:
//PS4BT DS4(&BluetoothDevice, PAIR);
//Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi:
PS4BT DS4(&BluetoothDevice);

#include "DUALSHOCK4.h"


DUALSHOCK4::DUALSHOCK4(int n1,int* a1,int n2,int* a2,int n3,int* a3,int n4,int* a4) {
  
  _wheels = n1;   wheel = a1;
  _pickups = n2;  pickup = a2;
  _loads = n3;    load = a3;
  _shoots = n4;   shoot = a4;

  UpStt     = DownStt   = LeftStt = RightStt  = 0;
  TriStt    = CirStt    = CrStt   = SqrStt    = 0;
  L1Stt     = L3Stt     = R1Stt   = R3Stt     = 0;
  LstickStt = RstickStt = L2Stt   = R2Stt     = 0;

  serial = Serial.available();
  
}

DUALSHOCK4::DUALSHOCK4(int n1,int* a1,int n2,int* a2,int n3,int* a3): DUALSHOCK4::DUALSHOCK4(n1,a1,n2,a2,n3,a3,0,blank) {  }
DUALSHOCK4::DUALSHOCK4(int n1,int* a1,int n2,int* a2): DUALSHOCK4::DUALSHOCK4(n1,a1,n2,a2,0,blank,0,blank) {  }
DUALSHOCK4::DUALSHOCK4(int n1,int* a1): DUALSHOCK4::DUALSHOCK4(n1,a1,0,blank,0,blank,0,blank) {  }

void DUALSHOCK4::task() {
  LibUsb.Task();
}
bool DUALSHOCK4::Connected() {
  return DS4.connected();
}
bool DUALSHOCK4::PSClicked() {
  return DS4.getButtonClick(PS);
}
void DUALSHOCK4::Discontect() {
  DS4.disconnect();
}

/* Omni wheels controlling: ------------------------------------------------------------------ */
void DUALSHOCK4::Up() {
   if (DS4.getButtonPress(UP)) {
      //if (serial) Serial.print(F("\r\nUp"));
      DS4.setLed(Red);
          wheel[0] = -50; wheel[1] = -50; wheel[2] = 50; wheel[3] = 50;
          UpStt = 1;
    }
    else if (UpStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          UpStt = 0;
    }
}

void DUALSHOCK4::Down() {
   if (DS4.getButtonPress(DOWN)) {
      //if (serial) Serial.print(F("\r\nDown"));
      DS4.setLed(Yellow);
          wheel[0] = 50; wheel[1] = 50; wheel[2] = -50; wheel[3] = -50;
          DownStt = 1;
    }
    else if (DownStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          DownStt = 0;
    }
}

void DUALSHOCK4::Left() {
   if (DS4.getButtonPress(LEFT)) {
      //if (serial) Serial.print(F("\r\nLeft"));
      DS4.setLed(Green);
          wheel[0] = -50; wheel[1] = 50; wheel[2] = 50; wheel[3] = -50;
          LeftStt = 1;
    }
    else if (LeftStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          LeftStt = 0;
    }
}

void DUALSHOCK4::Right() {
   if (DS4.getButtonPress(RIGHT)) {
      //if (serial) Serial.print(F("\r\nRight"));
      DS4.setLed(Blue);
          wheel[0] = 50; wheel[1] = -50; wheel[2] = -50; wheel[3] = 50;
          RightStt = 1;
    }
    else if (RightStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          RightStt = 0;
    }
}

int DUALSHOCK4::scaled(float in, float maxin, float maxout){
  float out = in*maxout/maxin;
  int rounded = (int) out;
  if (out - rounded >= 0.5) rounded++;
    if (rounded > maxout){
        rounded = (int) maxout;
    }
  return rounded;
}

void DUALSHOCK4::AnalogeStickConvert(int x, int y, int *I, int *II, int *III, int *IV){
  // I, II, III, IV tuong ung voi cac goc phan tu trong he truc toa do Oxy
    int temp = 2*(x - y);
  *IV = scaled(temp, 255, 50); *II = scaled(-temp, 255, 50);
    temp = 2*(255 - (x + y));
  *I = scaled(temp, 255, 50); *III = scaled(-temp, 255, 50);
}

void DUALSHOCK4::LAnalogueStick() {
  int x = DS4.getAnalogHat(LeftHatX), y = DS4.getAnalogHat(LeftHatY);
  if (x > 137 || x < 117 || y > 137 || y < 117){
      AnalogeStickConvert(x,y,&wheel[2],&wheel[1],&wheel[0],&wheel[3]);
      LstickStt = 1;
      /*if (serial) {Serial.print(F("\r\nLeftHatX: "));
      Serial.print(x);
      Serial.print(F("\tLeftHatY: "));
      Serial.print(y);}*/
  }
  else if (LstickStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          LstickStt = 0;
  }
}

void DUALSHOCK4::RAnalogueStick() {
  int x = DS4.getAnalogHat(RightHatX), y = DS4.getAnalogHat(RightHatY);
  if (x > 137 || x < 117 || y > 137 || y < 117){
      AnalogeStickConvert(x,y,&wheel[2],&wheel[1],&wheel[0],&wheel[3]);
      RstickStt = 1;
      /*if (serial) {Serial.print(F("\r\nRightHatX: "));
      Serial.print(x);
      Serial.print(F("\tRightHatY: "));
      Serial.print(y);}*/
  }
  else if (RstickStt){
          wheel[0] = 0; wheel[1] = 0; wheel[2] = 0; wheel[3] = 0;
          RstickStt = 0;
  }
}
    
#endif
