#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13); //Define PIN12 & PIN13 as software UART
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

#include "Decorations.h"
#include "Wheels.h"
#include "Buttons.h"
int previous = millis(), current;  
//int N1=0,N2=0,N3=0,N4=0,accelerate=2000;
bool motorOn = 1;

void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);   // set the data rate for the SoftwareSerial port
  pinMode(10, OUTPUT);          // sets the digital pin 13 as output
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop() {
  
  //Dualshock4 handling----------------------
  Usb.Task();
  current = millis();
  int N1=0,N2=0,N3=0,N4=0,accelerate=2000;
  if (PS4.connected()) {    
      LeftJoystick(&N1,&N2,&N3,&N4);
      RightJoystick(&N1,&N2,&N3,&N4);
    if (PS4.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS4.disconnect();
    }
    else{
      ButtonUp(&N1,&N2,&N3,&N4);
      ButtonDown(&N1,&N2,&N3,&N4);
      ButtonRight(&N1,&N2,&N3,&N4);
      ButtonLeft(&N1,&N2,&N3,&N4);
      CrossButton(&N1,&N2,&N3,&N4);
      //L2Button();
    }
    if (N1 || N2 || N3 || N4) {SetSpeed(N1,N2,N3,N4,accelerate); motorOn = 1;}
    else if (motorOn) {SetSpeedNow(N1,N2,N3,N4,20000); motorOn = 0;}  
  }
  else if (motorOn) {SetSpeedNow(0,0,0,0,20000); motorOn = 0;}
  //-----------------------------------------
  
}
