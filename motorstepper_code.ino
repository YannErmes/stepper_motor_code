// Définition des broches connectées au module du moteur pas à pas
// Define the pins connected to the stepper motor driver module
int stepperIN1 = 8;   // Bobine A / Coil A
int stepperIN2 = 9;   // Bobine B / Coil B
int stepperIN3 = 10;  // Bobine C / Coil C
int stepperIN4 = 11;  // Bobine D / Coil D

// Définition des boutons de commande de direction
// Define the control buttons for direction
int pinG = 12;  // Bouton pour rotation anti-horaire / Button for counterclockwise rotation
int pinD = 13;  // Bouton pour rotation horaire / Button for clockwise rotation

// Variable pour suivre la position des pas
// Variable to track the step position
int step_num = 0;

// Nombre de pas pour une rotation complète (pour le moteur 28BYJ-48)
// Number of steps per full rotation (for 28BYJ-48 stepper motor)
const int stepsPerRevolution = 2048;

void setup() {
  Serial.begin(9600); // Initialisation de la communication série pour le debug / Initialize serial communication for debugging

  // Configuration des broches du moteur en sortie / Set stepper motor pins as outputs
  pinMode(stepperIN1, OUTPUT);
  pinMode(stepperIN2, OUTPUT);
  pinMode(stepperIN3, OUTPUT);
  pinMode(stepperIN4, OUTPUT);

  // Configuration des boutons en entrée / Set control buttons as inputs
  pinMode(pinD, INPUT);
  pinMode(pinG, INPUT);
}

void loop() {
  delay(2); // Petit délai pour stabiliser la lecture des entrées / Small delay to stabilize input readings

  // Vérification si le bouton gauche (pinG) est pressé / Check if the left button (pinG) is pressed
  if (digitalRead(pinG) == HIGH) {
    stepcontrol(true); // Rotation anti-horaire / Rotate counterclockwise
  }
  // Vérification si le bouton droit (pinD) est pressé / Check if the right button (pinD) is pressed
  else if (digitalRead(pinD) == HIGH) {
    stepcontrol(false); // Rotation horaire / Rotate clockwise
  }
}

// Fonction pour contrôler le mouvement du moteur / Function to control stepper motor movement
void stepcontrol(bool dir) {
  if (dir) {
    // Rotation horaire / Clockwise rotation
    switch (step_num) {
      case 0:
        digitalWrite(stepperIN1, HIGH);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, LOW);
        break;
      case 1:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, HIGH);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, LOW);
        break;
      case 2:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, HIGH);
        digitalWrite(stepperIN4, LOW);
        break;
      case 3:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, HIGH);
        break;
    }
  } else {
    // Rotation anti-horaire / Counterclockwise rotation
    switch (step_num) {
      case 0:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, HIGH);
        break;
      case 1:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, HIGH);
        digitalWrite(stepperIN4, LOW);
        break;
      case 2:
        digitalWrite(stepperIN1, LOW);
        digitalWrite(stepperIN2, HIGH);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, LOW);
        break;
      case 3:
        digitalWrite(stepperIN1, HIGH);
        digitalWrite(stepperIN2, LOW);
        digitalWrite(stepperIN3, LOW);
        digitalWrite(stepperIN4, LOW);
        break;
    }
  }

  // Incrémenter le nombre de pas / Increment step number
  step_num++;

  // Réinitialiser le compteur de pas lorsqu'il atteint 4 / Reset step number when it reaches 4 to loop the sequence
  if (step_num > 3) {
    step_num = 0;
  }
}

/*
Matériel nécessaire / Required Materials:

1. Arduino Uno ou compatible / Arduino Uno or compatible board
2. Moteur pas à pas 28BYJ-48 / 28BYJ-48 stepper motor
3. Module pilote ULN2003 / ULN2003 stepper motor driver module
4. Boutons poussoirs x2 / Push buttons x2
5. Résistances 10kΩ x2 (optionnel pour pull-down) / 10kΩ resistors x2 (optional for pull-down)
6. Câbles de connexion / Jumper wires
7. Alimentation 5V (USB ou externe) / 5V power supply (USB or external)
*/
