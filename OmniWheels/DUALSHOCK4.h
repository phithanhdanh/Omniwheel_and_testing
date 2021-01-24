#ifndef DUALSHOCK4_H
#define DUALSHOCK4_H

class DUALSHOCK4 {

  public:
  
    #define MAX_MOTOR 100
    
    DUALSHOCK4(int,int*);                            // * constructor (number of wheels, Speed array)
    DUALSHOCK4(int,int*,int,int*);                   // * constructor (..., number of pickup engines, Pick_up array)
    DUALSHOCK4(int,int*,int,int*,int,int*);          // * constructor (..., number of load engines, Load array)
    DUALSHOCK4(int,int*,int,int*,int,int*,int,int*); // * constructor (..., number of shooting engines, Shoot array)

    /* Functions to use with PS4 Bluetooth library: */
    void task();
    bool Connected();
    bool PSClicked();
    void Discontect();
    
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
  
    bool serial;
    int _wheels, _pickups, _loads, _shoots; // * number of wheels, pickup,... (sizes of arrays)    
    int *wheel, *pickup, *load, *shoot;     // speed arrays (declared as pointer)
    static int blank[MAX_MOTOR];
    /* Buttons status (currently pressed or not): */
    bool UpStt, DownStt, LeftStt, RightStt;
    bool TriStt, CirStt, CrStt, SqrStt;
    bool L1Stt, L3Stt, R1Stt, R3Stt;
    bool LstickStt, RstickStt, L2Stt, R2Stt;

    /* Caculating functions */
    void AnalogeStickConvert(int,int,int*,int*,int*,int*);
    int scaled(float,float,float);

};


#endif
