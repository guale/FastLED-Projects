#include <Arduino.h>
#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 14
CRGB leds[NUM_LEDS];

const uint8_t BRIGHTNESS = 63; //Scaling factor for the brightness
const uint8_t MIN_VAL = 127; //Defines the minimum value returned by the randomVal function
const uint8_t MAX_VAL = 255; //Defines the maximum value returned by the randomVal function

static uint8_t randomVal() {
	return random(MIN_VAL, MAX_VAL);
}

static uint8_t randomHue() {
	return random(0, 255);
}

//Assigns random starting color and target
CHSV colorStart = CHSV(randomHue(), 255, randomVal());
CHSV colorTarget = CHSV(randomHue(), 255, randomVal());
CHSV colorCurrent = colorStart;
CHSV colorStartH = colorStart;
CHSV colorStartV = colorStart;

CHSV colorPrevious = CHSV(0, 0, 0);

uint8_t blendRateHue = 100;  // How fast to blend hue.
uint8_t blendRateVal = 255;  // How fast to blend value.

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
		if (colorCurrent.h == colorTarget.h) {
			colorStartH.h = colorCurrent.h;
			colorTarget.h = randomHue();
			k = 0;
			// Serial.printf("New colorTarget hue:\t %u\n", colorTarget.h);
		}

		colorCurrent.h = blend(colorStartH, colorTarget, k, FORWARD_HUES).h;

		// Serial.printf("colorCurrent hue:\t%u\tcolorTarget hue\t%u\tk:%u\n", colorCurrent.h, colorTarget.h, k);

		k++;
	}

	//Blends the value independently of the hue
	EVERY_N_MILLISECONDS(blendRateVal) {
		static uint8_t k;
		if (colorCurrent.v == colorTarget.v) {
			colorStartV.v = colorCurrent.v;
			colorTarget.v = random(128, 255);
			k = 0;
			// Serial.printf("New colorTarget val:\t %u\n", colorTarget.v);
		}

		colorCurrent.v = blend(colorStartV, colorTarget, k, SHORTEST_HUES).v;

		// Serial.printf("colorCurrent val:\t%u\tcolorTarget val\t%u\tk:%u\n", colorCurrent.v, colorTarget.v, k);

		k++;
	}


	//Updates LEDs only when color has changed
	if (colorPrevious != colorCurrent) {
		// Serial.println("tick");

		fill_solid(leds, NUM_LEDS, colorCurrent);
		FastLED.show();

		colorPrevious=colorCurrent;
	}
}
