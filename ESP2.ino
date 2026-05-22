#include <HardwareSerial.h>
#include <ESP32Servo.h>

HardwareSerial SerialPort(2);

char number = ' ';
unsigned long inicio_audio = 0;
unsigned long duracion_audio = 15000;
bool permiso  = false;
const int led = 2;

//Foco
const int foco = 13;
unsigned long blink = 100;
unsigned long tiempoAnterior = 0;
bool estado_foco = false;

//Servo Y
const int Servopin = 27;
int angulo = 0;
Servo cabeza_y;

//Arco
const int rele_arco = 23;

void setup() {
  delay(3000);
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  cabeza_y.attach(Servopin);
  pinMode(foco, OUTPUT);
  pinMode(rele_arco, OUTPUT);
  digitalWrite(foco, LOW);
  digitalWrite(rele_arco, HIGH);
  delay(2000);
  cabeza_y.write(90);

  SerialPort.setTimeout(10); //Nuevo
}

void loop() {

  if(SerialPort.available()){
    String msg = SerialPort.readStringUntil('\n');
    msg.trim();
    if(msg == "EMPIEZA"){
      permiso = true;
      inicio_audio = millis();
      digitalWrite(rele_arco, LOW);
    }
  }

  // Lugar donde se ejecutarab todas las rutinas
  if(permiso){
    
    blink_foco();
    movimiento_cabeza_y();
    if(millis() - inicio_audio >= duracion_audio){
      finalizar_audio();
    }
  }
}

void finalizar_audio(){
  permiso = false;
  digitalWrite(foco, LOW);
  cabeza_y.write(10);
  digitalWrite(rele_arco, HIGH);
  delay(7000);
  cabeza_y.write(90);
  delay(2500);
  SerialPort.println("HECHO");
}

void blink_foco(){
  unsigned long tiempoActual = millis();
  if(tiempoActual - tiempoAnterior >= blink){
    tiempoAnterior = tiempoActual;
    estado_foco = !estado_foco;
    digitalWrite(foco, estado_foco);
  }
}

void movimiento_cabeza_y(){
  for(angulo = 90; angulo <= 140; angulo++){
    cabeza_y.write(angulo);
    delay(1);
  }
  for(angulo = 140; angulo >= 40; angulo--){
    cabeza_y.write(angulo);
    delay(1);
  }
  for(angulo = 40; angulo <= 90; angulo++){
    cabeza_y.write(angulo);
    delay(1);
  }
}



