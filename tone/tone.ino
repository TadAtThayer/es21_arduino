#include <Arduino.h>

// These pin names are all available in the documentation for the Grove board
// we are using
//
// https://wiki.seeedstudio.com/Grove-Beginner-Kit-For-Arduino/
//

int rotaryPin = A0;   //Arduino pin assigned to potentiometer
int rotaryValue = 0;  //variable for storing potentiometer reading

int buzzerPin = 5;

void setup(void) {

  // We are going to read from the rotary sensor
  pinMode(rotaryPin, INPUT);  //setting potentiometer as input

  // We're going to play a tone on the buzzer, so make it an output
  pinMode( buzzerPin, OUTPUT );
}


void loop(void) {

  // Read the position of the rotary sensor
  // This returns a value between 0 (all the way clockwise) and 1023 (all the way counter clockwise)
  rotaryValue = analogRead(rotaryPin);   
  
  // Turn it off below 10.
  if ( rotaryValue < 10 ){
    noTone(buzzerPin);
  } else {
    tone(buzzerPin, rotaryValue);
  }

}
