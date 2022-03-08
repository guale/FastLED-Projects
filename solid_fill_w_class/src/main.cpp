#include <Arduino.h>
#include <FastLED.h>
#include "Color.h"
#define NUM_LEDS 64
#define DATA_PIN 14
CRGB leds[NUM_LEDS];

const uint8_t BRIGHTNESS = 63; //Scaling factor for the brightness

const uint8_t BLEND_RATE_HUE = 50;  // How fast to blend hue.
const uint8_t BLEND_RATE_VAL = 33;  // How fast to blend value.

Color color;

void setup() {
	// Serial.begin(9600);
	// delay(1000);
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);

	// Serial.println("");
	// Serial.printf("Start color:\t%u,%u,%u\n", color.start.h, color.start.s, color.start.v);

	// Serial.printf("New color.target hue:\t %u\n", color.target.h);
	// Serial.printf("New color.target val:\t %u\n", color.target.v);
}

void loop() {
	EVERY_N_MILLISECONDS(BLEND_RATE_HUE) {
		static uint8_t k;
		if (color.current.h == color.target.h) {
			color.startH.h = color.current.h;
			color.target.h = color.randomHue();
			k = 0;
			Serial.printf("New color.target hue:\t %u\n", color.target.h);
		}

		color.current.h = blend(color.startH, color.target, k, FORWARD_HUES).h;

		Serial.printf("color.current hue:\t%u\tcolorTarget hue\t%u\tk:%u\n", color.current.h, color.target.h, k);

		k++;
	}

	//Blends the value independently of the hue
	EVERY_N_MILLISECONDS(BLEND_RATE_VAL) {
		static uint8_t k;
		if (color.current.v == color.target.v) {
			color.startV.v = color.current.v;
			color.target.v = color.randomVal();
			k = 0;
			Serial.printf("New color.target val:\t %u\n", color.target.v);
		}

		color.current.v = blend(color.startV, color.target, k, SHORTEST_HUES).v;

		Serial.printf("color.current val:\t%u\tcolorTarget val\t%u\tk:%u\n", color.current.v, color.target.v, k);

		k++;
	}


	//Updates LEDs only when color has changed
	if (color.previous != color.current) {
		// Serial.println("tick");

		fill_solid(leds, NUM_LEDS, color.current);
		FastLED.show();

		color.previous = color.current;
	}
}
