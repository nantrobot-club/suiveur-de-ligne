// On définit les pins utilisés pour les entrées et sorties

// Pin pour la vitesse du moteur
int pin_moteur = 11;
// Pins pour le sens de rotation du moteur
int pin_sens_1 = 10;
int pin_sens_2 = 9;
// Pin pour le bouton
int pin_bouton = 13;

// On définit la vitesse de base du moteur
int vitesse = 10;

// Mise en place des entrées et sorties au démarrage
void setup() {
  // Déclaration des pins en sortie
  pinMode(pin_moteur, OUTPUT);
  pinMode(pin_sens_1, OUTPUT);
  pinMode(pin_sens_1, OUTPUT);
  // Déclaration du pin d'entrée
  pinMode(pin_bouton, INPUT);
  // On choisit le sens de rotation du moteur
  digitalWrite(pin_sens_1, HIGH);
  digitalWrite(pin_sens_2, LOW);
}

// Code executé en boucle
void loop() {
  // Si on detecte un appui sur le bouton
  if(digitalRead(pin_bouton)) {
    // On augmente la vitesse
    vitesse += 30;
    // On s'assure que la vitesse est inférieure à 255 (valeur max)
    if(vitesse > 255) {
      vitesse = 255;
    }
    // On écrit la vitesse en sortie
    analogWrite(pin_moteur, vitesse);
    // On attend 1000ms=1s
    delay(1000);
  }
}
