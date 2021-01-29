/**************************************************************
 * Arduino Motor Driver Library - for MSD Driver
 * by Phi Thanh Danh <phithanhdanh2001@gmail.com>
 * 
 * Bach Khoa Robocon Team - 2021
 * 
 * Used PIN: 12, 13 (RX, TX)
 * ************************************************************/
 
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MotorDriver.h"

MotorDriver::MotorDriver(int num_of_motor,int* Speed, int* acceleration, const int RX, const int TX){ 
  motor = Speed;              
  accelerate = acceleration;  
  n = num_of_motor;          
  for (int i=0; i<n; i++) {
    set[i]=0;
    prespeed[i]=Speed[i];
  }
  DriverSerial =  new SoftwareSerial(RX, TX);

}

void MotorDriver::begin(int baudRate){
  DriverSerial->begin(baudRate);
  if (Serial) Serial.println(F("\nMotor Driver Library Started"));
  previousmillis = millis();
  currentmillis = millis();
}

void MotorDriver::SetSpeed(){
  ScaleSpeed(&motor[0],1.05);
  currentmillis = millis();
  String s;
  if (currentmillis - previousmillis >= DELAY){
    s = String(" A"+ String(*accelerate)+"}");
    for (int i = 0; i<n; i++){
      if (set[i] == 0){
        set[i] = 1;
        if (motor[i] != prespeed[i]) {
          data = String("{N" + String(i+1) + "  V" + String(motor[i]) + s);
          DriverSerial->println(data);
          if (Serial) Serial.println(String("\n\n\n\n\n\n\n\n\n\n::::::::::::::::::::::::::" + data + "::::::::::::::::::::::::::\n\n\n\n\n\n\n\n\n"));
          previousmillis = millis();
          prespeed[i] = motor[i];
          break;
        }
      }
    }
    if (set[n-1])
      for (int i=0; i<n; i++) set[i]=0;        
  }
}

void MotorDriver::DirectSet() { DirectSet(motor, *accelerate); }
void MotorDriver::DirectSet(int* newSpeed, int newAccelerate){
  ScaleSpeed(&newSpeed[0],1.05);
  String s = String(" A"+String(newAccelerate)+"}");
  for (int i=0; i<n; i++) {
    data = String("{N" + String(i+1) + "  V" + String(newSpeed[i]) + s);
    while ((int)(currentmillis - previousmillis) < DELAY) currentmillis = millis();  // * pause for DELAY amount of time before sending new signal to drivers.
    DriverSerial->println(data);
    if (Serial) Serial.println(String("\n\n\n\n\n\n\n\n\n\n::::::::::::::::::::::::::" + data + "::::::::::::::::::::::::::\n\n\n\n\n\n\n\n\n"));
    previousmillis = millis();
    set[i] = 0;
    prespeed[i] = motor[i] = newSpeed[i];
  }
  if (Serial) Serial.println("\nXXXX");
}

void MotorDriver::ScaleSpeed(int *motor_i,double proportion){
  if (*motor_i != 0) *motor_i *= proportion;
}
