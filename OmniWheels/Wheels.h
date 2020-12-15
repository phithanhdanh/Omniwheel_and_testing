
//SET SPEED AND ACCELERATION--------------------------------------
void SetSpeed(int N1, int N2, int N3, int N4, int acceleration){
          mySerial.print("{N1  V");mySerial.print(N1);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          delay(2);
          mySerial.print("{N2  V");mySerial.print(N2);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          delay(2);
          mySerial.print("{N3  V");mySerial.print(N3);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          delay(2);
          mySerial.print("{N4  V");mySerial.print(N4);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          delay(2);
}
