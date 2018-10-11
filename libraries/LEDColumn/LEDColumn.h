#ifndef LEDColumn_h
#define LEDColumn_h

#include "FastLed.h"
#include "Arduino.h"

class LEDColumn
{
  public:
  /* Constructor */
	  LEDColumn(void);
    LEDColumn(int columnNumber);

    void updateColumn(double *FFT_DATA, CRGB *leds);
    boolean isUpsideDown();
  private:
    int columnHeight;
    int computeHeight(double *FFT_DATA);
    int columnNumber;
    int startingLED;
    boolean upsideDown;
    int height;
    
};

#endif