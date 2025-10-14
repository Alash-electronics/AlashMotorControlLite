/*
 * IR_Servo_L298N - IR пультпен екі мотор + servo басқару
 *
 * МАҢЫЗДЫ: Arduino Uno Timer конфликті!
 * - IR → Timer2 (пин 3,11), Servo → Timer1 (пин 9,10)
 * - Моторлар үшін Timer0 (пин 5,6) қолданамыз
 *
 * Қосылу:
 * - IR VS1838B → D7
 * - Servo SG90 → D9
 * - L298N Motor A: IN1→D2, IN2→D4, ENA→D5(PWM)
 * - L298N Motor B: IN3→D8, IN4→D12, ENB→D6(PWM)
 *
 * IR пульт: [2]Алға [8]Артқа [4]Сол [6]Оң [5]Стоп [↑][↓][OK]-Servo
 * Alash Electronics | MIT License
 */


 
/*
#include <AlashMotorControlLite.h>
#include <AlashIRControlRX.h>
#include <Servo.h>

// Пиндер
#define IR_RX_PIN 7
#define SERVO_PIN 9
#define MOTOR_A_IN1 2
#define MOTOR_A_IN2 4
#define MOTOR_A_ENA 5  // PWM Timer0
#define MOTOR_B_IN3 8
#define MOTOR_B_IN4 12
#define MOTOR_B_ENB 6  // PWM Timer0

AlashMotorControlLite motorLeft(DIR_DIR_PWM, MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_ENA);
AlashMotorControlLite motorRight(DIR_DIR_PWM, MOTOR_B_IN3, MOTOR_B_IN4, MOTOR_B_ENB);
AlashIRControlRX irReceiver(IR_RX_PIN);
Servo myServo;

// IR кодтары (өз пультіңізге өзгертіңіз)
#define IR_FORWARD   0xFF18E7
#define IR_BACKWARD  0xFF4AB5
#define IR_LEFT      0xFF10EF
#define IR_RIGHT     0xFF5AA5
#define IR_STOP      0xFF38C7
#define IR_SERVO_LEFT   0xFFA857
#define IR_SERVO_RIGHT  0xFF629D
#define IR_SERVO_CENTER 0xFF02FD

int motorSpeed = 60;
int servoAngle = 90;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println(F("\n--- IR + Servo + Dual Motors ---"));
  Serial.println(F("IR:D7 Servo:D9 PWM:D5,D6\n"));

  irReceiver.begin();
  myServo.attach(SERVO_PIN);
  myServo.write(servoAngle);
  motorLeft.stop();
  motorRight.stop();
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
      motorLeft.setSpeed(motorSpeed);
      motorRight.setSpeed(motorSpeed);
      Serial.println(F("АЛҒА"));
      break;

    case IR_BACKWARD:
      motorLeft.setSpeed(-motorSpeed);
      motorRight.setSpeed(-motorSpeed);
      Serial.println(F("АРТҚА"));
      break;

    case IR_LEFT:
      motorLeft.setSpeed(-motorSpeed / 2);
      motorRight.setSpeed(motorSpeed);
      Serial.println(F("СОЛҒА"));
      break;

    case IR_RIGHT:
      motorLeft.setSpeed(motorSpeed);
      motorRight.setSpeed(-motorSpeed / 2);
      Serial.println(F("ОҢҒА"));
      break;

    case IR_STOP:
      motorLeft.stop();
      motorRight.stop();
      Serial.println(F("СТОП"));
      break;

    case IR_SERVO_LEFT:
      servoAngle -= 15;
      servoAngle = constrain(servoAngle, 0, 180);
      myServo.write(servoAngle);
      Serial.print(F("Servo ")); Serial.println(servoAngle);
      break;

    case IR_SERVO_RIGHT:
      servoAngle += 15;
      servoAngle = constrain(servoAngle, 0, 180);
      myServo.write(servoAngle);
      Serial.print(F("Servo ")); Serial.println(servoAngle);
      break;

    case IR_SERVO_CENTER:
      servoAngle = 90;
      myServo.write(servoAngle);
      Serial.println(F("Servo 90°"));
      break;

    default:
      Serial.println(F("белгісіз"));
      break;
  }
}
*/