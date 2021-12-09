volatile const int limite = 250;   //Valeur de référence
volatile bool cG, cD;
volatile int mG, mD;
//volatile long int t = millis();
//volatile bool virage = false;
volatile const int maxMot = 100; //Valeur max de vitesse
volatile const int minMot = 20; //Vitesse minimale d'une roue lors d'un virage (évite le sur-place)
volatile const long int K = 100;

volatile int state;


const int forward = 0;
const int turnRight= 1;
const int turnLeft= 2;


void setup() {
  // put your setup code here, to run once:
  pinMode (A0, INPUT);  //Capteur gauche
  pinMode (A1, INPUT);  //Capteur droit
  pinMode (3, OUTPUT); //Moteur gauche
  pinMode (5, OUTPUT); //Moteur droit
  pinMode (8,OUTPUT);
  digitalWrite(8,LOW);
  pinMode (9,OUTPUT);
  digitalWrite(9,LOW);
  pinMode (11,OUTPUT);
  digitalWrite(11,HIGH);
  pinMode (12,OUTPUT);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  state = 0;
}

void loop() {
    Serial.println(analogRead(A0));
    cD = analogRead(A0) > limite; //Ligne visible capteur gauche
    cG = analogRead(A1) > limite; //Ligne visible capteur droit
//    Serial.print(mG);
//    Serial.print(" ");
//    Serial.print(mD);
//    Serial.print(" : ");
//    Serial.print(cG);
//    Serial.print(" ");
//    Serial.println(cD);
//


if (cG && !cD){
  state = turnRight;
}
else if(cD && !cG){
  state = turnLeft;
}
else if( !cD && !cG){
  state = forward;
}


    if (state == forward)
      {
          mD = maxMot;
          mG = maxMot;
      }
    else if (state == turnLeft) //Ligne visible à gauche
    {     //t=millis();
          mG = maxMot*2;
          mD = minMot;//floor(min(255,max(minMot, maxMot/(K*(millis()-t)))));    //à factoriser par un facteur K pour lisser
          //Serial.println( K*maxMot/(millis()-t));
        }  
    else if (state == turnRight){             //Ligne visible à droite
        //t = millis();
          mD = maxMot*2;
          mG = minMot;//floor(min(255,max(minMot, maxMot/(K*(millis()-t)))));
          //Serial.println( maxMot/(K*(millis()-t)));
    }
    analogWrite(3, mG);
    analogWrite(5, mD);
}
