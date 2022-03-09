#include <Arduino.h>
#include <FastLED.h>
#include "Color.h"
#define DATA_PIN 14

// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 16;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const bool    kMatrixVertical = false;

#define NUM_LEDS (kMatrixWidth*kMatrixHeight)

CRGB leds[NUM_LEDS];

const uint8_t BRIGHTNESS = 63; //Scaling factor for the brightness
const uint8_t BLEND_RATE_HUE = 100;
const uint8_t BLEND_RATE_VAL = 33;

Color color;


void setup() {
	// Serial.begin(9600);
	// delay(1000);
	// Serial.println();
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);

	color.current.h = color.start.h + 36;

}

void loop() {
	EVERY_N_MILLISECONDS(BLEND_RATE_HUE) {
		color.start.h += 1;
		color.current.h += 1;
	}

	EVERY_N_MILLISECONDS(BLEND_RATE_VAL) {
		static uint8_t k;
		if (color.start.v == color.target.v) {
			color.startV.v = color.current.v;
			color.target.v = color.randomVal();
			k = 0;
			Serial.printf("New color.target val:\t %u\n", color.target.v);
		}

		color.current.v = blend(color.startV, color.target, k, SHORTEST_HUES).v;
		color.start.v = color.current.v;

		Serial.printf("color.current val:\t%u\tcolorTarget val\t%u\tk:%u\n", color.current.v, color.target.v, k);

		k++;
	}

	if (color.previous != color.start) {
		// Serial.println("tick");

		fill_gradient(leds, NUM_LEDS, color.start, color.current, FORWARD_HUES);
		FastLED.show();

		color.previous = color.start;
	}

	// fill_gradient(leds, NUM_LEDS, CHSV(0,255,255), CHSV(255,255,255), FORWARD_HUES);
	// FastLED.show();
}