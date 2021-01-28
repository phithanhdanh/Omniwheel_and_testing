#if 0
#ifndef DUALSHOCK4_H
#define DUALSHOCK4_H

#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>

class DUALSHOCK4 {
  
    #define MAX_MOTOR 100
    
  public:
    
    DUALSHOCK4(int,int*);                            // * constructor (number of wheels, Speed array)
    DUALSHOCK4(int,int*,int,int*);                   // * constructor (..., number of pickup engines, Pick_up array)
    DUALSHOCK4(int,int*,int,int*,int,int*);          // * constructor (..., number of load engines, Load array)
    DUALSHOCK4(int,int*,int,int*,int,int*,int,int*); // * constructor (..., number of shooting engines, Shoot array)

    void Initialize();
    /* Functions to use with PS4 Bluetooth library: */
    void Task();
    bool connected();
    bool PSClicked();
    void disconnect();
    
    /* Functions to get data from the Dualshock: */
    void Up();
    void Down();
    void Right();
    void Left();
    void Triangle();
    void Circle();
    void Cross();
    void Square();
    void L1Button();
    void L2Analogue();
    void L3Stick();
    void R1Button();
    void R2Analogue();
    void R3Stick();
    void LAnalogueStick();
    void RAnalogueStick();
  
  private:
  
    int _wheels, _pickups, _loads, _shoots; // * number of wheels, pickup,... (sizes of arrays)    
    int *wheel, *pickup, *load, *shoot;     // speed arrays (declared as pointer)
    int blank[MAX_MOTOR]={0};
    /* Buttons status (currently pressed or not): */
    bool UpStt, DownStt, LeftStt, RightStt;
    bool TriStt, CirStt, CrStt, SqrStt;
    bool L1Stt, L3Stt, R1Stt, R3Stt;
    bool LstickStt, RstickStt, L2Stt, R2Stt;

    /* Caculating functions */
    void AnalogeStickConvert(int,int,int*,int*,int*,int*);
    int scaled(float,float,float);

    USB *Usb;
    BTD *Btd;
    PS4BT *PS4;

};


#endif
#endif
