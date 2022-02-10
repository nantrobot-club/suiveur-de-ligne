// © 2022 NantesRobot

const int limiteCapteur = 250;   //Valeur de référence  des capteurs qui nous permet de différencier le blanc du noir

const int maxMot = 80; //Valeur max de vitesse en ligne droite
const int minMot = 20; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)

int etat = 0;                       // Variable qui stocke le numéro de l'état
int valMG, valMD;               // Valeur des commandes moteurs
bool detectionG, detectionD;    // Booléen (vrai ou faux) : détection de sortie de la ligne.


// Constantes des différents états possible pour le robot
const int toutDroit = 0;
const int tournerAGauche= 1;
const int tournerADroite= 2;

// Noms des entrées/sorties :
const int moteursGauches = 3; // D3
const int moteursDroits = 5;  // D5
const int capteurGauche = 14; // A0
const int capteurDroit = 15;  // A1
const int pinDebugLED = 2;    // D2
const int pinBeep = 7;    // D2

// Noms des pins du pont en H (NE PAS UTILISER)
const int IN4 = 8; // IN1 à 4 : gère le sens de rotation des moteurs droites et gauches
const int IN2 = 9; // On ne s'en occupera pas ici
const int IN3 = 11;
const int IN1 = 12;


void initPontEnH(){
    // NE PAS TOUCHER
    pinMode (IN4,OUTPUT);
    digitalWrite(IN4,LOW);
    pinMode (IN2,OUTPUT);
    digitalWrite(IN2,LOW);
    pinMode (IN3,OUTPUT);
    digitalWrite(IN3,HIGH);
    pinMode (IN1,OUTPUT);
    digitalWrite(IN1,HIGH);
    Serial.begin(9600);
}



void setup() {
    pinMode (capteurGauche, INPUT);  //Capteur gauche
    pinMode (capteurDroit, INPUT);  //Capteur droit
    pinMode (moteursGauches, OUTPUT); //Moteur gauche
    pinMode (moteursDroits, OUTPUT); //Moteur droit
    pinMode (pinDebugLED, OUTPUT);   // LED de debug : changement de mode ET capteurs (allumée si détecté, éteinte sinon).
    pinMode (pinBeep, OUTPUT);       // beeper sonore pour le changement de mode.

    initPontEnH();
}

void clignoteLED(){
  for (int i=0; i<3; i++){
    digitalWrite(pinDebugLED, HIGH);
    digitalWrite(pinBeep, HIGH);
    delay(100);
    digitalWrite(pinDebugLED, LOW);
    digitalWrite(pinBeep, LOW);
    delay(100);
  }
}

void loop() {
    Serial.print("CG ");
    Serial.print(analogRead(capteurGauche));
    Serial.print("CD ");
    Serial.print(analogRead(capteurDroit));
    Serial.print(" : ");
    Serial.print(detectionG);
    Serial.print(" ");
    Serial.print(detectionD);
    Serial.print(" ");
    Serial.print(valMG);
    Serial.print(" ");
    Serial.println(valMD);
    analogWrite(moteursDroits, 255);
    delay(2000);
    analogWrite(moteursDroits, 0);
    clignoteLED();
    analogWrite(moteursGauches, 255);
    delay(2000);
    analogWrite(moteursGauches, 0);
    clignoteLED();
    int cpt = 0;
    while (cpt < 5000){
      digitalWrite(pinDebugLED, (analogRead(capteurGauche) < limiteCapteur));
      cpt ++;
      delay(1);
    }
    clignoteLED();
    cpt = 0;
    while (cpt < 5000){
      digitalWrite(pinDebugLED, (analogRead(capteurDroit) < limiteCapteur));
      cpt ++;
      delay(1);
    }
    clignoteLED();
    }
