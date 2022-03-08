#include<FastLED.h>
#include<Arduino.h>
#include "Color.h"


//Declares the variables necessary to cycle colors
CHSV start;
CHSV target;
CHSV current;
CHSV previous;

//These variables are used to blend the hue and value independently.
CHSV startV;
CHSV startH;


uint8_t Color::randomHue() {
	return random(0, 255);
}

uint8_t Color::randomVal() {
	return random(MIN_VAL, MAX_VAL);
}

Color::Color() {

	//Start and target are initialized randomly
	start = CHSV(randomHue(), 255, randomVal());
	target = CHSV(randomHue(), 255, randomVal());
	current = start;
	//Used to decide whether or not to update the LEDs
	previous = CHSV(0, 0, 0);

	startH = CHSV(start.h, 0, 0);
	startV = CHSV(0, 0, start.v);
}