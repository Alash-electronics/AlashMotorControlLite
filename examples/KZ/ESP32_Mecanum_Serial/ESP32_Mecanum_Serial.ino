// Language: Қазақ | English: ../EN/ESP32_Mecanum_Serial/ | Русский: ../RU/ESP32_Mecanum_Serial/
/*
 * Serial Monitor арқылы меканум дөңгелектері бар роботты интерактивті басқару
 *
 * Қозғалтқыштарды қосу (режим PWM_PWM):
 * Motor 1 (Алдыңғы сол):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Алдыңғы оң): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Артқы сол):    IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Артқы оң):    IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Serial Monitor арқылы басқару командалары:
 * w - алға        q - диагональ алға-солға    e - диагональ алға-оңға
 * s - артқа       z - диагональ артқа-солға   c - диагональ артқа-оңға
 * a - солға
 * d - оңға
 * j - сағат тіліне қарсы айналу    l - сағат тілі бойынша айналу
 * x - тоқтату (еркін тоқтату)
 * b - тежеу (белсенді тежеу)
 * + - жылдамдықты арттыру
 * - - жылдамдықты азайту
 * h - анықтама (командалар тізімі)
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// 4 қозғалтқыш үшін объектілер жасаймыз
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Front Left
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Front Right
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Rear Left
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Rear Right

int speed = 60;  // Ағымдағы жылдамдық (0-100)

// Меканум дөңгелектерді басқару функциясы
void mecanumDrive(int vx, int vy, int rotation) {
  int speedFL = vx + vy + rotation;
  int speedFR = vx - vy - rotation;
  int speedRL = vx - vy + rotation;
  int speedRR = vx + vy - rotation;

  speedFL = constrain(speedFL, -100, 100);
  speedFR = constrain(speedFR, -100, 100);
  speedRL = constrain(speedRL, -100, 100);
  speedRR = constrain(speedRR, -100, 100);

  motorFL.setSpeed(speedFL);
  motorFR.setSpeed(speedFR);
  motorRL.setSpeed(speedRL);
  motorRR.setSpeed(speedRR);
}

void stopAll() {
  motorFL.stop();
  motorFR.stop();
  motorRL.stop();
  motorRR.stop();
}

void brakeAll() {
  motorFL.brake();
  motorFR.brake();
  motorRL.brake();
  motorRR.brake();
}

void printHelp() {
  Serial.println(F("\n╔══════════════════════════════════════════════════╗"));
  Serial.println(F("║   МЕКАНУМ РОБОТТЫ БАСҚАРУ - КОМАНДАЛАР           ║"));
  Serial.println(F("╠══════════════════════════════════════════════════╣"));
  Serial.println(F("║  НЕГІЗГІ ҚОЗҒАЛЫСТАР:                            ║"));
  Serial.println(F("║    w - Алға            s - Артқа                ║"));
  Serial.println(F("║    a - Солға           d - Оңға                 ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  ДИАГОНАЛЬДІ ҚОЗҒАЛЫСТАР:                        ║"));
  Serial.println(F("║    q - Алға-солға      e - Алға-оңға            ║"));
  Serial.println(F("║    z - Артқа-солға     c - Артқа-оңға           ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  АЙНАЛУ:                                         ║"));
  Serial.println(F("║    j - Сағат тіліне қарсы  l - Сағат тілімен   ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  ТОҚТАТУ:                                        ║"));
  Serial.println(F("║    x - Тоқтату (еркін)                          ║"));
  Serial.println(F("║    b - Тежеу (белсенді тежеу)                   ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  ЖЫЛДАМДЫҚТЫ БАСҚАРУ:                            ║"));
  Serial.println(F("║    + - Жылдамдықты арттыру                      ║"));
  Serial.println(F("║    - - Жылдамдықты азайту                       ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║    h - Осы анықтаманы көрсету                   ║"));
  Serial.println(F("╚══════════════════════════════════════════════════╝"));
  Serial.print(F("\nАғымдағы жылдамдық: "));
  Serial.print(speed);
  Serial.println(F("%\n"));
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("\n╔══════════════════════════════════════════════════╗"));
  Serial.println(F("║  ESP32 MECANUM 4WD ROBOT - SERIAL CONTROL       ║"));
  Serial.println(F("║  Драйвер: ZK-5AD                                 ║"));
  Serial.println(F("╚══════════════════════════════════════════════════╝\n"));

  printHelp();

  Serial.println(F("Жұмысқа дайын! Команда енгізіңіз..."));
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch(command) {
      // Негізгі қозғалыстар
      case 'w': case 'W':
        Serial.print(F("▲ Алға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, 0, 0);
        break;

      case 's': case 'S':
        Serial.print(F("▼ Артқа ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, 0, 0);
        break;

      case 'a': case 'A':
        Serial.print(F("◄ Солға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, speed, 0);
        break;

      case 'd': case 'D':
        Serial.print(F("► Оңға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, -speed, 0);
        break;

      // Диагональді қозғалыстар
      case 'q': case 'Q':
        Serial.print(F("↖ Алға-солға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, speed, 0);
        break;

      case 'e': case 'E':
        Serial.print(F("↗ Алға-оңға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, -speed, 0);
        break;

      case 'z': case 'Z':
        Serial.print(F("↙ Артқа-солға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, speed, 0);
        break;

      case 'c': case 'C':
        Serial.print(F("↘ Артқа-оңға ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, -speed, 0);
        break;

      // Айналу
      case 'j': case 'J':
        Serial.print(F("↺ Сағат тіліне қарсы айналу ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, 0, -speed);
        break;

      case 'l': case 'L':
        Serial.print(F("↻ Сағат тілі бойынша айналу ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, 0, speed);
        break;

      // Тоқтату
      case 'x': case 'X':
        Serial.println(F("■ Тоқтату"));
        stopAll();
        break;

      case 'b': case 'B':
        Serial.println(F("⊠ Тежеу"));
        brakeAll();
        break;

      // Жылдамдықты басқару
      case '+':
        speed = constrain(speed + 10, 0, 100);
        Serial.print(F("Жылдамдық арттырылды: "));
        Serial.print(speed);
        Serial.println(F("%"));
        break;

      case '-':
        speed = constrain(speed - 10, 0, 100);
        Serial.print(F("Жылдамдық азайтылды: "));
        Serial.print(speed);
        Serial.println(F("%"));
        break;

      // Анықтама
      case 'h': case 'H':
        printHelp();
        break;

      case '\n':
      case '\r':
        // Жаңа жол таңбаларын елемейміз
        break;

      default:
        Serial.print(F("Белгісіз команда: "));
        Serial.println(command);
        Serial.println(F("Анықтама үшін 'h' басыңыз"));
        break;
    }
  }
}
