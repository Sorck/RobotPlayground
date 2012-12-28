#include "QMotor.h"

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

// Makes it easier to code CW and CCW movement
#define CW 1
#define CCW 0

QMotor::QMotor(int duty)
{
    // private duty variable
    _duty = duty;
    
    // initialise the motor power pins
    Quit();
    
    // Setup PWM outputs
    analogWrite(RightPwr, 0);
    analogWrite(LeftPwr, 0);
}


/**
* void Quit
* Kills the motor power. (H-bridge stopping trick)
*/
void QMotor::Quit()
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
void QMotor::Forward()
{
	Drive(CCW, CCW);
}

/**
* void Left
* Drives the bot Left. (on the spot rotation)
*/
void QMotor::Left()
{
	Drive(CW, CCW);
}

/**
* void Backward
* Drives the bot backward.
*/
void QMotor::Backward()
{
	Drive(CW, CW);
}

/**
* void Right
* Drives the bot right. (on the spot rotation)
*/
void QMotor::Right()
{
	Drive(CCW, CW);
}

/**
* void Drive
* @param int LeftDirection CW or CCW for left motor
* @param int RightDirection CW or CCW for right motor
*/
void QMotor::Drive(int LeftDirection, int RightDirection)
{
    // Drive the Right Wheel
	digitalWrite(RightC, RightDirection == CW ? HIGH : LOW);
	digitalWrite(RightCC, RightDirection == CW ? LOW : HIGH);
	
    // Drive the Left Wheel
	digitalWrite(LeftC, LeftDirection == CW ? HIGH : LOW);
	digitalWrite(LeftCC, LeftDirection == CW ? LOW : HIGH);

    // Send power to the wheels
	analogWrite(RightPwr, _duty);
	analogWrite(LeftPwr, _duty);
}