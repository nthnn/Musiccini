/* Musiccini Example

   The diagram of this project is located at ../example-diagram.png
   This examples showcases the event listeners and the demonstration
   of how this library works in order to play a music.

   The example melody used is based on Tetris background musici MIDI
   file, which I cannot remember where I got it from.
*/

/*
	Copyright © 2022 Nathanne Isip
	Permission is hereby granted, free of charge,
	to any person obtaining a copy of this software
	and associated documentation files (the “Software”),
	to deal in the Software without restriction,
	including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so,
	subject to the following conditions:
	The above copyright notice and this permission notice
	shall be included in all copies or substantial portions
	of the Software.
	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF
	ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

// Include the Musiccini library
#include "musiccini.h"

#define BUZZER 2  // Digital pin for the active/passive buzzer
#define LED_1 3   // Digital pin for LED 1
#define LED_2 4   // Digital pin for LED 2
#define LED_3 5   // Digital pin for LED 3

// Define the song with this array format.
// The note first (defined with the octave number), then the note length
int melody[] = {
  // Segment 1
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_B4, 8, MUSICCINI_NOTE_C5, 8,
  MUSICCINI_NOTE_D5, 4,  MUSICCINI_NOTE_C5, 8, MUSICCINI_NOTE_B4, 8, 
  MUSICCINI_NOTE_A4, 4,  MUSICCINI_NOTE_A4, 8, MUSICCINI_NOTE_C5, 8,
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_D5, 8, MUSICCINI_NOTE_C5, 8, 
  MUSICCINI_NOTE_B4, -4, MUSICCINI_NOTE_C5, 8, MUSICCINI_NOTE_D5, 4,
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_C5, 4, MUSICCINI_NOTE_A4, 4,
  MUSICCINI_NOTE_A4, 8,  MUSICCINI_NOTE_A4, 4, MUSICCINI_NOTE_B4, 8,
  MUSICCINI_NOTE_C5, 8, 

  // Segment 2
  MUSICCINI_NOTE_D5, -4, MUSICCINI_NOTE_F5, 8, MUSICCINI_NOTE_A5, 4,
  MUSICCINI_NOTE_G5, 8,  MUSICCINI_NOTE_F5, 8, MUSICCINI_NOTE_E5, -4,
  MUSICCINI_NOTE_C5, 8,  MUSICCINI_NOTE_E5, 4, MUSICCINI_NOTE_D5, 8,
  MUSICCINI_NOTE_C5, 8,  MUSICCINI_NOTE_B4, 4, MUSICCINI_NOTE_B4, 8,
  MUSICCINI_NOTE_C5, 8,  MUSICCINI_NOTE_D5, 4, MUSICCINI_NOTE_E5, 4, 
  MUSICCINI_NOTE_C5, 4,  MUSICCINI_NOTE_A4, 4, MUSICCINI_NOTE_A4, 4,
  MUSICCINI_REST,    4, 

  // Segment 3
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_B4, 8, MUSICCINI_NOTE_C5, 8,
  MUSICCINI_NOTE_D5, 4,  MUSICCINI_NOTE_C5, 8, MUSICCINI_NOTE_B4, 8, 
  MUSICCINI_NOTE_A4, 4,  MUSICCINI_NOTE_A4, 8, MUSICCINI_NOTE_C5, 8,
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_D5, 8, MUSICCINI_NOTE_C5, 8, 
  MUSICCINI_NOTE_B4, -4, MUSICCINI_NOTE_C5, 8, MUSICCINI_NOTE_D5, 4,
  MUSICCINI_NOTE_E5, 4,  MUSICCINI_NOTE_C5, 4, MUSICCINI_NOTE_A4, 4,
  MUSICCINI_NOTE_A4, 8,  MUSICCINI_NOTE_A4, 4, MUSICCINI_NOTE_B4, 8,
  MUSICCINI_NOTE_C5, 8, 

  // Segment 4
  MUSICCINI_NOTE_D5, -4, MUSICCINI_NOTE_F5, 8, MUSICCINI_NOTE_A5, 4,
  MUSICCINI_NOTE_G5,  8, MUSICCINI_NOTE_F5, 8, MUSICCINI_NOTE_E5, -4,
  MUSICCINI_NOTE_C5,  8, MUSICCINI_NOTE_E5, 4, MUSICCINI_NOTE_D5, 8,
  MUSICCINI_NOTE_C5,  8, MUSICCINI_NOTE_B4, 4, MUSICCINI_NOTE_B4, 8,
  MUSICCINI_NOTE_C5,  8, MUSICCINI_NOTE_D5, 4, MUSICCINI_NOTE_E5, 4, 
  MUSICCINI_NOTE_C5,  4, MUSICCINI_NOTE_A4, 4, MUSICCINI_NOTE_A4, 4,
  MUSICCINI_REST,     4, 

  // Segment 5
  MUSICCINI_NOTE_E5,  2, MUSICCINI_NOTE_C5, 2, 
  MUSICCINI_NOTE_D5,  2, MUSICCINI_NOTE_B4, 2, 
  MUSICCINI_NOTE_C5,  2, MUSICCINI_NOTE_A4, 2, 
  MUSICCINI_NOTE_GS4, 2, MUSICCINI_NOTE_B4, 4,
  MUSICCINI_REST,     8,

  // Segment 6
  MUSICCINI_NOTE_E5, 2, MUSICCINI_NOTE_C5, 2, 
  MUSICCINI_NOTE_D5, 2, MUSICCINI_NOTE_B4, 2, 
  MUSICCINI_NOTE_C5, 4, MUSICCINI_NOTE_E5, 4,
  MUSICCINI_NOTE_A5, 2, 

  // Segment 7
  MUSICCINI_NOTE_GS5, 2, 
};

Musiccini music;  // Create a Musiccini object
int led = 3;      // Define the LED index that must blink
                  // when a note is being played

// This is a function callback which will be executed
// everytime before a note will be played.
void before_note_event(MusicciniNote note) {
  digitalWrite(led, HIGH);  // Turn on the indexed LED

  led++;        // Increment
  // Since we start from pin 3, the pin 5 will be the last pin
  // Thus, we must reset the LED pin number to 3.
  if(led == 6)
    led = 3;
}

// Unlike the before_note_event function, this
// is a function callback which will be executed
// everytime after a note will be played.
void after_note_event(MusicciniNote note) {
  // Turn off all the LEDs
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
}

void setup() {
  // Set-up all the LED pins as output
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  music.init(BUZZER);                   // Initialize the Musiccini object
  music.after_note(after_note_event);   // Set the after note event listener
  music.before_note(before_note_event); // Set the before note event listener
}

// This will play the melody repeatedly and asynchronously
void loop() {
  // The 114 is the BPM or the beats per minute
  // Which the second parameter is the length of the song
  music.play(114, melody, sizeof(melody) / sizeof(melody[0]));
}

// Program end.