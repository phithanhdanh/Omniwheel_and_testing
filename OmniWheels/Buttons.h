
#include <math.h>

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

int R2Stt   = 0; 
int L2Stt   = 0;
int UpStt   = 0;
int DownStt = 0;
int LeftStt = 0;
int RightStt  = 0;
int TriStt  = 0;
int CirStt  = 0;
int CrStt   = 0;
int SqrStt  = 0;
int LeftJStt  = 0;
int RightJStt = 0;

//Handling Button Up----------------------------------------------
void ButtonUp(){
      if (PS4.getButtonPress(UP)) {
          Serial.print(F("\r\nUp"));
          PS4.setLed(Red);
        while ( UpStt != 1){
         SetSpeed(-50,50,-50,50,2000);
          UpStt = 1;
        }
      }
      else {
        while( UpStt != 0){
         SetSpeed(0,0,0,0,2000);
          UpStt = 0;
        }
      }
}

//Handling Button Down--------------------------------------------
void ButtonDown(){
     if (PS4.getButtonPress(DOWN)) {
          Serial.print(F("\r\nDown"));
          PS4.setLed(Yellow);
        while ( DownStt != 1){
         SetSpeed(50,-50,50,-50,2000);
          DownStt = 1;
        } 
      }
       else{
        while ( DownStt != 0){
         SetSpeed(0,0,0,0,2000);
          DownStt = 0;
        }
      }
}

//Handling Button Right-------------------------------------------
void ButtonRight(){
        if (PS4.getButtonPress(RIGHT)) {
          Serial.print(F("\r\nRight"));
          PS4.setLed(Blue);
        while ( RightStt != 1){
        SetSpeed(-50,-50,50,50,2000);  
          RightStt = 1;
        }   
      }

      else {
        while( RightStt != 0){
         SetSpeed(0,0,0,0,2000);
          RightStt = 0;
        }
      }
}

//Handling Button Left--------------------------------------------
void ButtonLeft(){
        if (PS4.getButtonPress(LEFT)) {
        Serial.print(F("\r\nLeft"));
        PS4.setLed(Green);
        while ( LeftStt != 1){
         SetSpeed(50,50,-50,-50,2000);
          LeftStt = 1;
        }
      }
      else {
        while( LeftStt != 0){
         SetSpeed(0,0,0,0,2000);
          LeftStt = 0;
        }
      }
}

//Handling Button Triangle----------------------------------------
void TriangleButton(){
        if (PS4.getButtonPress(TRIANGLE)) {
          Serial.print(F("\r\nTraingle"));
        PS4.setRumbleOn(RumbleLow);
        while ( TriStt != 1){
          SetSpeed(0,0,200,0,2000);
          TriStt = 1;
        }
      }
      else {
        while( TriStt != 0){
         SetSpeed(0,0,0,0,2000);
          TriStt = 0;
        }
      }
}

//Handling Button Circle------------------------------------------
void CircleButton(){
        if (PS4.getButtonPress(CIRCLE)) {
          Serial.print(F("\r\nCircle"));
        PS4.setRumbleOn(RumbleHigh);
        while( CirStt != 1){
          SetSpeed(0,200,0,0,2000);
          CirStt = 1;
        }
      }
      else{
        while ( CirStt != 0){
         SetSpeed(0,0,0,0,2000);
          CirStt = 0;
        }
      }   
}

//Handling Button Cross-------------------------------------------
void CrossButton(){
        if (PS4.getButtonPress(CROSS)) {
          Serial.print(F("\r\nCross"));
        PS4.setLedFlash(10, 10); // Set it to blink rapidly
        while ( CrStt != 1){
          Serial.print(F("\r\nCross"));
          SetSpeed(200,0,0,0,2000);
          CrStt = 1;
        }
      }
      else {
        while ( CrStt != 0){
          SetSpeed(0,0,0,0,2000);
          CrStt = 0;
        }
      }  
}

//Handling Button Square------------------------------------------
void SquareButton(){
  
      if (PS4.getButtonPress(SQUARE)) {
         Serial.print(F("\r\nSquare"));
        PS4.setLedFlash(0, 0); // Turn off blinking
        while ( SqrStt != 1){
          SetSpeed(0,0,0,200,2000);
          SqrStt = 1;   
        }
      }
      else{
        while ( SqrStt != 0){
          SetSpeed(0,0,0,0,2000);
          SqrStt = 0;
        }   
      }
}
//Handling Button L2----------------------------------------------
void L2Button(){
       if (PS4.getButtonPress(L2)) {
        Serial.print(F("\r\nL2: "));
      Serial.print(PS4.getAnalogButton(L2));
        while ( L2Stt != 1){      
          SetSpeed(50,50,50,50,2000);  
          L2Stt = 1;
        }
      }
      else {
        while( L2Stt != 0){
          SetSpeed(0,0,0,0,2000);
          L2Stt = 0;
        }
      }
}

//Handling Button R2----------------------------------------------
void R2Button(){
        if (PS4.getButtonPress(R2)) {
          Serial.print(F("\r\nR2: "));
      Serial.print(PS4.getAnalogButton(R2));
        while ( R2Stt != 1){      
          SetSpeed(-50,-50,-50,-50,2000);   
          R2Stt = 1;
        }
      }
      else {
        while( R2Stt != 0){
         SetSpeed(0,0,0,0,2000);
          R2Stt = 0;
        }
      }
}

//Process Joysticks data------------------------------------------
int scaled(float in, float maxin, float maxout){
  int out = round(in*maxout/maxin);
    if (out > maxout){
        out = maxout;
    }
  return out;
}

void JoystickConverter(int x, int y, int *a, int *b, int *c, int *d){
    int temp = 2*(x - y);
  *a = scaled(temp, 255, 50); *b = scaled(-temp, 255, 50);
    temp = 2*(255 - (x + y));
  *d = scaled(temp, 255, 50); *c = scaled(-temp, 255, 50);
}

void LeftJoystick(){
  if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117){
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS4.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS4.getAnalogHat(LeftHatY));
      int a,b,c,d;
      JoystickConverter(PS4.getAnalogHat(LeftHatX),PS4.getAnalogHat(LeftHatY),&a,&b,&c,&d);
      SetSpeed(c,d,b,a,2000);
      LeftJStt = 1;
      }
      else {
        while( LeftJStt != 0){
          SetSpeed(0,0,0,0,2000);       
          LeftJStt = 0;
        }
      }
}
void RightJoystick(){
  if (PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nRightHatX: "));
      Serial.print(PS4.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS4.getAnalogHat(RightHatY));
      int a,b,c,d;
      JoystickConverter(PS4.getAnalogHat(RightHatX),PS4.getAnalogHat(RightHatY),&a,&b,&c,&d);
      SetSpeed(c,d,b,a,20000);
      RightJStt = 1;
      }
      else {
        while( RightJStt != 0){
          SetSpeed(0,0,0,0,20000);       
          RightJStt = 0;
        }
      }
}
//----------------------------------------------------------------
