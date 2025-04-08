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
  {'*','0','#'}
};
 
byte rowPins[ROWS] = {4, 3, 2, 0}; //connect to the row pinouts of the keypad
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
int count_arr; //[4] = {0,0,0,0};
int increment;
int decrement;
unsigned long time;
char key_val;
int wait_key_in;
int pow10;
int j;
int alarm;


// Setting up the keypad and seven segment display
void setup() {
  // Setting up the seven segment display counter.
  current_count = 0;   
  wait_key_in = 0;      // need at least 3 digits to make the start.
  pow10 = 100; //1;    // power of 10 used for setting each digit
  //pow10 = 1;    // power of 10 used for setting each digit
  j=0;
  alarm=1;
  pinMode(alarm,OUTPUT);
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  
  
}

// Running the timer program
void loop() {
  key_val=keypad.getKey(); // obtain inputs from the keypad
   digitalWrite(alarm,0);
  //for (wait_key_in = 0; wait_key_in < 4; wait_key_in = wait_key_in + 1){
  while (wait_key_in < 3){
    millis (); // delay required for while loop to not get hung up.
    digitalWrite(alarm,0);

   // For the hour and second digits, allow 0 - 9    
    if (wait_key_in == 0 || wait_key_in == 2){
      key_val=keypad.getKey(); 
      if (key_val != NO_KEY && key_val != keys[3][2] && key_val != keys[3][0]){
        count_arr = key_val - 48 ; // convert from char to int
        
        for ( j; j < wait_key_in; j= j + 1){  
          //pow10 = pow10 * 10;
          pow10 = pow10 / 10;
        }
        current_count = current_count + ((count_arr) * pow10); //* (pow(10,wait_key_in));
      
        wait_key_in = wait_key_in + 1; 

        digitalWrite(alarm,1); 
        delay(50);      
      }
      
      else if (key_val == keys[3][2]){
        current_count = 0;
        wait_key_in = 0;
        pow10 = 100;
        //pow10 = 1;
        j=0;
        digitalWrite(alarm,1);  
        delay(50); 
      }

      else if (key_val == keys[3][0]){
        digitalWrite(alarm,1);
        delay(50);
        break;
      }
    }
   // For the Minutes, allow 0 - 5

    else{     
      key_val=keypad.getKey(); 
      if (key_val != NO_KEY && key_val != keys[3][2] && key_val != keys[3][0] && key_val != keys[1][2] 
      && key_val != keys[2][0] && key_val != keys[2][1] && key_val != keys[2][2]){
        count_arr = key_val - 48 ;  // convert from char to int
        
        for ( j; j < wait_key_in; j= j + 1){  
          //pow10 = pow10 * 10;
          pow10 = pow10 / 10;
        }
        current_count = current_count + ((count_arr) * pow10); //* (pow(10,wait_key_in));
      
        wait_key_in = wait_key_in + 1;

        digitalWrite(alarm,1);
        delay(50);   
      }
      else if (key_val == keys[3][2]){
        current_count = 0;
        wait_key_in = 0;
        pow10 = 100;
        //pow10 = 1;
        j=0;
        digitalWrite(alarm,1); 
        delay(50);  
      }
      else if (key_val == keys[3][0]){
        digitalWrite(alarm,1);
        delay(50);
        break;     // This portion to enable downcounting after setting the timer partially

      }
      
    }

    // use the decimal pointer to indicate the digit being changed
    if (wait_key_in == 0){  
      sevseg.setNumber(current_count, 2);
      sevseg.refreshDisplay(); // Must run repeatedly
    }
    if (wait_key_in == 1){  
      sevseg.setNumber(current_count, 1);
      sevseg.refreshDisplay(); // Must run repeatedly
    }
    if (wait_key_in == 2){  
      sevseg.setNumber(current_count, 0);
      sevseg.refreshDisplay(); // Must run repeatedly
    }
  
  }
  if (key_val == keys[3][2]){
      current_count = 0;
      wait_key_in = 0;
      pow10 = 100;
      //pow10 = 1;
      j=0;
      digitalWrite(alarm,1); 
      delay(50); 
    }

  else if (key_val == keys[3][0]){
    
    digitalWrite(alarm,1); 
    delay(50); 
    digitalWrite(alarm,0); 
    time = millis();
    initial = time;        

    while(1){
      delay(1);
      time = millis();
      last = time - initial;      
      sevseg.setNumber(current_count, 2);  
      sevseg.refreshDisplay(); // Must run repeatedly 
      
      key_val=keypad.getKey(); 
      if (last >= 60000){       // Change this value to 60000 for minute count, 1000 for second count
        current_count = current_count - 1;          
        last = 0;
        initial = millis();
      }
      
      else if  (current_count / 100 != 0 && current_count % 100 == 0){//current_count / 100 != 0 &&  ) {
        current_count = current_count - 41;
      }
   

      // Allowing for resetting the counter and enter new values in the middle of opn.
      else if (key_val == keys[3][2]){
        current_count = 0;
        wait_key_in = 0;
        pow10 = 100;
        //pow10 = 1;
        j=0;
        digitalWrite(alarm,1); 
        delay(50); 
        break;
      }

      else if (current_count == 0){
        digitalWrite(alarm,1);        
      }
            

    }
  }

  sevseg.setNumber(current_count, 0);  
  sevseg.refreshDisplay(); // Must run repeatedly
  }


//}


  





