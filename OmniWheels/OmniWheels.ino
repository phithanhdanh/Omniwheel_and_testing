
#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

//Ket noi lan dau bang cach nhan nut share và nut PS.
//PS4BT PS4(&Btd, PAIR);
//Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi.
PS4BT PS4(&Btd);

//----------Library testing-----------//
int n = 4;
int Speed[] = {0, 0, 0, 0}, brake[] = {0,0,0,0};
int acceleration = 2000;
int *N1, *N2, *N3, *N4;
//int *N1=&Speed[0], *N2=&Speed[1], *N3=&Speed[2], *N4=&Speed[3];
//------Motor Driver Library test-----/
#include "MotorDriver.h"
MotorDriver omni(n, Speed, &acceleration,12,13);
/*/------DUALSHOCK4 Library test------/
#include "DUALSHOCK4.h"
DUALSHOCK4 PS4(4,Speed);
//------------------------------------*/

#include "Buttons.h"
bool motorOn = 1;

void setup() {
  Serial.begin(115200);
  omni.Initialize(19200);     // set the data rate for the SoftwareSerial port
  
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  
  //PS4.Initialize();
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

 N1=&Speed[0], N2=&Speed[1], N3=&Speed[2], N4=&Speed[3];
}

void loop() {
  
  //Dualshock4 handling----------------------
  Usb.Task();
  //Serial.print(F("\nAttempt1\n"));
  //PS4.Task();
  if (PS4.connected()) {   
      LeftJoystick(N1,N2,N3,N4);
      //RightJoystick(N1,N2,N3,N4);
      //PS4.LAnalogueStick();
      if (PS4.getButtonClick(PS)) {
      //if (PS4.PSClicked()){
        if (Serial) Serial.print(F("\r\nPS"));
        PS4.disconnect();
      }
      /*else{
      ButtonUp(N1,N2,N3,N4);
      ButtonDown(N1,N2,N3,N4);
      ButtonRight(N1,N2,N3,N4);
      ButtonLeft(N1,N2,N3,N4);
      CrossButton(N1,N2,N3,N4);
      //L2Button();
      }*/ 
      //Serial.print(F("\nAttempt3"));
    if (*N1 || *N2 || *N3 || *N4) {
      omni.SetSpeed(); 
      motorOn = 1;
    }
    else if (motorOn) {
      omni.DirectSet(brake,20000);
      motorOn = 0;
    }  
  }
  else if (motorOn) {
    omni.DirectSet(brake,20000);
    motorOn = 0;
  }
  //-----------------------------------------  
}
