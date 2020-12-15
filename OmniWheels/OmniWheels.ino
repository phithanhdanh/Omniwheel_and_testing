#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13); //Define PIN12 & PIN13 as software UART
#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
/* khong hieu sao co cai nay:
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 4000;           // interval at which to blink (milliseconds)
*/
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR); //Ket noi lan dau bang cach nhan nut share và nut PS.

// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd); //Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi.

#include "Wheels.h"
#include "Buttons.h"

void setup() {
  SetSpeed(0,0,0,0,20000);
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
  Usb.Task();  
/* Nay o dau ra khong biet:
  unsigned long currentMillis = millis();
  if (mySerial.available()) {
    Serial.write(mySerial.read());
   // Serial.write("hello");
  }
    PrintSerialMonitor();
*/
  if (PS4.connected()) {
    delay(1000);
  }
}
