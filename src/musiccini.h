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

// Musiccini definition starts
#ifndef MUSICCINI_H
#define MUSICCINI_H

#include <Arduino.h>

// Definition for the notes starting
// from 0 to the 8th octave
typedef enum {
	MUSICCINI_NOTE_B0 = 31,
	MUSICCINI_NOTE_C1 = 33,
	MUSICCINI_NOTE_CS1 = 35,
	MUSICCINI_NOTE_D1 = 37,
	MUSICCINI_NOTE_DS1 = 39,
	MUSICCINI_NOTE_E1 = 41,
	MUSICCINI_NOTE_F1 = 44,
	MUSICCINI_NOTE_FS1 = 46,
	MUSICCINI_NOTE_G1 = 49,
	MUSICCINI_NOTE_GS1 = 52,
	MUSICCINI_NOTE_A1 = 55,
	MUSICCINI_NOTE_AS1 = 58,
	MUSICCINI_NOTE_B1 = 62,
	MUSICCINI_NOTE_C2 = 65,
	MUSICCINI_NOTE_CS2 = 69,
	MUSICCINI_NOTE_D2 = 73,
	MUSICCINI_NOTE_DS2 = 78,
	MUSICCINI_NOTE_E2 = 82,
	MUSICCINI_NOTE_F2 = 87,
	MUSICCINI_NOTE_FS2 = 93,
	MUSICCINI_NOTE_G2 = 98,
	MUSICCINI_NOTE_GS2 = 104,
	MUSICCINI_NOTE_A2 = 110,
	MUSICCINI_NOTE_AS2 = 117,
	MUSICCINI_NOTE_B2 = 123,
	MUSICCINI_NOTE_C3 = 131,
	MUSICCINI_NOTE_CS3 = 139,
	MUSICCINI_NOTE_D3 = 147,
	MUSICCINI_NOTE_DS3 = 156,
	MUSICCINI_NOTE_E3 = 165,
	MUSICCINI_NOTE_F3 = 175,
	MUSICCINI_NOTE_FS3 = 185,
	MUSICCINI_NOTE_G3 = 196,
	MUSICCINI_NOTE_GS3 = 208,
	MUSICCINI_NOTE_A3 = 220,
	MUSICCINI_NOTE_AS3 = 233,
	MUSICCINI_NOTE_B3 = 247,
	MUSICCINI_NOTE_C4 = 262,
	MUSICCINI_NOTE_CS4 = 277,
	MUSICCINI_NOTE_D4 = 294,
	MUSICCINI_NOTE_DS4 = 311,
	MUSICCINI_NOTE_E4 = 330,
	MUSICCINI_NOTE_F4 = 349,
	MUSICCINI_NOTE_FS4 = 370,
	MUSICCINI_NOTE_G4 = 392,
	MUSICCINI_NOTE_GS4 = 415,
	MUSICCINI_NOTE_A4 = 440,
	MUSICCINI_NOTE_AS4 = 466,
	MUSICCINI_NOTE_B4 = 494,
	MUSICCINI_NOTE_C5 = 523,
	MUSICCINI_NOTE_CS5 = 554,
	MUSICCINI_NOTE_D5 = 587,
	MUSICCINI_NOTE_DS5 = 622,
	MUSICCINI_NOTE_E5 = 659,
	MUSICCINI_NOTE_F5 = 698,
	MUSICCINI_NOTE_FS5 = 740,
	MUSICCINI_NOTE_G5 = 784,
	MUSICCINI_NOTE_GS5 = 831,
	MUSICCINI_NOTE_A5 = 880,
	MUSICCINI_NOTE_AS5 = 932,
	MUSICCINI_NOTE_B5 = 988,
	MUSICCINI_NOTE_C6 = 1047,
	MUSICCINI_NOTE_CS6 = 1109,
	MUSICCINI_NOTE_D6 = 1175,
	MUSICCINI_NOTE_DS6 = 1245,
	MUSICCINI_NOTE_E6 = 1319,
	MUSICCINI_NOTE_F6 = 1397,
	MUSICCINI_NOTE_FS6 = 1480,
	MUSICCINI_NOTE_G6 = 1568,
	MUSICCINI_NOTE_GS6 = 1661,
	MUSICCINI_NOTE_A6 = 1760,
	MUSICCINI_NOTE_AS6 = 1865,
	MUSICCINI_NOTE_B6 = 1976,
	MUSICCINI_NOTE_C7 = 2093,
	MUSICCINI_NOTE_CS7 = 2217,
	MUSICCINI_NOTE_D7 = 2349,
	MUSICCINI_NOTE_DS7 = 2489,
	MUSICCINI_NOTE_E7 = 2637,
	MUSICCINI_NOTE_F7 = 2794,
	MUSICCINI_NOTE_FS7 = 2960,
	MUSICCINI_NOTE_G7 = 3136,
	MUSICCINI_NOTE_GS7 = 3322,
	MUSICCINI_NOTE_A7 = 3520,
	MUSICCINI_NOTE_AS7 = 3729,
	MUSICCINI_NOTE_B7 = 3951,
	MUSICCINI_NOTE_C8 = 4186,
	MUSICCINI_NOTE_CS8 = 4435,
	MUSICCINI_NOTE_D8 = 4699,
	MUSICCINI_NOTE_DS8 = 4978,
	MUSICCINI_REST = 0
} MusicciniNote;

// Type definition for the Musiccini::after_note
// and Musiccini::before_note function callback
typedef void (*MusicciniEvent)(MusicciniNote);

// Musiccini class definition
// See musiccini.cpp for much more detailed definitions
class Musiccini {
	private:
	int buzzerPin;
	bool has_started, has_stopped;
	MusicciniEvent after_evt, before_evt;

	public:
	void init(int buzzerPin);
	void play(int tempo, int song[], size_t length);
	void reset();
	
	void after_note(MusicciniEvent after_evt);
	void before_note(MusicciniEvent before_evt);

	bool was_played();
	bool is_done();
};

#endif

// Definition end.