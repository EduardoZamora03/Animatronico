int RELE_ON = 0;
int RELE_OFF = 1;

int rele1 = 33;
int rele2 = 12;
int rele3 = 14;
int rele4 = 27;

void setup() {
  pinMode(rele1,OUTPUT);
  pinMode(rele2,OUTPUT);
  pinMode(rele3,OUTPUT);
  pinMode(rele4,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(rele1, RELE_ON);
  digitalWrite(rele2, RELE_ON);
  digitalWrite(rele3, RELE_ON);
  digitalWrite(rele4, RELE_ON);
  Serial.println("Rele Accionado: Bonbilla encendida");
  delay(2000);

  digitalWrite(rele1, RELE_OFF);
  digitalWrite(rele2, RELE_OFF);
  digitalWrite(rele3, RELE_OFF);
  digitalWrite(rele4, RELE_OFF);
  Serial.println("Rele NO accionado: Bombilla Apagada");
  delay(2000);
}



/*#define RELE_ON 0
#define RELE_OFF 1

int rele = 2;

void setup() {
  pinMode(rele,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(rele, RELE_ON);
  Serial.println("Rele Accionado: Bonbilla encendida");
  delay(2000);

  digitalWrite(rele, RELE_OFF);
  Serial.println("Rele NO accionado: Bombilla Apagada");
  delay(2000);
}*/
