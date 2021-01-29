
#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

//co PAIR: nhan nut PS + share de ket noi (dung cho tay Dualshock moi hay usb bluetooth moi)
//khong co PAIR: nhan nut PS de ket noi (dung cho tay Dualshock va usb bluetooth da ket noi lan dau)
//PS4BT PS4(&Btd, PAIR);
PS4BT PS4(&Btd);

int n = 4;
int Speed[4], brake[4];
int acceleration = 2000;
bool motorOn = 1;
int *N1, *N2, *N3, *N4, *accelerate;

#include "MotorDriver.h"
MotorDriver omni(n, Speed, &acceleration, 12, 13);

#include "Buttons.h"

void setup() { 
  Serial.begin(115200);
  omni.begin(19200);     // set the data rate for the SoftwareSerial port
  
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  
  //PS4.Initialize();
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

 N1=&Speed[0]; N2=&Speed[1]; N3=&Speed[2]; N4=&Speed[3];
 accelerate = &acceleration;
}

void loop() { 

  Usb.Task();
  if (PS4.connected()) {   
    LAnalogueStick(N1,N2,N3,N4);
    R2Analogue(accelerate);
    if (PS4.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS4.disconnect();
    }
    else {
      UpButton(N1,N2,N3,N4);
      DownButton(N1,N2,N3,N4);
      RightButton(N1,N2,N3,N4);
      LeftButton(N1,N2,N3,N4);
    }
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

}
