#include <stdio.h>
#include <time.h>
#include "application.hpp"

mode_voiture mode=INIT;

// Moteur gauche
#ifndef LEFT_BI1_PIN
  #define LEFT_BI1_PIN 37
#endif
#ifndef LEFT_BI2_PIN
  #define LEFT_BI2_PIN 36
#endif
#ifndef LEFT_PWMB
  #define LEFT_PWMB_PIN 8
#endif

//Moteur droit
#ifndef RIGHT_BI1_PIN
  #define RIGHT_BI1_PIN 34
#endif
#ifndef RIGHT_BI2_PIN
  #define RIGHT_BI2_PIN 35
#endif
#ifndef RIGHT_PWMB
  #define RIGHT_PWMB_PIN 12
#endif


float trad_vitesse_volt(float vitesse){
    float voltage=(voltage_max * vitesse) / vitesse_max;
    return voltage;
}

motors_module_t initial_moteur(){
    motor_state_t moteur_droit;
    motor_pins_t pin_moteur_right={
        bi1_pin=RIGHT_BI1_PIN,
        bi2_pin=RIGHT_BI2_PIN,
        pwmb_pin=RIGHT_PWMB_PIN,
    };
    moteur_droit={
        pinMoteur=pin_moteur_right,
        last_applied_voltage=0,
        initialized=false,
    };
    motor_pins_t pin_moteur_left={
        bi1_pin=LEFT_BI1_PIN,
        bi2_pin=LEFT_BI2_PIN,
        pwmb_pin=LEFT_PWMB_PIN,
    };
    motor_state_t moteur_gauche={
        pinMoteur=pin_moteur_left,
        last_applied_voltage=0,
        initialized=false,
    };
    motors_module_t moteur_module={
        motor_left=moteur_gauche,
        motor_right=moteur_droit,
    };
    return moteur_module;
}


void change_mode(){
    switch (mode)
    {
        case INIT:
        initial_moteur();
        break;
        case STOP:

        break;

        case FORWARD:

        break;

        case TURN:

        break;
    }
}
