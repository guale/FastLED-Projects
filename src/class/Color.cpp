#include<FastLED.h>
#include "Color.h"

Color::Color() {
	static const uint8_t MIN_VAL = 127;
	static const uint8_t MAX_VAL = 255;



	CHSV start = CHSV(randomHue(), 255, randomVal());
	CHSV target = CHSV(randomHue(), 255, randomVal());
	CHSV current = start;
	CHSV previous = CHSV(0, 0, 0);

	CHSV startH = CHSV(start.h, 0, 0);
	CHSV startV = CHSV(0, 0, start.v);
}

	uint8_t Color::randomHue() {
		return random(0, 255);
	}

	uint8_t Color::randomVal() {
		return random(MIN_VAL, MAX_VAL);
	}