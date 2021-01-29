bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
bool UpStt, DownStt, LeftStt, RightStt;
bool TriStt, CirStt, CrStt, SqrStt;
bool L1Stt, L3Stt, R1Stt, R3Stt;
bool LstickStt, RstickStt, L2Stt, R2Stt;

// * ANALOGUE STICKS AND BUTTONS * //-----------------------------

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

//Process Analogue Sticks' data-----------------------------------
void AnalogeStickConvert(int x, int y, int *a, int *b, int *c, int *d){
    int temp = 2*(x - y);
  *a = scaled(temp, 255, 50); *b = scaled(-temp, 255, 50);
    temp = 2*(255 - (x + y));
  *d = scaled(temp, 255, 50); *c = scaled(-temp, 255, 50);
}

void LAnalogueStick(int *N1, int* N2, int*N3, int*N4){
  int x = PS4.getAnalogHat(LeftHatX), y = PS4.getAnalogHat(LeftHatY);
  if (x > 137 || x < 117 || y > 137 || y < 117){
    AnalogeStickConvert(x,y,N4,N2,N1,N3);
    LstickStt = 1;
  }
  else {
    if (LstickStt != 0){
      *N1 = 0; *N2 = 0; *N3 = 0; *N4 = 0;
      LstickStt = 0;
    }
  }
}

void RAnalogueStick(int *N1, int* N2, int*N3, int*N4){
}

//Process Analogue Buttons' data----------------------------------
void L2Analogue(){
}

void R2Analogue(int*accelerate){
  int x = PS4.getButtonPress(R2);
  /*if (x) {
    if (Serial) Serial.print(F("\r\nR2: "));
    if (Serial) Serial.print(x);
  }*/
  if (x) {
    if (x != oldR2Value) *accelerate = scaled(x,255,20000);
    R2Stt = 1;        
  }
  else {
    if (R2Stt != 0){
      *accelerate = 2000;
      R2Stt = 0;
    }
  }
  if (x != oldR2Value) PS4.setRumbleOn(PS4.getButtonPress(L2),PS4.getButtonPress(R2));
  oldR2Value = x;
}


// * DIGITAL BUTTONS * //-----------------------------------------

//Handling Button Up----------------------------------------------
void UpButton(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(UP)) {
    //if (Serial) Serial.print(F("\r\nUp"));
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
void DownButton(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(DOWN)) {
    //if (Serial) Serial.print(F("\r\nDown"));
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
void RightButton(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(RIGHT)) {
    //if (Serial) Serial.print(F("\r\nRight"));
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
void LeftButton(int *N1, int* N2, int*N3, int*N4){
  if (PS4.getButtonPress(LEFT)) {
    //if (Serial) Serial.print(F("\r\nLeft"));
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
}

//Handling Button Circle------------------------------------------
void CircleButton(){
}

//Handling Button Cross-------------------------------------------
void CrossButton(){
}

//Handling Button Square------------------------------------------
void SquareButton(){ 
}

//Handling L1 Button----------------------------------------------
void L1Button(){
}

//Handling R1 Button----------------------------------------------
void R1Button(){
}

//Handling L3 Button----------------------------------------------
void L3Button(){
}

//Handling R3 Button----------------------------------------------
void R3Button(){
}

//----------------------------------------------------------------
