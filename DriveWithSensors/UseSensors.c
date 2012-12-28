// Load our sensor library
#include "Sensor3204.c"
#include "Motor.c"

// not relevant on an Arduino
//int PwmCnt;

/*
* Pin Changes
* Pin 0 and 1 on Arduino cannot be used during testing as they're used for serial comms
*/

/**
 * Does what it says on the tin, sets up the initial state of the system.
 */
void setup()
{
    motor_init();
	
	sense_init();
}

/**
 * Default arduino loop. It's called repeatedly.
 */
void loop()
{
	// Read the sensors
	int sensor_results[4] = {Read_3204(0), Read_3204(1), Read_3204(2), Read_3204(3)};
	// Calculate mean sensor value
	int mean = 0;
	// For every sensor we have...
	for(int i=0; i<=3; i++)
	{
		// ...  add it's value to our mean
		mean += sensor_results[i];
	}
	// now divide our mean up nicely so it's actually the mean!
	mean = mean >> 2; // divides mean by 2^2 (i.e. by 4)
	// Move in the direction of our oddest (furthest from mean) sensor
	int mostOff;
	// just a tmp var
	int offBy;
	for(int i=0;i<=3;i++)
	{
		offBy = sensor_results[i] - mean;
		abs(offBy);
		if(offBy > sensor_results[mostOff])
		{
			mostOff = i;
		}
	}
	// @todo Don't bother with mostOff if it's only a little bit different
	switch(mostOff)
	{
		case 0:
			// move left
			Left();
			break;
		case 1:
			// if closer to sensor 0, move left
			if(abs(mostOff - sensor_results[0]) > abs(mostOff - sensor_results[2]))
			{
				Left();
			}
			// if closer to sensor 2, move forward
			else
			{
				Forward();
			}
			break;
		case 2:
			// if closer to sensor 3, move right
			if(abs(mostOff - sensor_results[3]) > abs(mostOff - sensor_results[1]))
			{
				Right();
			}
			// if closer to sensor 1, move forward
			else
			{
				Forward();
			}
			break;
		case 3:
			// move right
			Right();
			break;
	}
}