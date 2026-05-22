#include <HardwareSerial.h>
#include <ESP32Servo.h>

//HardwareSerial externos(1);
HardwareSerial SerialPort(2);  // Comunicación Serial2

const int trig = 32;
const int eco = 33;
const int servoPin = 26;

int angulo = 0;
int distancia;
Servo giro;

bool paro = false;

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  giro.attach(servoPin);
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  Serial.println("Sistema iniciado.");
  SerialPort.setTimeout(10); //Nuevo
}

void loop() {
  // Revisión constante del puerto serie
  if (SerialPort.available()) {
    comprobacion_mensaje();
  }

  //Parte en la que se ejecutara la rutina hasta que se mande el mensaje
  if(!paro){
    // Movimiento normal de la cabeza
    giro_cabeza();
  }
}

//Rutinas a realziar
void giro_cabeza(){
  Serial.println("Giro 1");
  for (angulo = 90; angulo <= 180; angulo++) {
    if (verificarInterrupcion()) {
      return;
    }
    giro.write(angulo);
    //Deteccion();
    delay_millis(20);
    //delay(5);
  }

  Serial.println("Giro 2");
  for (angulo = 180; angulo >= 0; angulo--) {
    if (verificarInterrupcion()) {
      return;
    }
    giro.write(angulo);
    //Deteccion();
    delay_millis(20);
    //delay(5);
  }

  Serial.println("Giro 3");
  for (angulo = 0; angulo <= 90; angulo++){
    if(verificarInterrupcion()){
      return;
    }
    giro.write(angulo);
    delay_millis(20);
  }
}

/*void comprobacion_mensaje() {
  static String mensaje = "";

  while(SerialPort.available()){
    char c = SerialPort.read();
    if(c == '\n'){
      mensaje.trim();
      if (mensaje == "REQ") {
        paro = true;
        Serial.println("Interrupción recibida: REQ");
        SerialPort.println("OK");
      } else if (mensaje == "DONE") {
        paro = false;
    //giro.write(90);
        Serial.println("Reanudando rutina principal (DONE)");
      }
    }
  }
}*/

void comprobacion_mensaje(){
  String mensaje = SerialPort.readStringUntil('\n');
  mensaje.trim();
  if(mensaje == "REQ"){
    paro = true;
    SerialPort.println("OK");
  }else if(mensaje == "DONE"){
    paro = false;
    giro.write(90);
    delay(1000);
    Serial.println("Reanudando");
  }
}



void Deteccion() {
  if (verificarInterrupcion()) {
    return;
  }
  distancia = medirDistancia();
  Serial.print(distancia);
  Serial.println(" cm");

  while (distancia > 0 && distancia < 10) {
    if (verificarInterrupcion()) {
      return;
    }
    giro.write(angulo);
    delay(10);
    distancia = medirDistancia();
  }
}

int medirDistancia() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duracion = pulseIn(eco, HIGH);
  return duracion * 0.034 / 2;
}

void delay_millis(unsigned long tiempo) {
  unsigned long inicio = millis();
  while (millis() - inicio < tiempo) {
    if (SerialPort.available()) {
      comprobacion_mensaje();
    }
    if (paro) {
      return; // si llega REQ, salir inmediatamente
    }
  }
}

bool verificarInterrupcion() {
  if (SerialPort.available()) {
    comprobacion_mensaje();
  }
  return paro;
}


