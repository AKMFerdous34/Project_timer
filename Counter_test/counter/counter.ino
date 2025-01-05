#include "SevSeg.h"
SevSeg sevseg;
//int seconds;
unsigned long initial;
unsigned long last;
int initiate;
int start;
int final_count;
int current_count;
unsigned long time;
void setup() {
  // put your setup code here, to run once:
 byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);  
  current_count = 5 ; 
  start = 0;
  initiate = 100;
  //sevseg.setNumber(0b0000, 2);
 // sevseg.refreshDisplay(); // Must run repeatedly
  //Serial.begin(9600);
}


void loop() {
  
  initiate = analogRead(A5);
  if(initiate<20){
    start = 1;
  }
  //Serial.println(start);
 //
  //sevseg.setNumber(0b0000, 2);
  //sevseg.refreshDisplay(); // Must run repeatedly
  if (start){
  //count in seconds
  time = millis();
  initial = time;
  //Serial.println(start);
  //seconds = time/1000;
  //test the minutes
  //seconds = time/60000;
  // Serial.println(count);
  while(1){
   time = millis();
   last = time - initial;
   Serial.println(last);
   sevseg.setNumber(current_count, 2);  
   sevseg.refreshDisplay(); // Must run repeatedly 
  if (last >= 60000){  
  current_count = current_count - 1;   
  sevseg.setNumber(current_count, 2);  
  sevseg.refreshDisplay(); // Must run repeatedly
  break;
  }
  }
  if (current_count == 0){
    //sound the alarm
    analogWrite(A0,255);
  }
  }
  //Serial.println(current_count);
  sevseg.setNumber(current_count, 2);
  sevseg.refreshDisplay(); // Must run repeatedly
  }
  
  

