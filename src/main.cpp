#include <Arduino.h>
#include <FastLED.h>
#include <./class/Color.h>
#define NUM_LEDS 64
#define DATA_PIN 14
CRGB leds[NUM_LEDS];

const uint8_t BRIGHTNESS = 63; //Scaling factor for the brightness
const uint8_t MIN_VAL = 127; //Defines the minimum value returned by the randomVal function
const uint8_t MAX_VAL = 255; //Defines the maximum value returned by the randomVal function

// static uint8_t randomVal() {
// 	return random(MIN_VAL, MAX_VAL);
// }

// static uint8_t randomHue() {
// 	return random(0, 255);
// }

//Assigns random starting color and target
// CHSV colorStart = CHSV(randomHue(), 255, randomVal());
// CHSV colorTarget = CHSV(randomHue(), 255, randomVal());
// CHSV colorCurrent = colorStart;
// CHSV colorStartH = colorStart;
// CHSV colorStartV = colorStart;

// CHSV colorPrevious = CHSV(0, 0, 0);

uint8_t blendRateHue = 100;  // How fast to blend hue.
uint8_t blendRateVal = 255;  // How fast to blend value.

Color color;

void setup() {
	// Serial.begin(9600);
	// delay(1000);
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);

	// Serial.printf("New colorTarget hue:\t %u\n", colorTarget.h);
	// Serial.printf("New colorTarget val:\t %u\n", colorTarget.v);
}

void loop() {
	EVERY_N_MILLISECONDS(blendRateHue) {
		static uint8_t k;
		if (color.current.h == color.target.h) {
			color.start.h = color.current.h;
			color.target.h = color.randomHue();
			k = 0;
			// Serial.printf("New colorTarget hue:\t %u\n", colorTarget.h);
		}

		color.current.h = blend(color.startH, color.target, k, FORWARD_HUES).h;

		// Serial.printf("colorCurrent hue:\t%u\tcolorTarget hue\t%u\tk:%u\n", colorCurrent.h, colorTarget.h, k);

		k++;
	}

	//Blends the value independently of the hue
	EVERY_N_MILLISECONDS(blendRateVal) {
		static uint8_t k;
		if (color.current.v == color.target.v) {
			color.startV.v = color.current.v;
			color.target.v = random(128, 255);
			k = 0;
			// Serial.printf("New colorTarget val:\t %u\n", colorTarget.v);
		}

		color.current.v = blend(color.startV, color.target, k, SHORTEST_HUES).v;

		// Serial.printf("colorCurrent val:\t%u\tcolorTarget val\t%u\tk:%u\n", colorCurrent.v, colorTarget.v, k);

		k++;
	}


	//Updates LEDs only when color has changed
	if (color.previous != color.current) {
		// Serial.println("tick");

		fill_solid(leds, NUM_LEDS, color.current);
		FastLED.show();

		color.previous=color.current;
	}
}
