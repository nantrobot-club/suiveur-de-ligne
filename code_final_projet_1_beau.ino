const int limiteCapteur = 250;   //Valeur de référence  des capteurs qui nous permet de différencier le blanc du noir
bool detectionG, detectionD;
int valMG, valMD;
//volatile long int t = millis();
//volatile bool virage = false;
const int maxMot = 80; //Valeur max de vitesse en ligne droite
const int minMot = 20; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)

int etat;

//différents états possible pour le robot
const int toutDroit = 0;
const int tournerAGauche= 1;
const int tournerADroite= 2;

//entrées sorties :
const int moteursGauches = 3;
const int moteursDroits = 5;
const int capteurGauche = 14; //A0
const int capteurDroit = 15;  //A1

const int IN4 = 8; // IN1 à 4 : gère le sens de rotation des moteurs droites et gauches
const int IN2 = 9; // On ne s'en occupera pas ici
const int IN3 = 11;
const int IN1 = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode (capteurGauche, INPUT);  //Capteur gauche
  pinMode (capteurDroit, INPUT);  //Capteur droit
  pinMode (moteursGauches, OUTPUT); //Moteur gauche
  pinMode (moteursDroits, OUTPUT); //Moteur droit
  pinMode (IN4,OUTPUT);
  digitalWrite(IN4,LOW);
  pinMode (IN2,OUTPUT);
  digitalWrite(IN2,LOW);
  pinMode (IN3,OUTPUT);
  digitalWrite(IN3,HIGH);
  pinMode (IN1,OUTPUT);
  digitalWrite(IN1,HIGH);
  Serial.begin(9600);
  etat = 0;
}

void loop() {
  //Serial.println(analogRead(capteurGauche));
  
  detectionG = analogRead(capteurGauche) < limiteCapteur; //Ligne visible capteur gauche
  detectionD = analogRead(capteurDroit) < limiteCapteur; //Ligne visible capteur droit

  
//pour afficher les valeurs : 
  
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
//


  if (!detectionG && detectionD)
  {
      etat = tournerAGauche;
  }
  else if(!detectionD && detectionG)
  {
      etat = tournerADroite;
  }
  else if( !detectionD && !detectionG)
  {
      etat = toutDroit;
  }


  if (etat == toutDroit)
  {
      valMD = maxMot;
      valMG = maxMot;
  }
  else if (etat == tournerADroite) 
  {   
      valMG = maxMot*2;
      valMD = minMot;
  }  
  else if (etat == tournerAGauche)
  {  
      valMD = maxMot*2;
      valMG = minMot;
  }
  analogWrite(moteursGauches, valMG);
  analogWrite(moteursDroits, valMD);
}
