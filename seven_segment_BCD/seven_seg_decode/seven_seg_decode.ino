// Using a BCD decoder to generate 7 segment 

int TEST_LED=19;
int BIN_PIN[4]={9,10,11,12};
int DIG_PIN[4] = {5, 6, 7, 8};
int j;
void setup() {
  pinMode(TEST_LED, OUTPUT);
  
  for(j=0;j<4;j=j+1){
    pinMode(BIN_PIN[j], OUTPUT);
    pinMode(DIG_PIN[j], OUTPUT);
  }
  //Serial.begin(9600);  
  
}
void loop() {
  
  //Serial.print(BIN_PIN[0]);
  //delay (5);
  digitalWrite(DIG_PIN[2],1);//BIN_PIN[0],1);
  digitalWrite(TEST_LED,1);//BIN_PIN[0],1);
  digitalWrite(DIG_PIN[3],1);
  ssdisp(9);

}


void ssdisp (int dig_val){
 // int bin_val_array[][4];
  int i;
  int bin_val_array[10][4] = {{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},
  {0,1,1,0},{0,1,1,1},{1,0,0,0},{1,0,0,1}};
  
  for (int i=0;i<4;i=i+1){    
    digitalWrite(BIN_PIN[i],bin_val_array[dig_val][i]);
    delay(4);
  }

}






















//REDUNDANT

/*
//byte numDigits = 4;
  //byte digitPins[] = {2, 3, 4, 5};
  //byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  //bool resistorsOnSegments = 0;
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.


    sevseg.setNumber(5555, 2);
  sevseg.refreshDisplay(); // Must run repeatedly

  */