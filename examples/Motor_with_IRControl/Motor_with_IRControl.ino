/*
 * Motor_with_IRControl - IR пультпен моторды басқару
 *
 * МАҢЫЗДЫ: Arduino Uno/Nano-да IR библиотекасы Timer2 қолданады (пин 3, 11).
 * Моторлар үшін Timer1 (пин 9, 10) немесе Timer0 (пин 5, 6) қолданыңыз!
 *
 * Қосылу:
 * - IR приемник VS1838B → D7
 * - L298N: IN1→D4, ENA(PWM)→D9 (Timer1 - IR-мен конфликтсіз!)
 * - Немесе TB6612FNG: IN1→D9, IN2→D10 (екеуі де Timer1)
 *
 * IR кодтары (өз пультіңізге өзгертіңіз):
 * [2] Алға, [8] Артқа, [4] Баяулату, [6] Жылдамдату, [5] Тоқтату
 *
 * Alash Electronics (https://alash-electronics.kz) | MIT License
 */




/*
#include <AlashMotorControlLite.h>
#include <AlashIRControlRX.h>

// Пиндер
#define IR_RX_PIN 7

#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 9);  // PWM=9 (Timer1 - дұрыс!)
  // Немесе: AlashMotorControlLite motor(PWM_PWM, 9, 10);
#endif

AlashIRControlRX irReceiver(IR_RX_PIN);

// IR кодтары (өз пультіңізге өзгертіңіз)
#define IR_FORWARD  0xFF18E7
#define IR_BACKWARD 0xFF4AB5
#define IR_SLOWER   0xFF10EF
#define IR_FASTER   0xFF5AA5
#define IR_STOP     0xFF38C7

int currentSpeed = 0;
const int speedStep = 20;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println(F("\n--- Motor + IR Control ---"));
  Serial.print(F("IR: пин ")); Serial.println(IR_RX_PIN);
  Serial.println(F("[2]Алға [8]Артқа [4]Баяу [6]Жылдам [5]Тоқтату\n"));

  irReceiver.begin();
  motor.stop();
}

void loop() {
  if (irReceiver.check()) {
    handleIRCommand(irReceiver.data);
  }
}

void handleIRCommand(uint32_t irCode) {
  Serial.print(F("IR: 0x"));
  Serial.print(irCode, HEX);
  Serial.print(F(" → "));

  switch(irCode) {
    case IR_FORWARD:
      if (currentSpeed <= 0) currentSpeed = speedStep;
      Serial.print(F("АЛҒА ")); Serial.println(currentSpeed);
      motor.setSpeed(currentSpeed);
      break;

    case IR_BACKWARD:
      if (currentSpeed >= 0) currentSpeed = -speedStep;
      Serial.print(F("АРТҚА ")); Serial.println(currentSpeed);
      motor.setSpeed(currentSpeed);
      break;

    case IR_FASTER:
      if (currentSpeed > 0) {
        currentSpeed = min(100, currentSpeed + speedStep);
      } else if (currentSpeed < 0) {
        currentSpeed = max(-100, currentSpeed - speedStep);
      } else {
        currentSpeed = speedStep;
      }
      Serial.print(F("ЖЫЛДАМ ")); Serial.println(currentSpeed);
      motor.setSpeed(currentSpeed);
      break;

    case IR_SLOWER:
      if (currentSpeed > 0) {
        currentSpeed = max(0, currentSpeed - speedStep);
      } else if (currentSpeed < 0) {
        currentSpeed = min(0, currentSpeed + speedStep);
      }
      Serial.print(F("БАЯУ ")); Serial.println(currentSpeed);
      if (currentSpeed == 0) motor.stop();
      else motor.setSpeed(currentSpeed);
      break;

    case IR_STOP:
      currentSpeed = 0;
      motor.stop();
      Serial.println(F("ТОҚТАТУ"));
      break;

    default:
      Serial.println(F("белгісіз"));
      break;
  }
}
*/