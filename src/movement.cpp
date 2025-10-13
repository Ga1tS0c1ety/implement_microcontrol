#include "motors.h"

motor_error_t robot_move_forward(float v) {
    motor_error_t err_left = motors_set_voltage_left(v);
    motor_error_t err_right = motors_set_voltage_right(v);
    if (err_left != MOTOR_OK) return err_left;
    if (err_right != MOTOR_OK) return err_right;
    return MOTOR_OK;
}

motor_error_t robot_turn_left(float v) {
    motor_error_t err_left = motors_set_voltage_left(-v);
    motor_error_t err_right = motors_set_voltage_right(v);
    if (err_left != MOTOR_OK) return err_left;
    if (err_right != MOTOR_OK) return err_right;
    return MOTOR_OK;
}

motor_error_t robot_turn_right(float v) {
    motor_error_t err_left = motors_set_voltage_left(v);
    motor_error_t err_right = motors_set_voltage_right(-v);
    if (err_left != MOTOR_OK) return err_left;
    if (err_right != MOTOR_OK) return err_right;
    return MOTOR_OK;
}

void robot_stop() {
    motors_stop();
}