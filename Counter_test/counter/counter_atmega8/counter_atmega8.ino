#include "SevSeg.h"
#include <Keypad.h>

//================================//
//========Keypad settings ======= //
//================================//

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

// mapping of the character keys on the keypad

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'Start','0','CLR'}
};
 
byte rowPins[ROWS] = {1, 2, 3, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {17, 18, 19}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 


//================================//
// seven segment display settings //
//================================//
  
  SevSeg sevseg; // seven segment library object
  byte numDigits = 4; // 4 digits on the seven segment display
  byte digitPins[] = {8, 7, 6, 5}; // mapping the digit pins to the atmega pins
  byte segmentPins[] = {9, 10, 11, 12, 13, 14, 15, 16}; // mapping segment pins to atmega pins
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins

  // extra settings for the seven segment display 
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected 



//declarations for timer
unsigned long initial;
unsigned long last;
int initiate;
int start;
int final_count;
int current_count;
int increment;
int decrement;
unsigned long time;
char key_val;


// Setting up the keypad and seven segment display
void setup() {
  // Setting up the seven segment display counter.
  current_count = 5 ;   
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  Serial.begin(9600);
  
}

// Running the timer program
void loop() {
  
  key_val=keypad.getKey(); 

  
  // Serial.println(key_val);
 /* if (increment < 100){
    if (current_count == 55){
    current_count = 59;
    delay(200);
    }else if (current_count == 59) {
    current_count = 5;
    delay(200);
    }else {
    current_count = current_count + 5 ;
    delay(200);
     }
     } 
  
  else if (decrement < 100){
    if (current_count == 5){
    current_count = 59;
    delay(200);
    }
    else if (current_count == 59){ 
    current_count = 55;
    delay(200);
    }
    else{ 
    current_count = current_count - 5 ;
    delay(200);
    }
  }    
// Working upto here

 
  //delay(100);
  //if(initiate){
    //start = 1;
   // delay(200);
  //}
  //Serial.println(start);
 //
  //sevseg.setNumber(0b0000, 2);
  //sevseg.refreshDisplay(); // Must run repeatedly
  */
   if (key_val == keys[3][0]){
    //count in seconds
    //Serial.println(current_count);
    time = millis();
    initial = time;
    //current_count = 29;
    //Serial.println(initial);
    //seconds = time/1000;
    //test the minutes
    //seconds = time/60000;
    //Serial.println(count);

    while(1){
      delay(1);
      time = millis();
      last = time - initial;
      //Serial.println(last);
      sevseg.setNumber(current_count, 2);  
      sevseg.refreshDisplay(); // Must run repeatedly 
      if (last >= 1000){  
        current_count = current_count - 1;   
        sevseg.setNumber(current_count, 2);  
        sevseg.refreshDisplay(); // Must run repeatedly
        last = 0;
        initial = millis();
      }
      else if (current_count == 0){
        //analogWrite(A0,255);
        break;
      }

    }
  }
  // Working here
  // else if (current_count == 0){
  //   //sound the alarm
  //   analogWrite(A0,255);
  // }
  
  //Serial.println(current_count);  
  sevseg.setNumber(current_count, 2);
  sevseg.refreshDisplay(); // Must run repeatedly
  }  
//}


  
  


