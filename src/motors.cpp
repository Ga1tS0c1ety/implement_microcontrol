#include "motors.h"

#ifndef LEFT_BI1_PIN
  #define LEFT_BI1_PIN 37
#endif
#ifndef LEFT_BI2_PIN
  #define LEFT_BI2_PIN 36
#endif
#ifndef LEFT_PWMB
  #define LEFT_PWMB_PIN 8
#endif

#ifndef RIGHT_BI1_PIN
  #define RIGHT_BI1_PIN 34
#endif
#ifndef RIGHT_BI2_PIN
  #define RIGHT_BI2_PIN 35
#endif
#ifndef RIGHT_PWMB
  #define RIGHT_PWMB_PIN 12
#endif

static float last_left_v = 0.0f;
static float last_right_v = 0.0f;
static bool initialized = false;

static float saturate_voltage(float v) {
  if (v > MOTORS_MAX_VOLTAGE) return MOTORS_MAX_VOLTAGE;
  if (v < -MOTORS_MAX_VOLTAGE) return -MOTORS_MAX_VOLTAGE;
  return v;
}

static uint8_t voltage_to_pwm(float mag_v) {
  if (mag_v < 0.0f) mag_v = 0.0f;
  if (mag_v > MOTORS_MAX_VOLTAGE) mag_v = MOTORS_MAX_VOLTAGE;
  float ratio = mag_v / MOTORS_MAX_VOLTAGE;
  uint8_t pwm = (uint8_t)roundf(ratio * 255.0f);
  return pwm;
}

void motors_init(void) {
  if (initialized) return;

  pinMode(LEFT_BI1_PIN, OUTPUT);
  pinMode(LEFT_BI2_PIN, OUTPUT);
  pinMode(LEFT_PWMB_PIN, OUTPUT);
  pinMode(RIGHT_BI1_PIN, OUTPUT);
  pinMode(RIGHT_BI2_PIN, OUTPUT);
  pinMode(RIGHT_PWMB_PIN, OUTPUT);

  digitalWrite(LEFT_BI1_PIN, LOW);
  digitalWrite(LEFT_BI2_PIN, LOW);
  analogWrite(LEFT_PWMB_PIN, 0);
  digitalWrite(RIGHT_BI1_PIN, LOW);
  digitalWrite(RIGHT_BI2_PIN, LOW);
  analogWrite(RIGHT_PWMB_PIN, 0);

  last_left_v = 0.0f;
  last_right_v = 0.0f;
  initialized = true;
}

static motor_error_t motors_set_voltage_generic(
    float v, 
    uint8_t bi1_pin,
    uint8_t bi2_pin,
    uint8_t pwmb_pin,
    float *last_v_out
) {
  if (!initialized) motors_init();
  float sat = saturate_voltage(v);
  bool out_of_range = (sat != v);

  
  bool forward = (sat >= 0.0f);
  float mag = forward ? sat : -sat;

  uint8_t pwm = voltage_to_pwm(mag);

  
  analogWrite(pwmb_pin, 0);
  
  if (mag == 0.0f) {
    digitalWrite(bi1_pin, LOW);
    digitalWrite(bi2_pin, LOW);
  } else {
    if (forward) {
      digitalWrite(bi1_pin, HIGH);
      digitalWrite(bi2_pin, LOW);
    } else {
      digitalWrite(bi1_pin, LOW);
      digitalWrite(bi2_pin, HIGH);
    }
  }

  analogWrite(pwmb_pin, pwm);

  if (last_v_out) *last_v_out = forward ? mag : -mag;
  if (out_of_range) return MOTOR_ERR_OUT_OF_RANGE;
  return MOTOR_OK;
}

motor_error_t motors_set_voltage_left(float v) {
  return motors_set_voltage_generic(v, LEFT_BI2_PIN, LEFT_BI1_PIN, LEFT_PWMB_PIN, &last_left_v);
}

motor_error_t motors_set_voltage_right(float v) {
  return motors_set_voltage_generic(v, RIGHT_BI1_PIN, RIGHT_BI2_PIN, RIGHT_PWMB_PIN, &last_right_v);
}

void motors_stop(void) {
  if (!initialized) motors_init();

  analogWrite(LEFT_PWMB_PIN, 0);
  analogWrite(RIGHT_PWMB_PIN, 0);
  digitalWrite(LEFT_BI1_PIN, LOW);
  digitalWrite(LEFT_BI2_PIN, LOW);
  digitalWrite(RIGHT_BI1_PIN, LOW);
  digitalWrite(RIGHT_BI2_PIN, LOW);
  last_left_v = last_right_v = 0.0f;
}

bool motors_get_last_applied(float *left_v_out, float *right_v_out) {
  if (!initialized) return false;
  if (left_v_out) *left_v_out = last_left_v;
  if (right_v_out) *right_v_out = last_right_v;
  return true;
}
