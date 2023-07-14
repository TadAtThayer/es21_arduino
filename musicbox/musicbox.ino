// Define the pitch for the notes
#include "music.h"

//including the libraries
#include <Arduino.h>
#include <U8x8lib.h>

// This allows us to write to the small OLED display
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);

// These pin names are all available in the documentation for the Grove board
// we are using
//
// https://wiki.seeedstudio.com/Grove-Beginner-Kit-For-Arduino/
//

int rotaryPin = A0;   //Arduino pin assigned to potentiometer
int rotaryValue = 0;  //variable for storing potentiometer reading

const int buttonPin = 6;  //Arduino pin assinged to button
int buttonState = 0;      //variable for storing button state

int tonepin = 5;  // Arduino pin assigned to Buzzer
int frequency;    // variable for storing the frequency


//The melody of song 1
int tune1[] = {
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5,
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
};

//The duration of each note in tune1
float durt1[] = {
  0.5, 0.5, 0.5, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1, 1

};

//The melody of song 2
int tune2[] = {
  NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_A3,
  NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_CS4, NOTE_B3,
  NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_A3,
  NOTE_A3, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_FS4,
  NOTE_FS4, NOTE_E4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_A4, NOTE_FS4,
  NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_A3, NOTE_A3, NOTE_E4, NOTE_D4, NOTE_FS4, NOTE_G4,
  NOTE_FS4, NOTE_E4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_C4, NOTE_D4,
  NOTE_E4, NOTE_A3, NOTE_A3, NOTE_E4, NOTE_D4
};

//The duration of each note in song 2
float durt2[] = {
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  1,
  1 + 1,
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  1,
  1,
  0.5,
  1,
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  0.5,
  1,
  0.5,
  0.5,
  1,
  1,
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  1,
  1 + 0.5,
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  0.5,
  1,
  0.5,
  1,
  0.25,
  0.25,
  0.25,
  0.25,
  1,
  0.5,
  1,
  0.5,
  1,
  1,
  1 + 0.5,
};

//The melody of song 3
int tune3[] = {
  NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_G4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_C4
};

//The duration of each note in song 3
float durt3[] = {
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1,
  0.5, 0.5, 1, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 0.5, 1
};

void setup(void) {

  // We are going to read from the rotary sensor and the button
  pinMode(rotaryPin, INPUT);  //setting potentiometer as input
  pinMode(buttonPin, INPUT);  //setting button as input

  // We're going to send "music" out of the buzzer
  pinMode(tonepin, OUTPUT);  //setting buzzer as output

  // set up the OLED display
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}


void loop(void) {

  // Read the position of the rotary sensor
  rotaryValue = analogRead(rotaryPin);   //reads the value from the potentiometer (it maps input voltages between 0 5V into integer values between 0 and 1023)
  buttonState = digitalRead(buttonPin);  // reads the value from the button, either HIGH or LOW

  u8x8.setCursor(0, 0);

  u8x8.print("      ");
  u8x8.println(rotaryValue);

  //Set arbitrary ranges for each song to play
  //using if-else statements
  if (rotaryValue > 100 && rotaryValue < 200) {
    u8x8.println("In range - 1   ");
    int length = sizeof(tune1) / sizeof(tune1[0]);

    if (buttonState == HIGH) {
      for (int x = 0; x < length; x++) {
        tone(tonepin, tune1[x]);
        delay(400 * durt1[x]);
        delay(100 * durt1[x]);
        noTone(tonepin);
      }
      delay(4000);
    }

  } else if (rotaryValue > 400 && rotaryValue < 500) {
    int length = sizeof(tune2) / sizeof(tune2[0]);
    u8x8.println("In range - 2  ");
    if (buttonState == HIGH) {
      for (int x = 0; x < length; x++) {
        tone(tonepin, tune2[x]);
        delay(400 * durt2[x]);
        delay(100 * durt2[x]);
        noTone(tonepin);
      }
    }
  } else if (rotaryValue > 780 && rotaryValue < 880) {
    u8x8.println("In range - 3   ");
    int length = sizeof(tune3) / sizeof(tune3[0]);

    if (buttonState == HIGH) {
      for (int x = 0; x < length; x++) {
        tone(tonepin, tune3[x]);
        delay(400 * durt3[x]);
        delay(100 * durt3[x]);
        noTone(tonepin);
      }
    }
  } else {
    u8x8.print("Out of range.");
  }
}
