include <arduinoFFT.h>
#include <math.h>
#include <FastLED.h>
#include <LEDColumn.h>

#define SAMPLES 32
#define SAMPLING_FREQUENCY 10000
#define DATAPIN1 43
#define DATAPIN2 53
#define NUM_LEDS 300
#define AIN A7

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];
LEDColumn LEDColumns1[10];
LEDColumn LEDColumns2[10];
void setup()
{
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  FastLED.addLeds<NEOPIXEL, DATAPIN1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATAPIN2>(leds2, NUM_LEDS);

  //sets up each LED Column
  for (int i = 0; i < 10; i++)
  {
    int evenOdd = (i % 2);
    LEDColumns1[i] = *(new LEDColumn(evenOdd));
    LEDColumns2[i] = *(new LEDColumn(evenOdd));
  }
  //make the bottom of every column light up
  for (int i = 0; i < 10; i++) {
    if (LEDColumns1[i].isUpsideDown()) {
      leds1[((30 * i) + 29)] = CRGB(0, 0, 100);
      leds2[((30 * i) + 29)] = CRGB(0, 0, 100);
    } else {
      leds1[(30 * i)] = CRGB(0, 0, 100);
      leds2[(30 * i)] = CRGB(0, 0, 100);
    }
  }
   FastLED.show();
}

void loop()
{
  /*SAMPLING*/
  for (int i = 0; i < SAMPLES; i++)
  {
    microseconds = micros();    //Overflows after around 70 minutes!

    vReal[i] = analogRead(AIN);
    vImag[i] = 0;

    while (micros() < (microseconds + sampling_period_us)) {
    }
  }
  /*FFT*/
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  //get the max value of the magnitude and pass it to LEDColumn to compute
  for (int i = 0; i < 20; i++) {
    double max = 0;
    for (int j = 0; j < (SAMPLES / 20); j++) {
      double currentReal = vReal[((SAMPLES / 20) * i + j)];

      if (currentReal > max) {
        max = currentReal;
      }
    }
    double computedMax = log(max * max * max);
    if (i < 10) {
      //the height of the LED columns must have increased
      if (LEDColumns1[i].computeHeight(computedMax) > 0) {

        if (LEDColumns1[i].isUpsideDown()) {
          leds1[(30 * i) + 29 - LEDColumns1[i].getHeight()] = CRGB(0, 0, 100);

        } else {
          leds1[(30 * i) + LEDColumns1[i].getHeight()] = CRGB(0, 0, 100);
        }
      } else {
        if (LEDColumns1[i].isUpsideDown()) {
          leds1[(30 * i) + 29 - LEDColumns1[i].getHeight() - 1] = CRGB::Black;
        } else {
          leds1[(30 * i) + LEDColumns1[i].getHeight() + 1] = CRGB::Black;
        }
      }
      FastLED.show();
    } else {
      if (LEDColumns2[i - 10].computeHeight(computedMax) > 0) {

        if (LEDColumns2[i - 10].isUpsideDown()) {
          leds2[(30 * (i - 10)) + 29 - LEDColumns2[i - 10].getHeight()] = CRGB(0, 0, 100);

        } else {
          leds2[(30 * (i - 10)) + LEDColumns2[i - 10].getHeight()] = CRGB(0, 0, 100);
        }
      } else {
        if (LEDColumns2[i - 10].isUpsideDown()) {
          leds2[(30 * (i - 10)) + 29 - LEDColumns2[i - 10].getHeight() - 1] = CRGB::Black;
        } else {
          leds2[(30 * (i - 10)) + LEDColumns2[i - 10].getHeight() + 1] = CRGB::Black;
        }
      }
      FastLED.show();
    }

  }
}
