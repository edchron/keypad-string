#include "KeyPad.h"

const byte ROWS = 4; // rows
const byte COLS = 4; //number of columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};

KeyPad kp = KeyPad(buatKeymap(keys), ROWS, COLS, rowPins, colPins);
//KeyPad kp = KeyPad();

uint8_t bacaString(char *MyStr) {
  uint8_t idx = 0;
  char chr;
  bool str_received = false;
  while (!str_received) {
    unsigned char keypressed = kp.ReadKeypad();
    if (keypressed != 0) {
      chr = keypressed;
      if ( chr == '*' || chr == '#') { //Ending input trigger
        MyStr[idx] = 0 ; //null terminated
        str_received = true;
      }
      else {
        Serial.write(chr);
        *MyStr = chr;
        MyStr++;
      }
    }
  }
  return idx;
}

void setup() {
  char i;
  for (i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  Serial.println("Initialization");
  delay(500);
  Serial.println("Input string with 16 characters maximum");
  Serial.println("Push * or # to show the result");
}

void loop() {
  char myString[16];
  ReadString(myString);
  if (strlen(myString) > 16) {
    Serial.println("");
    Serial.println("More than 16 characters");
    Serial.println("");
  }
  else {
    Serial.println("");
    Serial.print("Result: ");
    Serial.write(myString) ;
    Serial.println("");
    Serial.println("");
  }
}
