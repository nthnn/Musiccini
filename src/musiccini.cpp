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

#include "musiccini.h"

// Definition of the Musiccini object contructor
void Musiccini::init(int buzzerPin) {
	this->reset();                    // Reset as an object
	this->buzzerPin = buzzerPin;      // Set the buzzer pin

  	pinMode(this->buzzerPin, OUTPUT); // Initialize the buzzer pin as output
}

// Resets the information of Musiccini object
void Musiccini::reset() {
	this->has_stopped = false;
	this->has_started = false;
}

// Plays the defined song once
// The length must be the size of the song[] parameter
void Musiccini::play(int tempo, int song[], size_t length) {
	int wholenote = (60000 * 4) / tempo;
	int gap = 0, duration = 0;

	this->has_stopped = false;
	this->has_started = true;

	for(int current = 0; current < length; current = current + 2) {
		int note = song[current];
		gap = song[current + 1];

		if(this->before_evt != NULL)
			this->before_evt(note);

		if(gap > 0)
			duration = (wholenote) / gap;
		else if(gap < 0) {
			duration = (wholenote) / abs(gap);
			duration *= 1.5;
		}

		tone(this->buzzerPin, note, duration * 0.9);
		delay(duration);
		noTone(this->buzzerPin);

		if(this->after_evt != NULL)
			this->after_evt(note);
	}

	this->has_stopped = true;
}

// Sets the event listener which will be
// fired/called whenever a note was played
void Musiccini::after_note(MusicciniEvent after_evt) {
	this->after_evt = after_evt;
}

// Sets the event listener which will be
// fired/called whenever a note will be played
void Musiccini::before_note(MusicciniEvent before_evt) {
	this->before_evt = before_evt;
}

// Returns true if the song was finished playing
bool Musiccini::was_played() {
	return this->has_started;
}

// Returns true if the song was
// finished playing and has stopped
bool Musiccini::is_done() {
	return this->has_started && this->has_stopped;
}

// Definition end.