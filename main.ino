volatile int limite = 250;   //Valeur de référence
volatile bool cG, cD;
volatile int mG, mD;
volatile long int t = millis();
volatile bool virage = false;
volatile int maxMot = 255; //Valeur max de vitesse
volatile int minMot = 70; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)
volatile long int K = 10000;

void setup() {
  // put your setup code here, to run once:
  pinMode (A0, INPUT);  //Capteur gauche
  pinMode (A1, INPUT);  //Capteur droit
  pinMode (3, OUTPUT); //Moteur gauche
  pinMode (5, OUTPUT); //Moteur droit
  Serial.begin(9600);
}

void loop() {
    //Serial.println(analogRead(A0));
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
      else{
          mD = maxMot;
          mG = floor(min(255,max(minMot, K*maxMot/(millis()-t))));    //à factoriser par un facteur K pour lisser
          Serial.println( K*maxMot/(millis()-t));
          virage = true;
        }
          
      }
    else{             //Ligne visible à droite
       if (!virage){
        virage = true;
        t = millis();
      }
      else{
          mG = maxMot;
          mD = floor(min(255,max(minMot, K*maxMot/(millis()-t))));
          Serial.println( K*maxMot/(millis()-t));
          virage = true;
    }
   }
    analogWrite(3, mG);
    analogWrite(5, mD);
}
