#ifndef COLOR_H
#define COLOR_H

#include<Arduino.h>
#include<FastLED.h>

class Color {
private:
	static const uint8_t MIN_VAL=127; //Defines the minimum value returned by the randomVal function
	static const uint8_t MAX_VAL=255; //Defines the maximum value returned by the randomVal function

public:

	Color();
	CHSV start;
	CHSV target;
	CHSV startH;
	CHSV startV;
	CHSV current;
	CHSV previous;

	uint8_t randomHue();
	uint8_t randomVal();
};

#endif