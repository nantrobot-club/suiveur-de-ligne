// Connexion
const int pinCapteurDroite = A0;
const int pinCapteurGauche = A1;
const int pinMoteursDroite = 3; // à changer
const int pinMoteursGauche = 5; // à changer

// Etat du robot
bool virage = false;
bool arret = false;

// Capteurs
bool cG, cD;  // Booleens vrais si les capteurs Gauche et Droit detectent la ligne noire.
const int seuilLuminosite = 250;  // Valeur de reference, seuil de luminosite a au-dela duquel on considere que le capteur detecte une ligne noire.

// Moteurs
typedef bool COTE_MOTEUR;  // Definition d'un type de booleen pour le cote du moteur. Inutilise pour l'instant?
const COTE_MOTEUR DROITE = true;
const COTE_MOTEUR GAUCHE = false;
int mG, mD;  // Valeurs des vitesses appliquees aux moteurs Gauche et Droite.
int maxMot = 255;  // Tension pour une vitesse maximale appliquable aux moteurs.
int minMot = 70;  // Tension pour une vitesse minimale applicable aux moteurs (pour eviter le sur-place dans les virages).

// Virage
long int nbLoopEnVirage;  // Compteur d'itérations dans le virage.
long int K = 100;  // Facteur de vitesse de desceleration en virage.

void setup() {
	pinMode(pinCapteurDroite, INPUT);  // Capteur gauche
	pinMode(pinCapteurGauche, INPUT);  // Capteur droit
	pinMode(pinMoteursDroite, OUTPUT); // Moteur gauche
	pinMode(pinMoteursGauche, OUTPUT); // Moteur droit
	Serial.begin(9600);
}

int decelerationVirage() {
	return floor(
		min(
			maxMot,
			max(
				minMot,
				K * maxMot / nbLoopEnVirage
			)
		)
	);
}

int commencerVirage() {
	virage = true;
	nbLoopEnVirage = 0;
}

void loop() {
	// Si le robot est en arret, il ne se passe rien.
	if (arret) {
		// Recuperation des informations des capteurs.
		cG = analogRead(A0) > seuilLuminosite; // On regarde si le capteur gauche detecte la ligne.
		cD = analogRead(A1) > seuilLuminosite; // On regarde si le capteur droit detecte la ligne.

		// Affichage des informations du robot.
		Serial.print(mG);
		Serial.print(" ");
		Serial.print(mD);
		Serial.print(" : ");
		Serial.print(cG);
		Serial.print(" ");
		Serial.println(cD);

		// Adaptation du comportement des moteurs en fonction des donnees capteur.
		if (cG && cD) {
			// Les deux capteurs detectent la ligne noire. Il y a un probleme et le robot s'arrete.
			mD = 0;
			mG = 0;
			arret = true;
		}
		else if (!cG && !cD) {
			// Les deux capteurs ne detectent pas la ligne noire. On avance en ligne droite.
			virage = false;
			mD = maxMot;
			mG = maxMot;
		}
		else {
			// Les deux capteurs ne detectent pas la meme chose. Le robot doit tourner.
			if(!virage) {
				commencerVirage();
			}
			nbLoopEnVirage = nbLoopEnVirage + 1;  // On est dans une nouvelle iteration pendant le virage.
			if (cG && !cD) {
				// Le capteur gauche detecte la ligne, donc le robot est trop a droite. Il faut tourner a gauche.
				mD = maxMot;
				mG = decelerationVirage();   // TODO: à factoriser par un facteur pour lisser.
			}
			else {
				// Le capteur droit detecte la ligne, donc le robot est trop a gauche. Il faut tourner a droite.
				mG = maxMot;
				mD = decelerationVirage();
			}
		}
		// On transmet les valeurs de puissance a appliquer aux moteurs.
		analogWrite(pinMoteursGauche, mG);
		analogWrite(pinMoteursDroite, mD);
	}
}


