// Language: Қазақ | English: ../EN/ESP32_Mecanum_4WD_Demo/ | Русский: ../RU/ESP32_Mecanum_4WD_Demo/
/*
 * ZK-5AD драйверімен ESP32 үшін меканум дөңгелектері бар роботты басқару (4 қозғалтқыш)
 *
 * Меканум дөңгелектері роботқа кез келген бағытта қозғалуға мүмкіндік береді:
 * - Алға/артқа
 * - Солға/оңға (бүйірлік қозғалыс)
 * - Диагональді қозғалыс
 * - Орнында айналу
 *
 * Қозғалтқыштарды қосу (режим PWM_PWM):
 * Motor 1 (Алдыңғы сол):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Алдыңғы оң): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Артқы сол):    IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Артқы оң):    IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Дөңгелектердің орналасуы (жоғарыдан көрініс):
 *     АЛДЫҢҒЫ БӨЛІК
 *    M1 ↗     ↖ M2
 *         [ ]
 *    M3 ↖     ↗ M4
 *     АРТҚЫ БӨЛІК
 *
 * Меканум дөңгелектерінің роликтер бағыты:
 * M1: / (оңға қарай диагональ)
 * M2: \ (солға қарай диагональ)
 * M3: \ (солға қарай диагональ)
 * M4: / (оңға қарай диагональ)
 *
 * Драйверді қуаттандыру:
 * VCC -> 5V немесе 3.3V
 * GND -> GND
 * VM -> Қозғалтқыштарға қуат (6-12V)
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// PWM_PWM режимінде 4 қозғалтқыш үшін объектілер жасаймыз
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Алдыңғы сол (Front Left)
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Алдыңғы оң (Front Right)
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Артқы сол (Rear Left)
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Артқы оң (Rear Right)

// Меканум дөңгелектерді басқару функциясы
// vx: алға/артқа жылдамдық (-100 ден 100 дейін)
// vy: солға/оңға жылдамдық (-100 ден 100 дейін)
// rotation: айналу жылдамдығы (-100 ден 100 дейін)
void mecanumDrive(int vx, int vy, int rotation) {
  // Меканум дөңгелектері үшін формулалар
  int speedFL = vx + vy + rotation;  // Алдыңғы сол
  int speedFR = vx - vy - rotation;  // Алдыңғы оң
  int speedRL = vx - vy + rotation;  // Артқы сол
  int speedRR = vx + vy - rotation;  // Артқы оң

  // Жылдамдықты -100 ден 100 дейінгі диапазонда шектейміз
  speedFL = constrain(speedFL, -100, 100);
  speedFR = constrain(speedFR, -100, 100);
  speedRL = constrain(speedRL, -100, 100);
  speedRR = constrain(speedRR, -100, 100);

  // Қозғалтқыштардың жылдамдығын орнатамыз
  motorFL.setSpeed(speedFL);
  motorFR.setSpeed(speedFR);
  motorRL.setSpeed(speedRL);
  motorRR.setSpeed(speedRR);
}

// Барлық қозғалтқыштарды тоқтату функциясы
void stopAll() {
  motorFL.stop();
  motorFR.stop();
  motorRL.stop();
  motorRR.stop();
}

// Барлық қозғалтқыштарды тежеу функциясы
void brakeAll() {
  motorFL.brake();
  motorFR.brake();
  motorRL.brake();
  motorRR.brake();
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 Mecanum 4WD Robot Control"));
  Serial.println(F("Инициализация аяқталды"));
  delay(2000);
}

void loop() {
  // ==================== Алға қозғалыс ====================
  Serial.println(F("1. Алға қозғалыс (50% жылдамдық)"));
  mecanumDrive(50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("2. Алға қозғалыс (100% жылдамдық)"));
  mecanumDrive(100, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Артқа қозғалыс ====================
  Serial.println(F("3. Артқа қозғалыс (50% жылдамдық)"));
  mecanumDrive(-50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Солға бүйірлік қозғалыс ====================
  Serial.println(F("4. Солға бүйірлік қозғалыс (бүйірімен)"));
  mecanumDrive(0, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Оңға бүйірлік қозғалыс ====================
  Serial.println(F("5. Оңға бүйірлік қозғалыс (бүйірімен)"));
  mecanumDrive(0, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Диагональді қозғалыс ====================
  Serial.println(F("6. Диагональді қозғалыс (алға-солға)"));
  mecanumDrive(50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("7. Диагональді қозғалыс (алға-оңға)"));
  mecanumDrive(50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("8. Диагональді қозғалыс (артқа-солға)"));
  mecanumDrive(-50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("9. Диагональді қозғалыс (артқа-оңға)"));
  mecanumDrive(-50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Орнында айналу ====================
  Serial.println(F("10. Орнында сағат тілі бойынша айналу"));
  mecanumDrive(0, 0, 50);
  delay(2000);

  brakeAll();
  delay(1000);

  Serial.println(F("11. Орнында сағат тіліне қарсы айналу"));
  mecanumDrive(0, 0, -50);
  delay(2000);

  brakeAll();
  delay(1000);

  // ==================== Біріктірілген қозғалыс ====================
  Serial.println(F("12. Дөңгелекпен қозғалыс (алға + айналу)"));
  mecanumDrive(60, 0, 30);
  delay(3000);

  stopAll();
  delay(1000);

  Serial.println(F("13. Доғамен қозғалыс (алға-солға + айналу)"));
  mecanumDrive(50, 30, 20);
  delay(3000);

  stopAll();
  delay(1000);

  // ==================== Күрделі траектория ====================
  Serial.println(F("14. Төртбұрышты траектория"));

  // Алға
  Serial.println(F("  - Алға"));
  mecanumDrive(70, 0, 0);
  delay(1500);

  // Оңға бүйірлік қозғалыс
  Serial.println(F("  - Оңға"));
  mecanumDrive(0, -70, 0);
  delay(1500);

  // Артқа
  Serial.println(F("  - Артқа"));
  mecanumDrive(-70, 0, 0);
  delay(1500);

  // Солға бүйірлік қозғалыс
  Serial.println(F("  - Солға"));
  mecanumDrive(0, 70, 0);
  delay(1500);

  brakeAll();
  delay(2000);

  Serial.println(F("Цикл аяқталды. Кідіріс 3 секунд...\n"));
  delay(3000);
}
