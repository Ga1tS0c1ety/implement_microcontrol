
enum mode_voiture{
    INIT,
    STOP,
    FORWARD,
    TURN,
};

#define timeout 50
//parametre du motteur
#define vitesse_max 52.3
#define voltage_max 9.0

//define motteur 
#pragma region 
typedef struct {
  motor_state_t * motor_left;
  motor_state_t * motor_right;
} motors_module_t;

typedef struct {
  const motor_pins_t * pinMoteur;
  float last_applied_voltage;
  bool initialized;
} motor_state_t;

// Struct à initialiser lors du setup
typedef struct {
  uint8_t bi1_pin;
  uint8_t bi2_pin;
  uint8_t pwmb_pin;
} motor_pins_t;

#pragma endregion
