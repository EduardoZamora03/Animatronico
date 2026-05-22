#include <HardwareSerial.h>

HardwareSerial SerialUART(1);
const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialUART.begin(9600, SERIAL_8N1, 16, 17);

}

void loop() {
  if(SerialUART.available()){
    char dato = SerialUART.read();
    Serial.println(dato);

    if(dato == 'A'){
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
      Serial.println("OK");
    }
  }

}
