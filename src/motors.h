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
 * Doit être appelé avant tout autre appel moteur.
 * Permet de configurer les pins de contrôle des moteurs.
 */
void motors_init(void);

/**
 * Applique une tension (en volts) au moteur gauche.
 * @param v Tension désirée en volts (peut être négative pour marche arrière).
 * @return Code d'erreur moteur :
 *  - MOTOR_OK si la valeur demandée est dans la plage de voltage autorisée.
 *  - MOTOR_ERR_OUT_OF_RANGE si v a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t motors_set_voltage_left(float v);

/**
 * Applique une tension (en volts) au moteur droit.
 * @param v Tension désirée en volts (peut être négative pour marche arrière).
 * @return Code d'erreur moteur :
 *  - MOTOR_OK si la valeur demandée est dans la plage de voltage autorisée.
 *  - MOTOR_ERR_OUT_OF_RANGE si v a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t motors_set_voltage_right(float v);

/**
 * Arrête les deux moteurs.
 * Met le voltage des deux moteurs à 0V
 */
void motors_stop(void);

/**
 * Récupère la dernière valeur réellement appliquée (après saturation).
 * Renvoie true si des valeurs valides existent.
 * @param left_v_out Pointeur pour stocker la dernière tension appliquée au moteur gauche (peut être NULL).
 * @param right_v_out Pointeur pour stocker la dernière tension appliquée au moteur droit (peut être NULL).
 * @return true si les valeurs sont valides, false si le module n'a pas été initialisé.
 */
bool motors_get_last_applied(float *left_v_out, float *right_v_out);

#endif
