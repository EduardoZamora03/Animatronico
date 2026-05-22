#include <ESP32Servo.h>

#define TOUCH_PIN_1   T0   // T0 = GPIO 4
#define TOUCH_PIN_2   T3   // T3 = GPIO 15

#define SERVO_PIN_1   12
#define SERVO_PIN_2   13

Servo servo1;
Servo servo2;

// Estados independientes
int estado1 = 0;   // Servo 1 -> 0° o 180°
int estado2 = 0;   // Servo 2 -> 0° o 180°

int umbral1 = 30;  // Umbral para touch 1
int umbral2 = 30;  // Umbral para touch 2

bool ultimoToque1 = false;
bool ultimoToque2 = false;

void setup() {
  Serial.begin(115200);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);

  servo1.write(0);
  servo2.write(0);

  Serial.println("Listo. Usa Touch1 y Touch2 para controlar los servos.");
}

void loop() {

  // ---------- LECTURA TOUCH 1 ----------
  int valor1 = touchRead(TOUCH_PIN_1);
  bool tocado1 = (valor1 < umbral1);

  if (tocado1 && !ultimoToque1) {
    estado1 = !estado1;

    if (estado1 == 1) {
      servo1.write(180);
      Serial.println("Servo 1 -> 180°");
    } else {
      servo1.write(0);
      Serial.println("Servo 1 -> 0°");
    }

    delay(500); // anti-rebote
  }

  ultimoToque1 = tocado1;

  // ---------- LECTURA TOUCH 2 ----------
  int valor2 = touchRead(TOUCH_PIN_2);
  bool tocado2 = (valor2 < umbral2);

  if (tocado2 && !ultimoToque2) {
    estado2 = !estado2;

    if (estado2 == 1) {
      servo2.write(180);
      Serial.println("Servo 2 -> 180°");
    } else {
      servo2.write(0);
      Serial.println("Servo 2 -> 0°");
    }

    delay(500); // anti-rebote
  }

  ultimoToque2 = tocado2;
}
