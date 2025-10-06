#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// --- Définition des broches pour les moteurs ---
const int ENA = 9;   // Enable moteur gauche (PWM)
const int IN1 = 8;   // Direction moteur gauche
const int IN2 = 7;   // Direction moteur gauche

const int ENB = 10;  // Enable moteur droit (PWM)
const int IN3 = 12;  // Direction moteur droit
const int IN4 = 11;  // Direction moteur droit

// --- Prototypes des fonctions ---
void avancer(int vitesse);
void reculer(int vitesse);
void stopRobot();

void setup() {
  // Initialisation des broches
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Démarre avec les moteurs arrêtés
  stopRobot();
}

void loop() {
  // Fait avancer le robot pendant 3 secondes
  avancer(200);
  delay(3000);

  // Stoppe le robot 1 seconde
  stopRobot();
  delay(1000);

  // Fait reculer le robot pendant 3 secondes
  reculer(200);
  delay(3000);

  // Stoppe de nouveau 2 secondes
  stopRobot();
  delay(2000);
}

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

