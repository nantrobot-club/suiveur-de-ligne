typedef bool COTE_MOTEUR;
const COTE_MOTEUR DROITE = true;
const COTE_MOTEUR GAUCHE = false;

bool cG, cD;
const int limite = 250;  //Valeur de référence

int mG, mD;
long int t = millis();
bool virage = false;
bool arret = false;
int maxMot = 255; 		//Valeur max de vitesse
int minMot = 70; 		//Vitesse minimale d'une roue lors d'un virage (évite le sur-place)
long int K = 10000;

const int pinCapteurDroite = A0;
const int pinCapteurGauche = A1;

const int pinMoteursDroite = 3; // à changer
const int pinMoteursGauche = 5; // à changer

void setup() {
	pinMode (pinCapteurDroite, INPUT);  //Capteur gauche
	pinMode (pinCapteurGauche, INPUT);  //Capteur droit
	pinMode (pinMoteursDroite, OUTPUT); //Moteur gauche
	pinMode (pinMoteursGauche, OUTPUT); //Moteur droit
	Serial.begin(9600);
}

int decelerationVirage() {
	return floor(min(maxMot,max(minMot, K*maxMot/(millis()-t))));
}

int commencerVirage() {
	virage = true;
	t = millis() - 1;
}

void loop() {
	if(arret) {
		return;
	}
    cG = analogRead(A0) < limite; //Ligne visible capteur gauche
    cD = analogRead(A1) < limite; //Ligne visible capteur droit
    Serial.print(mG);
    Serial.print(" ");
    Serial.print(mD);
    Serial.print(" : ");
    Serial.print(cG);
    Serial.print(" ");
    Serial.println(cD);
    if (cG == cD)
	{
		if(cG) {
			mD = maxMot;
			mG = maxMot;
		}
		else {
			mD = 0;
			mG = 0;
			arret = true;
		}
		virage = false;
	}
    else {
    	if(!virage) {
    		commencerVirage();
    	}
	    if (cG && !cD) {	//Ligne visible à gauche
			mD = maxMot;
			mG = decelerationVirage();   //à factoriser par un facteur K pour lisser
			Serial.println( K*maxMot/(millis()-t));  
		}
	    else {             //Ligne visible à droite
	        mG = maxMot;
	        mD = decelerationVirage();
	        Serial.println( K*maxMot/(millis()-t));
		}
	}
    analogWrite(pinMoteursGauche, mG);
    analogWrite(pinMoteursDroite, mD);
}


