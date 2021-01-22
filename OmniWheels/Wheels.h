int previousmillis = millis(), currentmillis = millis();
bool set1 = 0, set2 = 0, set3 = 0, set4 = 0;

//SET SPEED AND ACCELERATION--------------------------------------
void SetSpeed(int N1, int N2, int N3, int N4, int acceleration){
  if (N1 >0) N1 *= 1.05;
  else if (N1<0) N1 *= 1.05;
  String s1,s2,s3,s4, x = String(" A"+String(String(acceleration)+"}"));
  s1 = String(String("{N1  V" + String(N1)) + x);
  s2 = String(String("{N2  V" + String(N2)) + x);
  s3 = String(String("{N3  V" + String(N3)) + x);
  s4 = String(String("{N4  V" + String(N4)) + x);

  currentmillis = millis();
  if (currentmillis - previousmillis >= 2){
      if (set1 == 0){
          mySerial.print(s1);
          //mySerial.print("{N1  V");mySerial.print(N1);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          previousmillis = millis();
          Serial.print(F("\r\n\n\n\n:::::::::::::::::::::::::: ")); Serial.print(s1); Serial.print(F(" ::::::::::::::::::::::::::\n\n\n\n"));
          set1 = 1;
      }
      else if (set2 == 0){     
          mySerial.print(s2);
          //mySerial.print("{N2  V");mySerial.print(N2);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          previousmillis = millis();
          Serial.print(F("\r\n\n\n\n:::::::::::::::::::::::::: ")); Serial.print(s2); Serial.print(F(" ::::::::::::::::::::::::::\n\n\n\n"));
          set2 = 1;
      }     
      else if (set3 == 0){      
          mySerial.print(s3);    
          //mySerial.print("{N3  V");mySerial.print(N3);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          previousmillis = millis();
          Serial.print(F("\r\n\n\n\n:::::::::::::::::::::::::: ")); Serial.print(s3); Serial.print(F(" ::::::::::::::::::::::::::\n\n\n\n"));
          set3 = 1;
      }     
      else if (set4 == 0){
          mySerial.print(s4);
          //mySerial.print("{N4  V");mySerial.print(N4);mySerial.print(" A"); mySerial.print(acceleration);mySerial.println("}");
          previousmillis = millis();
          Serial.print(F("\r\n\n\n\n:::::::::::::::::::::::::: ")); Serial.print(s4); Serial.print(F(" ::::::::::::::::::::::::::\n\n\n\n"));
          set4 = 1;
      }
      else {set1 = 0, set2 = 0, set3 = 0, set4 = 0;}       
  }      
}

void SetSpeedNow(int N1, int N2, int N3, int N4, int acceleration){
  if (N1 >0) N1 *= 1.05;
  else if (N1<0) N1 *= 1.05;
  String s1,s2,s3,s4, x = String("  V0 A20000 }"+String(String(acceleration)+"}"));
  s1 = String(String("{N1" + x));
  s2 = String(String("{N2" + x));
  s3 = String(String("{N3" + x));
  s4 = String(String("{N4" + x));

  delay(2);
  mySerial.print(s1);
  delay(2); Serial.print("\nX");
  mySerial.print(s2);
  delay(2); Serial.print("X");
  mySerial.print(s3);
  delay(2); Serial.print("X");
  mySerial.print(s4);
  delay(2); Serial.print("X\n");
}
