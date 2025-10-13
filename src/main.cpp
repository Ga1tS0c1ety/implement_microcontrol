#include "Arduino.h"
#include "motors.h"
#include "movement.h"

/* // --- Définition des broches pour les moteurs ---
const int ENB = 8;  // Enable moteur droit (PWM)
const int IN3 = 36;  // Direction moteur droit
const int IN4 = 37;  // Direction moteur droit

const int ENA = 12;   // Enable moteur gauche (PWM)
const int IN1 = 34;   // Direction moteur gauche
const int IN2 = 35;   // Direction moteur gauche
*/

void setup() {
  Serial.begin(115200);
  motors_init();
  Serial.println("Motor TB6612 test ready.");
  Serial.println("Commands: F v / L v / R v / STOP");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) return;
    if (line.equalsIgnoreCase("STOP")) {
      robot_stop();
      Serial.println("OK STOP");
      return;
    }
    //char side; float val;
    Serial.print("DEBUG LINE: '");
    Serial.print(line);
    Serial.println("'");
    // On prend le premier caractère comme side
    char side = line.charAt(0);
    // On prend tout ce qui suit après le premier espace comme valeur
    float val = line.substring(2).toFloat();  // 2 = premier caractère + espace
    motor_error_t e;
    if (side == 'F' || side == 'f') e = robot_move_forward(val);
    else if (side == 'R' || side == 'r') e = robot_turn_right(val);
    else if (side == 'L' || side == 'l') e = robot_turn_left(val);
    else { Serial.println("ERR side"); return; }
    if (e == MOTOR_OK) Serial.println("ACK");
    else if (e == MOTOR_ERR_OUT_OF_RANGE) Serial.println("ACK (sat)");
    else Serial.println("ERR HW");
    float lv, rv; motors_get_last_applied(&lv, &rv);
    Serial.print("Applied L="); Serial.print(lv); Serial.print(" V, R="); Serial.print(rv); Serial.println(" V");
    // } else Serial.println("ERR parse");
  }
}

/*
// --- Fonctions de mouvement ---

void avancer(int vitesse) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
}

void reculer(int vitesse) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
*/
