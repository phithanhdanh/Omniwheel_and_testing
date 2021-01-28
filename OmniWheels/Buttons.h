
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

//Convert Analogue data-------------------------------------------
int scaled(float in, float maxin, float maxout){
  float out = in*maxout/maxin;
  int rounded = (int) out;
  if (out - rounded >= 0.5) rounded++;
    if (rounded > maxout){
        rounded = (int) maxout;
    }
  return rounded;
}

//Handling Button Up----------------------------------------------
void ButtonUp(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(UP)) {
    //Serial.print(F("\r\nUp"));
    PS4.setLed(Red);
    *N1 = -50; *N2 = -50; *N3 = 50; *N4 = 50;
    UpStt = 1;
  }
  else {
    if (UpStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      UpStt = 0;
    }
  }
}

//Handling Button Down--------------------------------------------
void ButtonDown(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(DOWN)) {
    //Serial.print(F("\r\nDown"));
    PS4.setLed(Yellow);
    *N1 = 50; *N2 = 50; *N3 = -50; *N4 = -50;
    DownStt = 1; 
  }
  else {
    if (DownStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      DownStt = 0;
    }
  }
}

//Handling Button Right-------------------------------------------
void ButtonRight(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(RIGHT)) {
    //Serial.print(F("\r\nRight"));
    PS4.setLed(Blue);
    *N1 = 50; *N2 = -50; *N3 = -50; *N4 = 50;          
    RightStt = 1;  
  }
  else {
    if (RightStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      RightStt = 0;
    }
  }
}

//Handling Button Left--------------------------------------------
void ButtonLeft(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(LEFT)) {
    //Serial.print(F("\r\nLeft"));
    PS4.setLed(Green);
    *N1 = -50; *N2 = 50; *N3 = 50; *N4 = -50;          
    LeftStt = 1;
  }
  else {
    if (LeftStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      LeftStt = 0;
    }
  }
}

//Handling Button Triangle----------------------------------------
void TriangleButton(){
  /*if (PS4.getButtonPress(TRIANGLE)) {
    Serial.print(F("\r\nTraingle"));
    PS4.setRumbleOn(RumbleLow);
    //
    TriStt = 1;        
  }
  else {
    if (TriStt != 0){
      //
      TriStt = 0;
    }
  }*/
}

//Handling Button Circle------------------------------------------
void CircleButton(){
  /*if (PS4.getButtonPress(CIRCLE)) {
    Serial.print(F("\r\nCircle"));
    PS4.setRumbleOn(RumbleHigh);
    //
    CirStt = 1;        
  }
  else {
    if (CirStt != 0){
      //
      CirStt = 0;
    }
  }*/
}

//Handling Button Cross-------------------------------------------
void CrossButton(int *N1, int* N2, int*N3, int*N4){
        if (PS4.getButtonPress(CROSS)) {
          Serial.print(F("\r\nCross"));
          PS4.setLedFlash(10, 10); // Set it to blink rapidly
          *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
          //CrStt = 1;
        }
}

//Handling Button Square------------------------------------------
void SquareButton(){ 
  /*if (PS4.getButtonPress(SQUARE)) {
    Serial.print(F("\r\nSquare"));
    PS4.setLedFlash(0, 0); // Turn off blinking
    //
    SqrStt = 1;        
  }
  else {
    if (SqrStt != 0){
      //
      SqrStt = 0;
    }
  }*/
}
//Handling Button L2----------------------------------------------
void L2Button(){
  /*if (PS4.getButtonPress(L2)) {
    Serial.print(F("\r\nL2: "));
    Serial.print(PS4.getAnalogButton(L2));
    //
    L2Stt = 1;        
  }
  else {
    if (L2Stt != 0){
      //
      L2Stt = 0;
    }
  }*/
}

//Handling Button R2----------------------------------------------
void R2Button(){
  /*if (PS4.getButtonPress(R2)) {
    Serial.print(F("\r\nR2: "));
    Serial.print(PS4.getAnalogButton(R2));
    //
    R2Stt = 1;        
  }
  else {
    if (R2Stt != 0){
      //
      R2Stt = 0;
    }
  }*/
}

//Process Joysticks data------------------------------------------
void JoystickConverter(int x, int y, int *a, int *b, int *c, int *d){
    int temp = 2*(x - y);
  *a = scaled(temp, 255, 50); *b = scaled(-temp, 255, 50);
    temp = 2*(255 - (x + y));
  *d = scaled(temp, 255, 50); *c = scaled(-temp, 255, 50);
}

void LeftJoystick(int *N1, int* N2, int*N3, int*N4){
  int x = PS4.getAnalogHat(LeftHatX), y = PS4.getAnalogHat(LeftHatY);
  if (x > 137 || x < 117 || y > 137 || y < 117){
    JoystickConverter(x,y,N4,N2,N1,N3);
    LeftJStt = 1;
  }
  else {
    if (LeftJStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      LeftJStt = 0;
    }
  }
}
void RightJoystick(int *N1, int* N2, int*N3, int*N4){
  int x = PS4.getAnalogHat(RightHatX), y = PS4.getAnalogHat(RightHatY);
  if (x > 137 || x < 117 || y > 137 || y < 117){
    JoystickConverter(x,y,N4,N2,N1,N3);
    RightJStt = 1;

  }    
  else {
    if (RightJStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      RightJStt = 0;
    }
  }
}
//----------------------------------------------------------------
