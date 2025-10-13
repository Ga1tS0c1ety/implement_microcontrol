#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

#define MOTORS_MAX_VOLTAGE 9.0f

typedef enum {
    MOTOR_OK = 0,
    MOTOR_ERR_OUT_OF_RANGE = 1,
} motor_error_t;

/**
 * Initialise le module motors.
 * Doit être appelé avant tout autre appel.
 * Configure la couche hardware PWM via hw_pwm_init() (abstraction).
 */
void motors_init(void);

/**
 * Applique une tension (en volts) au moteur gauche.
 * - v : tension souhaitée (ex : 0.0, 5.0, -3.0)
 * Retour :
 *  - MOTOR_OK si la valeur demandée est dans la plage et que la HW accepte la commande
 *  - MOTOR_ERR_OUT_OF_RANGE si v a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t motors_set_voltage_left(float v);

/**
 * Applique une tension (en volts) au moteur droit.
 * Même comportement que motors_set_voltage_left.
 */
motor_error_t motors_set_voltage_right(float v);

/**
 * Arrête les deux moteurs (met duty = 0).
 * Retour : none (opération garantie sauf erreur matérielle interne - loggée).
 */
void motors_stop(void);

/**
 * Récupère la dernière valeur réellement appliquée (après saturation).
 * Renvoie true si des valeurs valides existent.
 */
bool motors_get_last_applied(float *left_v_out, float *right_v_out);

#endif // MOTORS_H
