// © 2022 NantesRobot

const int limiteCapteur = 250;   //Valeur de référence  des capteurs qui nous permet de différencier le blanc du noir

const int maxMot = 80; //Valeur max de vitesse en ligne droite
const int minMot = 20; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)

int etat;                       // Variable qui stocke le numéro de l'état
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
    // Initialisation des pins d'entrées/sorties
    // À compléter





    // Initialisation de l'état
    // À compléter

    initPontEnH();
}

void loop() {
  
    // Détection de la ligne pour chaque capteur
    // À compléter

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


    // Choix de la direction (gauche, droite, tout droit)
    // Indice : utilser la variable etat pour les conditions
    // À compléter








    // Commande des moteurs
    // Indice : utilser la variable etat pour les conditions et valMG et valMD pour les valeurs.
    // À compléter







    // Attention à ne pas oublier d'envoyer la commande aux pins des moteurs.


    }
