// Language: Қазақ | English: ../EN/MultiMotorSync/ | Русский: ../RU/MultiMotorSync/
/*
 * Бұл мысал бірнеше қозғалтқышты синхрондауды көрсетеді
 *
 * Бірнеше қозғалтқышпен жұмыс кезінде маңызды:
 * - Іске қосу мен тоқтатуды синхрондау
 * - Жылдамдықты үйлестіру
 * - Топтық басқару үшін функциялар жасау
 * - Кодты дұрыс ұйымдастыру
 *
 * Бұл мысал бірнеше қозғалтқышты бір уақытта басқарудың
 * ең жақсы тәжірибелерін көрсетеді.
 *
 * 2 қозғалтқыш үшін қосылым:
 * Arduino:
 *   Motor 1: DIR -> Pin 4, PWM -> Pin 3
 *   Motor 2: DIR -> Pin 7, PWM -> Pin 6
 *
 * ESP32:
 *   Motor 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 *   Motor 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// Қозғалтқыш объектілерін жасаймыз
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32 - PWM_PWM режимі
  AlashMotorControlLite motorLeft(PWM_PWM, 32, 33);
  AlashMotorControlLite motorRight(PWM_PWM, 25, 26);
#else
  // Arduino - DIR_PWM режимі
  AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
  AlashMotorControlLite motorRight(DIR_PWM, 7, 6);
#endif

// ========== ТОПТЫҚ БАСҚАРУ ФУНКЦИЯЛАРЫ ==========

// Екі қозғалтқышта синхронды жылдамдық орнату
void setBothMotors(int leftSpeed, int rightSpeed) {
  motorLeft.setSpeed(leftSpeed);
  motorRight.setSpeed(rightSpeed);
}

// Барлық қозғалтқышты тоқтату
void stopAllMotors() {
  motorLeft.stop();
  motorRight.stop();
}

// Барлық қозғалтқышты тежеу
void brakeAllMotors() {
  motorLeft.brake();
  motorRight.brake();
}

// Екі қозғалтқыштың жылдамдығын тегіс өзгерту
void smoothBothMotors(int leftTarget, int rightTarget, unsigned long rampTime) {
  int leftCurrent = motorLeft.getSpeed();
  int rightCurrent = motorRight.getSpeed();

  int leftDiff = leftTarget - leftCurrent;
  int rightDiff = rightTarget - rightCurrent;

  int maxSteps = max(abs(leftDiff), abs(rightDiff));
  if (maxSteps == 0) return;

  unsigned long stepDelay = rampTime / maxSteps;

  for (int step = 1; step <= maxSteps; step++) {
    // Әр қозғалтқыш үшін ағымдағы жылдамдықты есептейміз
    int leftSpeed = leftCurrent + (leftDiff * step / maxSteps);
    int rightSpeed = rightCurrent + (rightDiff * step / maxSteps);

    motorLeft.setSpeed(leftSpeed);
    motorRight.setSpeed(rightSpeed);

    delay(stepDelay);
  }

  // Мақсатты мәндерге дәл жетуді кепілдендіреміз
  motorLeft.setSpeed(leftTarget);
  motorRight.setSpeed(rightTarget);
}

// Алға қозғалу
void moveForward(int speed) {
  setBothMotors(speed, speed);
}

// Артқа қозғалу
void moveBackward(int speed) {
  setBothMotors(-speed, -speed);
}

// Орнында оңға бұрылу
void turnRight(int speed) {
  setBothMotors(speed, -speed);
}

// Орнында солға бұрылу
void turnLeft(int speed) {
  setBothMotors(-speed, speed);
}

// Тегіс бұрылыс (доға) оңға
void arcRight(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed - turnAmount;
  setBothMotors(leftSpeed, rightSpeed);
}

// Тегіс бұрылыс (доға) солға
void arcLeft(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed - turnAmount;
  int rightSpeed = baseSpeed;
  setBothMotors(leftSpeed, rightSpeed);
}

// Барлық қозғалтқыш күйін шығару
void printMotorStatus() {
  Serial.print(F("Сол: "));
  Serial.print(motorLeft.getSpeed());
  Serial.print(F("  |  Оң: "));
  Serial.println(motorRight.getSpeed());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  БІРНЕШЕ ҚОЗҒАЛТҚЫШТЫ СИНХРОНДАУ              ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== НЕГІЗГІ СИНХРОНДАУ ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("НЕГІЗГІ СИНХРОНДАУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Екі қозғалтқышты бір уақытта іске қосу\n"));

  Serial.println(F("ЖАМАН - қозғалтқыштар кезекпен іске қосылады:"));
  Serial.println(F("  motorLeft.setSpeed(80);"));
  Serial.println(F("  delay(100);  // Сол жақ қазірдің өзінде жұмыс істейді!"));
  Serial.println(F("  motorRight.setSpeed(80);\n"));

  Serial.println(F("ЖАҚСЫ - қозғалтқыштар синхронды іске қосылады:"));
  Serial.println(F("  motorLeft.setSpeed(80);"));
  Serial.println(F("  motorRight.setSpeed(80);  // Сол жақтан кейін бірден\n"));

  Serial.println(F("Синхронды іске қосамыз:"));
  setBothMotors(70, 70);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Бір уақытта тоқтату"));
  stopAllMotors();
  printMotorStatus();
  delay(2000);

  // ========== ӘРТҮРЛІ ЖЫЛДАМДЫҚТАР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ӘРТҮРЛІ ЖЫЛДАМДЫҚТАРДЫ ҮЙЛЕСТІРУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Сол 80%, Оң 40% (бұрылыс)"));
  setBothMotors(80, 40);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Сол 40%, Оң 80% (бұрылыс)"));
  setBothMotors(40, 80);
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== ҚОЗҒАЛЫС ФУНКЦИЯЛАРЫН ПАЙДАЛАНУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ҚОЗҒАЛЫС ФУНКЦИЯЛАРЫ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ 60% жылдамдықпен алға"));
  moveForward(60);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ 50% жылдамдықпен артқа"));
  moveBackward(50);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Орнында оңға бұрылу"));
  turnRight(50);
  printMotorStatus();
  delay(1500);

  Serial.println(F("\n→ Орнында солға бұрылу"));
  turnLeft(50);
  printMotorStatus();
  delay(1500);

  stopAllMotors();
  delay(1000);

  // ========== ТЕГІС БҰРЫЛЫСТАР (ДОҒАЛАР) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТЕГІС БҰРЫЛЫСТАР (ДОҒАЛАР)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Оңға доға (негізгі жылдамдық 70)"));
  arcRight(70, 30);  // Оң қозғалтқыш 40-та (70-30)
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Солға доға (негізгі жылдамдық 70)"));
  arcLeft(70, 30);   // Сол қозғалтқыш 40-та (70-30)
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== СИНХРОНДЫ ТЕГІС ЖЫЛДАМДЫҚ ӨЗГЕРТУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("СИНХРОНДЫ ТЕГІС ӨЗГЕРТУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Тегіс үдеу: 0 → 80 2 секундта"));
  smoothBothMotors(80, 80, 2000);
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Тегіс баяулау: 80 → 30 1.5 секундта"));
  smoothBothMotors(30, 30, 1500);
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Тегіс тоқтату: 30 → 0 1 секундта"));
  smoothBothMotors(0, 0, 1000);
  printMotorStatus();
  delay(1000);

  // ========== КҮРДЕЛІ МАНЕВРЛЕР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("КҮРДЕЛІ МАНЕВРЛЕР"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Маневр 1: Төртбұрыш\n"));

  for (int side = 1; side <= 4; side++) {
    Serial.print(F("  Қабырға "));
    Serial.print(side);
    Serial.println(F(": Алға"));
    moveForward(60);
    delay(1500);

    Serial.println(F("  90° бұрылыс"));
    turnRight(50);
    delay(750);  // Шамамен 90 градус

    stopAllMotors();
    delay(300);
  }

  delay(1000);

  Serial.println(F("\nМаневр 2: Сегіз\n"));

  Serial.println(F("  Оң шеңбер:"));
  for (int i = 0; i < 4; i++) {
    arcRight(60, 40);
    delay(750);
  }

  Serial.println(F("  Сол шеңбер:"));
  for (int i = 0; i < 4; i++) {
    arcLeft(60, 40);
    delay(750);
  }

  stopAllMotors();
  delay(2000);

  // ========== ТӘУЕЛСІЗ БАСҚАРУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТӘУЕЛСІЗ БАСҚАРУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Сол жақ тегіс үдейді, оң жақ тұр"));
  for (int speed = 0; speed <= 80; speed += 5) {
    motorLeft.setSpeed(speed);
    // motorRight 0-де қалады
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Оң жақ сол жаққа жетеді"));
  for (int speed = 0; speed <= 80; speed += 5) {
    motorRight.setSpeed(speed);
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Екеуі де тегіс тоқтайды"));
  smoothBothMotors(0, 0, 1500);
  delay(1000);

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║      СИНХРОНДАУДЫҢ ЕҢ ЖАҚСЫ ТӘЖІРИБЕЛЕРІ      ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  1. Жиі операциялар үшін функциялар жасаңыз: ║"));
  Serial.println(F("║     • moveForward(speed)                      ║"));
  Serial.println(F("║     • turnLeft(speed)                         ║"));
  Serial.println(F("║     • stopAllMotors()                         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  2. Жылдамдықтарды кезекпен орнатыңыз:        ║"));
  Serial.println(F("║     motorLeft.setSpeed(speed);                ║"));
  Serial.println(F("║     motorRight.setSpeed(speed);               ║"));
  Serial.println(F("║     // Олардың арасында delay() ҚОЛДАНБАҢЫЗ! ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  3. Тегіс қозғалыс үшін пайдаланыңыз:         ║"));
  Serial.println(F("║     • Жалпы smoothBothMotors() функциясын     ║"));
  Serial.println(F("║     • Жылдамдықтарды синхронды өзгерту        ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  4. Ағымдағы күйді әрқашан тексеріңіз:        ║"));
  Serial.println(F("║     • getSpeed() қолданыңыз                   ║"));
  Serial.println(F("║     • Жөндеу үшін Serial-ға шығарыңыз         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  5. Роботтар үшін Robot класын жасаңыз:       ║"));
  Serial.println(F("║     class Robot {                             ║"));
  Serial.println(F("║       AlashMotorControlLite left, right;      ║"));
  Serial.println(F("║       void forward(int speed);                ║"));
  Serial.println(F("║       void turn(int angle);                   ║"));
  Serial.println(F("║     }                                          ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
