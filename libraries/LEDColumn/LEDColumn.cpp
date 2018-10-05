#include "Arduino.h"
#include "FastLED.h"
#include "LEDColumn.h"

LEDColumn::LEDColumn(void)
{
}
LEDColumn::LEDColumn(int evenOdd)
{
    upsideDown = evenOdd > 0 ? true : false;
    height = 0;
}
boolean LEDColumn::isUpsideDown()
{
    return (_Odd == 1);
}
// return the height

/**
 * calculate the new height of the columns based on whether it is incremented or decremented
 * return 1 if the height is incremented, -1 if it is decremented, or 0 if it stays the same
 */

int LEDColumn::computeHeight(double *FFT_data, CRGB *leds)
{
    //get the 

}