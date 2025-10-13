#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "motors.h"

motor_error_t robot_move_forward(float v);
motor_error_t robot_turn_left(float v);
motor_error_t robot_turn_right(float v);
void robot_stop();

#endif