#ifndef SENSOR3204_H

#define SENSOR3204_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
  
int Read_3204(int channel);
void sense_init();
    
    class Sensor3204
    {
        public:
            Sensor3204();
            int read(int channel);
    };

#endif