/**
 * @file QMotor.h
 * @author James Robson
 * @copyright 2012, James Robson
 * @class QMotor
 */

// Inclusion guard.
#ifndef QMOTOR_H
#define QMOTOR_H

// Two different versions of Arduino IDE need to be tested for...
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class QMotor
{
    public:
        QMotor(int duty);
        void Quit();
        void Forward();
        void Left();
        void Backward();
        void Right();
        void Drive(int LeftDirection, int RightDirection);
    private:
        int _duty;
};

#endif