#include <stdio.h>
#include <time.h>

//j'ai besoin de fonction de base 
enum mode_voiture{
    STOP,
    FORWARD,
    TURN,
};

#define timeout 50
//config 
#define vitesse_max 52.3
#define voltage_max 9.0
mode_voiture mode=STOP;

float trad_vitesse_volt(float vitesse){
    float voltage=(voltage_max * vitesse) / vitesse_max;
    return voltage;
}


void change_mode(){
    switch (mode)
    {
        case STOP:

        break;

        case FORWARD:

        break;

        case TURN:

        break;
    }
}
