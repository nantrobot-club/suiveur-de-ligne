typedef bool COTE_MOTEUR;
const COTE_MOTEUR DROITE = true;
const COTE_MOTEUR GAUCHE = false;

volatile bool cG, cD;
volatile int mG, mD;
volatile long int t = millis();
volatile bool virage = false;
volatile int maxMot = 255; //Valeur max de vitesse
volatile int minMot = 70; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)
volatile long int K = 10000;

const int limite = 250;   //Valeur de référence

const int pinCapteurDroite = A0;
const int pinCapteurGauche = A1;

const int pinMoteursDroite = 3; // à changer
const int pinMoteursGauche = 5; // à changer

int debutVirage = 0;

void setup() {
	// put your setup code here, to run once:
	pinMode (pinCapteurDroite, INPUT);  //Capteur gauche
	pinMode (pinCapteurGauche, INPUT);  //Capteur droit
	pinMode (pinMoteursDroite, OUTPUT); //Moteur gauche
	pinMode (pinMoteursGauche, OUTPUT); //Moteur droit
	Serial.begin(9600);
}

void commandeMoteurs(COTE_MOTEUR cote, int vitesse) {
	int pinCommande = pinMoteursGauche;
	if(cote == DROITE) pinCommande = pinMoteursDroite;
	analogWrite(pinCommande, vitesse);
}

void loop() {
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
			mD = maxMot;
			mG = maxMot;
			virage = false;
	}
    else if (cG && !cD) //Ligne visible à gauche
    {
		if (!virage){
			virage = true;
			t = millis();
		}
		else
		{
			mD = maxMot;
			mG = floor(min(255,max(minMot, K*maxMot/(millis()-t))));    //à factoriser par un facteur K pour lisser
			Serial.println( K*maxMot/(millis()-t));
		}  
	}
    else
    {             //Ligne visible à droite
		if (!virage)
		{
			virage = true;
			t = millis();
		}
		else
		{
          mG = maxMot;
          mD = floor(min(255,max(minMot, K*maxMot/(millis()-t))));
          Serial.println( K*maxMot/(millis()-t));
		}
	}
    analogWrite(3, mG);
    analogWrite(5, mD);
}
