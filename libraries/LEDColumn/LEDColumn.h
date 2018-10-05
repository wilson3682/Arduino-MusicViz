#ifndef LEDColumn_h
#define LEDColumn_h

#include "FastLed.h"
#include "Arduino.h"

class LEDColumn
{
  public:
  /* Constructor */
	  LEDColumn(void);
    LEDColumn(int evenOdd, int startingLED);

    void update column(double *FFT_DATA CRGB *leds);
    boolean isUpsideDown();
  private:
    int startingLED;
    boolean upsideDown;
    int height;
    int _Odd;

    
};

#endif