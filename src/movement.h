#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "motors.h"

/**
 * Applie une commande de mouvement aux deux moteurs.
 * Pour avancer, v doit être positif.
 * Pour reculer, v doit être négatif.
 * @dev Appelle motors_set_voltage_right avec la valeur v.
 * @dev Appelle motors_set_voltage_left avec la valeur v.
 * @param v Vitesse linéaire désirée en volts (même pour les deux moteurs).
 * @return Code d'erreur moteur :
 *  - MOTOR_OK si les valeurs demandées sont dans la plage de voltage autorisée.
 * - MOTOR_ERR_OUT_OF_RANGE si une des valeurs a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t robot_move_forward(float v);

/**
 * Applie une commande de rotation vers la gauche.
 * Le moteur gauche recule, le moteur droit avance.
 * @dev Appelle motors_set_voltage_right avec la valeur v.
 * @dev Appelle motors_set_voltage_left avec la valeur -v.
 * @param v Vitesse angulaire désirée en volts.
 * @return Code d'erreur moteur :  
 * - MOTOR_OK si la valeur demandée est dans la plage de voltage autorisée.
 * - MOTOR_ERR_OUT_OF_RANGE si la valeur a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t robot_turn_left(float v);

/**
 * Applie une commande de rotation vers la droite.
 * Le moteur droit avance, le moteur gauche recule.
 * @dev Appelle motors_set_voltage_right avec la valeur v.
 * @dev Appelle motors_set_voltage_left avec la valeur -v.
 * @param v Vitesse angulaire désirée en volts.
 * @return Code d'erreur moteur :  
 * - MOTOR_OK si la valeur demandée est dans la plage de voltage autorisée.
 * - MOTOR_ERR_OUT_OF_RANGE si la valeur a été hors plage (mais la valeur saturée a été appliquée)
 */
motor_error_t robot_turn_right(float v);

/**
 * Arrête les deux moteurs.
 * Met le voltage des deux moteurs à 0V
 * @dev Appelle motors_stop().
 */
void robot_stop();

#endif