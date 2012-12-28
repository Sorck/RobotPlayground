/**
 * @file Sensor3204.h
 * @author James Robson
 * @copyright 2012, James Robson
 * @class Sensor3204
 */

// inclusion guard
#ifndef SENSOR3204_H

#define SENSOR3204_H

// Someone decided they'd rename the Arduiono header files so we need some conditional directives.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Sensor3204
{
    public:
        Sensor3204();
        int read(int channel);
};

#endif