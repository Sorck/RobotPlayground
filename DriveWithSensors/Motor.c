void motor_init()
{
    //PWM Vars
    duty = 80;
	//PwmCnt = 0;
	
	// initialise the motor power pins
	Quit();
	
	// Setup the PWM outputs
	analogWrite(RightPwr, 0);
	analogWrite(LeftPwr, 0);
}

// The duty on the PWM cycle
int duty;

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