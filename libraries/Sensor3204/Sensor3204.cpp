/**
 * @file Sensor3204.cpp
 * @author James Robson
 * @copyright 2012, James Robson
 * @class Sensor3204
 */

#include "Sensor3204.h"

// Code based off of http://playground.arduino.cc/Code/MCP3208

/**
* Sensor Reader
* MCP3204 12-bit 4-channel ADC
*/
// MCP3204.8
#define CS 15
// MCP3204.9
#define DIN 14
// MCP3204.10
#define DOUT 13
// MCP3204.11
#define CLK 12

// list of channels
//const char chans[] = {0xC, 0xD, 0xE, 0xF};


//------------- ADC READ FUNCTION----------------
int Sensor3204::read(int channel)
{
    int adcvalue = 0;
    //command bits - start, mode, chn (3), dont care (3)
    byte commandbits = B11000000;

    //allow channel selection
    commandbits|((channel-1)<<3);
    
    //Select adc
    digitalWrite(CS,LOW);
    int i;
    // setup bits to be written
    for (i=7; i>=3; i--)
    {
        digitalWrite(DOUT,commandbits&1<<i);
        //cycle clock
        digitalWrite(CLK,HIGH);
        digitalWrite(CLK,LOW);    
    }
    
    //ignores 2 null bits
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);
    digitalWrite(CLK,HIGH);  
    digitalWrite(CLK,LOW);
    
    //read bits from adc
    for (i=11; i>=0; i--)
    {
        adcvalue+=digitalRead(DIN)<<i;
        //cycle clock
        digitalWrite(CLK,HIGH);
        digitalWrite(CLK,LOW);
    }
    digitalWrite(CS, HIGH); //turn off device
    return adcvalue;
}

Sensor3204::Sensor3204()
{
    digitalWrite(CS, HIGH);
}