/**************************************************************
 * Arduino Motor Driver Library - for MSD Driver
 * by Phi Thanh Danh <phithanhdanh2001@gmail.com>
 * 
 * Bach Khoa Robocon Team - 2021
 * 
 * Used PIN: 12, 13 (RX, TX)
 * ************************************************************/
#if 1
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MotorDriver.h"

MotorDriver::MotorDriver(int num_of_motor,int* Speed, int* acceleration,const int RX = 12,const int TX=13){ 
  motor = Speed;
  accelerate = acceleration;
  n = num_of_motor;
  for (int i=0; i<n; i++) set[i]=0;
  DriverSerial = new SoftwareSerial(RX, TX);
}

void MotorDriver::Initialize(int baudRate){
  DriverSerial->begin(baudRate);
  if (Serial) Serial.println(F("\nMotor Driver Started"));
  previousmillis = millis();
  currentmillis = millis();
}

void MotorDriver::SetSpeed(){
  currentmillis = millis();
  String s;
  if (currentmillis - previousmillis >= DELAY){
    s = String(" A"+ String(*accelerate)+"}");
    int i=0;
    for (i = 0; i<n; i++){
      if (set[i] == 0){
        data = String("{N" + String(i+1) + "  V" + String(motor[i]) + s);
        //DriverSerial->println(data);
        previousmillis = millis();
        if (Serial) Serial.println(String("\n\n\n\n\n\n\n\n\n\n::::::::::::::::::::::::::" + data + "::::::::::::::::::::::::::\n\n\n\n\n\n\n\n\n"));
        set[i] = 1;
        break;
      }
    }
    if (set[n-1])
      for (i=0; i<n; i++) set[i]=0;        
  }
}

void MotorDriver::DirectSet(int* newSpeed, int newAcceleration){
  String s = String(" A"+String(newAcceleration)+"}");
  for (int i=0; i<n; i++) {
    data = String("{N" + String(i+1) + "  V" + String(newSpeed[i]) + s);
    while (currentmillis - previousmillis < DELAY) currentmillis = millis();  // * pause for DELAY amount of time before sending new signal to drivers.
    //DriverSerial->println(data);
    previousmillis = millis();
    set[i]=0;
    motor[i]=newSpeed[i];
    //if (Serial) Serial.println(String("\n\n\n\n\n\n\n\n\n\n::::::::::::::::::::::::::" + data + "::::::::::::::::::::::::::\n\n\n\n\n\n\n\n\n"));
  }
  if (Serial) Serial.println("\nXXXX");
}

void MotorDriver::ScaleSpeed(int *motor_i,int proportion){
  if (*motor_i != 0) *motor_i *= proportion;
}

#endif
