#include "Arduino.h"
#include "FastLED.h"
#include "LEDColumn.h"

LEDColumn::LEDColumn(void)
{
}
LEDColumn::LEDColumn(int columnNumber, int columnHeight)
{
    //Starting LED is based off of the # of LEDS in each column and the column posisition
    this->columnNumber = columnNumber;
    this->columnHeight = columnHeight;
    startingLED = columnNumber * columnHeight;
    upsideDown = columnNumber % 2 > 0 ? true : false;
    height = 0;
}
boolean LEDColumn::isUpsideDown()
{
    return upsideDown;
}

int LEDCOLUMN::computeHeight(double FFTData[], FFTSize){
    //loop through the FFT data to get the max data point
    // corresponding to this column's frequency
    double max = 1;
    for(int i = 0; i < FFTSize / 20; i++){
        double currentData = FFTData[(columnNumber * (FFTSize / 20) + i)];
        if(currentReal > max){
            max = currentReal;
        }
    }
    return log(max * max * max);
}
/**
 *  Update the LED's of the column. The height of the column is based off of the FFT_data array that is passed in.
 * 
 */

int LEDColumn::updateColumn(double FFTData[], int FFTSize,  CRGB leds[], int CRGBSize){
    height = computeHeight(FFTSize);
}