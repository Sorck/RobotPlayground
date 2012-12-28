#ifndef MOTOR_H
#define MOTOR_H

void motor_init();

void Quit();
void Forward();
void Left();
void Backward();
void Right();

void Drive(int LeftDirection, int RightDirection);
 
#endif