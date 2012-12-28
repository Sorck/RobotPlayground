// Load our sensor library
#include "Sensor3204.c"

// not relevant on an Arduino
//int PwmCnt;
// The duty on the PWM cycle
int duty;

/*
* Pin Changes
* Pin 0 and 1 on Arduino cannot be used during testing as they're used for serial comms
*/

// Right motor CW
#define RightC 0
// Right motor CCW
#define RightCC 1
// Right motor go
#define RightPwr 2

// Left motor CW
#define LeftC 0
// Left motor CCW
#define LeftCC 1
// Left motor go
#define LeftPwr 2

#define CW 1
#define CCW 0

/**
 * Does what it says on the tin, sets up the initial state of the system.
 */
void setup()
{
    //PWM Vars
	duty = 80;
	//PwmCnt = 0;
	
	// initialise the motor power pins
	Quit();
	
	// Setup the PWM outputs
	analogWrite(RightPwr, 0);
	analogWrite(LeftPwr, 0);
	
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

/**
* void Quit
* Kills the motor power. (H-bridge stopping trick courtesy of Mark)
*/
void Quit()
{
	digitalWrite(RightC, LOW);
	digitalWrite(RightCC, LOW);
	digitalWrite(LeftC, LOW);
	digitalWrite(LeftCC, LOW);
}

/**
* void Forward
* Drives the bot forward.
*/
void Forward()
{
	Drive(CCW, CCW);
}

/**
* void Left
* Drives the bot Left.
*/
void Left()
{
	Drive(CW, CCW);
}

/**
* void Backward
* Drives the bot backward.
*/
void Backward()
{
	Drive(CW, CW);
}

/**
* void Right
* Drives the bot right.
*/
void Right()
{
	Drive(CCW, CW);
}

/**
* Motor Driving functions
*/

/**
* Drive
* @param int LeftDirection CW or CCW for left motor
* @param int RightDirection CW or CCW for right motor
*/
void Drive(int LeftDirection, int RightDirection)
{
	digitalWrite(RightC, RightDirection == CW ? HIGH : LOW);
	digitalWrite(RightCC, RightDirection == CW ? LOW : HIGH);
	
	digitalWrite(LeftC, LeftDirection == CW ? HIGH : LOW);
	digitalWrite(LeftCC, LeftDirection == CW ? LOW : HIGH);
	
	//PWM Vars
	duty = 80;

	analogWrite(RightPwr, duty);
	analogWrite(LeftPwr, duty);
	//DriveRLoop();
	//DriveLLoop();
}

/*void DriveRLoop()
{
	PwmCnt = 0;
	while(PwmCnt <= 20)
	{
		PwmCnt ++;
		// @todo PWM RightPwr, duty
		analogWrite(RightPwr, duty);
	}
}

// do the pwm on the left motor
void DriveLLoop()
{
	PwmCnt = 0;
	while(PwmCnt <= 20)
	{
		PwmCnt ++;
		// @todo PWM LeftPwr, duty
	}
}*/