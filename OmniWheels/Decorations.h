

//void SetSpeed(int N1, int N2, int N3, int N4, int acceleration);
//void SetSpeedNow(int N1, int N2, int N3, int N4, int acceleration);

int scaled(float in, float maxin, float maxout);
void JoystickConverter(int x, int y, int *a, int *b, int *c, int *d);

void ButtonUp(int *N1, int* N2, int*N3, int*N4);
void ButtonDown(int *N1, int* N2, int*N3, int*N4);
void ButtonRight(int *N1, int* N2, int*N3, int*N4);
void ButtonLeft(int *N1, int* N2, int*N3, int*N4);
void TriangleButton();
void CircleButton();
void CrossButton(int *N1, int* N2, int*N3, int*N4);
void SquareButton();
void L2Button();
void R2Button();
void LeftJoystick(int *N1, int* N2, int*N3, int*N4);
void RightJoystick(int *N1, int* N2, int*N3, int*N4);
