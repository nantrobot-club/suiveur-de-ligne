int capteurInfrarouge;
const int limite1(200);
const int limite2(850);
const int limite3(990);

const int led1(2);
const int led2(3);
const int led3(4);

const int pinCapteur(A0);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  pinMode(pinCapteur,INPUT);

  Serial.begin(9600);
}

void loop() {
  
  capteurInfrarouge = analogRead(pinCapteur);
  Serial.print(capteurInfrarouge);
  Serial.println("   ");
  
  if (limite3 < capteurInfrarouge ){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  if (capteurInfrarouge < limite3){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  if (capteurInfrarouge < limite2){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
  }
  if ( capteurInfrarouge < limite1){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
  }

delay(50);
}
