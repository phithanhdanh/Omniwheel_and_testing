#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <SoftwareSerial.h>

class MotorDriver{
    
    #define MAX_NUM 100
    #define DELAY 2
    
  public:

    MotorDriver(int,int*,int*,const int, const int); // * contructor.Declare the number of Drivers; Links the MotorDriver to the Speed array and acceleration.
    void begin(int);       // * put this in void setup() to set the Serial Baudrate that we would use to communicate with MSD Drivers.
    void SetSpeed();            // * send updated data from the Speed array to Drivers.
    void DirectSet(int*,int);   // * send new speed data immediately to Drivers (this include new Speed array and new acceleration).
    void DirectSet();
    
  private:
  
    bool set[MAX_NUM];          // * array of motors' status (set or not set).
    int currentmillis, previousmillis;  // * we use these to send data to Drivers continuously.
    String data;                // * objest String. Contain the command string we need to send to Drivers.
    int* motor;                 // * pointer to the Speed array. 
    int *accelerate;            // * pointer to acceleration variable. 
    int n;                      // * number of motors.  
    int prespeed[MAX_NUM]; 

    void ScaleSpeed(int*,double);  // * Increase speed of specifed motor.

    SoftwareSerial *DriverSerial; // * Pointer to object of class SofwareSerial.

};

#endif
