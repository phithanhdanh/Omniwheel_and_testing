/**************************************************************
 * Arduino Motor Driver Library - for MSD Driver
 * by Phi Thanh Danh <phithanhdanh2001@gmail.com>
 * 
 * Bach Khoa Robocon Team - 2021
 * 
 * Used PIN: 12, 13.
 * ************************************************************/
#if 1
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <SoftwareSerial.h>
SoftwareSerial DriverSerial(12, 13); //Define PIN12 & PIN13 as software UART

#include "MotorDriver.h"

MotorDriver::MotorDriver(int num_of_motor,int* Speed, int* acceleration) {
  previousmillis = millis();
  currentmillis = millis(); 
  motor = Speed;
  accelerate = acceleration;
  n = num_of_motor;
  for (int i=0; i<n; i++) set[i]=0;
}

void MotorDriver::Initialize(int baudRate, int output_pin){
  DriverSerial.begin(baudRate);
  pinMode(output_pin, OUTPUT);
}

void MotorDriver::SetSpeed(){
  currentmillis = millis();
  if (currentmillis - previousmillis >= DELAY){
    String s = String(" A"+String(String(*accelerate)+"}"));
    int i=0;
    for (i = 0; i<n; i++){
      if (!set[i]){
        data = String(String(String(String("{N" + String(i+1)) + "  V") + String(motor[i])) + s);
        DriverSerial.println(data);
        previousmillis = millis();
        //MotorDriver::Display(String("\n\n\n\n\n\n\n\n\n\n::::::::::::::::::::::::::" + String(data + "::::::::::::::::::::::::::\n\n\n\n\n\n\n\n\n")));
        set[i] = 1;
        break;
      }
    }
    if (set[n-1])
      for (i=0; i<n; i++) set[i]=0;        
  }
}

void MotorDriver::DirectSet(int* newSpeed, int newAcceleration){
  String s = String(" A"+String(String(newAcceleration)+"}"));
  for (int i=0; i<n; i++){
    data = String(String(String(String("{N" + String(i+1)) + "  V") + String(newSpeed[i])) + s);
    delay(2);
    DriverSerial.println(data);
  }
  previousmillis = millis();
  for (int i=0; i<n; i++) set[i]=0;
}

void MotorDriver::Display(String s){
  if (Serial.available()) Serial.println(s);
}

#endif
