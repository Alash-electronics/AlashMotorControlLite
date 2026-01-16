// Language: Қазақ | English: ../EN/ESP32_Mecanum_4WD_Demo/ | Русский: ../RU/ESP32_Mecanum_4WD_Demo/
// TODO: Translate comments and strings to Kazakh
/*
 * Управление роботом с меканум колесами (4 мотора) на ESP32 с драйвером ZK-5AD
 *
 * Меканум колеса позволяют роботу двигаться в любом направлении:
 * - Вперед/назад
 * - Влево/вправо (страфинг)
 * - Диагональное движение
 * - Поворот на месте
 *
 * Подключение моторов (режим PWM_PWM):
 * Motor 1 (Передний левый):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Передний правый): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Задний левый):    IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Задний правый):    IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Расположение колес (вид сверху):
 *     ПЕРЕДНЯЯ ЧАСТЬ
 *    M1 ↗     ↖ M2
 *         [ ]
 *    M3 ↖     ↗ M4
 *     ЗАДНЯЯ ЧАСТЬ
 *
 * Направление роликов меканум-колес:
 * M1: / (диагональ вправо)
 * M2: \ (диагональ влево)
 * M3: \ (диагональ влево)
 * M4: / (диагональ вправо)
 *
 * Питание драйвера:
 * VCC -> 5V или 3.3V
 * GND -> GND
 * VM -> Питание моторов (6-12V)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Создаем объекты для 4 моторов в режиме PWM_PWM
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Передний левый (Front Left)
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Передний правый (Front Right)
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Задний левый (Rear Left)
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Задний правый (Rear Right)

// Функция для управления меканум-колесами
// vx: скорость вперед/назад (-100 до 100)
// vy: скорость влево/вправо (-100 до 100)
// rotation: скорость вращения (-100 до 100)
void mecanumDrive(int vx, int vy, int rotation) {
  // Формулы для меканум-колес
  int speedFL = vx + vy + rotation;  // Передний левый
  int speedFR = vx - vy - rotation;  // Передний правый
  int speedRL = vx - vy + rotation;  // Задний левый
  int speedRR = vx + vy - rotation;  // Задний правый

  // Ограничиваем скорости в диапазоне -100 до 100
  speedFL = constrain(speedFL, -100, 100);
  speedFR = constrain(speedFR, -100, 100);
  speedRL = constrain(speedRL, -100, 100);
  speedRR = constrain(speedRR, -100, 100);

  // Устанавливаем скорости моторов
  motorFL.setSpeed(speedFL);
  motorFR.setSpeed(speedFR);
  motorRL.setSpeed(speedRL);
  motorRR.setSpeed(speedRR);
}

// Функция для остановки всех моторов
void stopAll() {
  motorFL.stop();
  motorFR.stop();
  motorRL.stop();
  motorRR.stop();
}

// Функция для торможения всех моторов
void brakeAll() {
  motorFL.brake();
  motorFR.brake();
  motorRL.brake();
  motorRR.brake();
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 Mecanum 4WD Robot Control"));
  Serial.println(F("Инициализация завершена"));
  delay(2000);
}

void loop() {
  // ==================== Движение вперед ====================
  Serial.println(F("1. Движение вперед (50% скорости)"));
  mecanumDrive(50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("2. Движение вперед (100% скорости)"));
  mecanumDrive(100, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Движение назад ====================
  Serial.println(F("3. Движение назад (50% скорости)"));
  mecanumDrive(-50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Страфинг влево ====================
  Serial.println(F("4. Страфинг влево (движение боком)"));
  mecanumDrive(0, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Страфинг вправо ====================
  Serial.println(F("5. Страфинг вправо (движение боком)"));
  mecanumDrive(0, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Диагональное движение ====================
  Serial.println(F("6. Диагональное движение (вперед-влево)"));
  mecanumDrive(50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("7. Диагональное движение (вперед-вправо)"));
  mecanumDrive(50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("8. Диагональное движение (назад-влево)"));
  mecanumDrive(-50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("9. Диагональное движение (назад-вправо)"));
  mecanumDrive(-50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Поворот на месте ====================
  Serial.println(F("10. Поворот на месте по часовой стрелке"));
  mecanumDrive(0, 0, 50);
  delay(2000);

  brakeAll();
  delay(1000);

  Serial.println(F("11. Поворот на месте против часовой стрелки"));
  mecanumDrive(0, 0, -50);
  delay(2000);

  brakeAll();
  delay(1000);

  // ==================== Комбинированное движение ====================
  Serial.println(F("12. Движение по кругу (вперед + поворот)"));
  mecanumDrive(60, 0, 30);
  delay(3000);

  stopAll();
  delay(1000);

  Serial.println(F("13. Движение по дуге (вперед-влево + поворот)"));
  mecanumDrive(50, 30, 20);
  delay(3000);

  stopAll();
  delay(1000);

  // ==================== Сложная траектория ====================
  Serial.println(F("14. Квадратная траектория"));

  // Вперед
  Serial.println(F("  - Вперед"));
  mecanumDrive(70, 0, 0);
  delay(1500);

  // Страфинг вправо
  Serial.println(F("  - Вправо"));
  mecanumDrive(0, -70, 0);
  delay(1500);

  // Назад
  Serial.println(F("  - Назад"));
  mecanumDrive(-70, 0, 0);
  delay(1500);

  // Страфинг влево
  Serial.println(F("  - Влево"));
  mecanumDrive(0, 70, 0);
  delay(1500);

  brakeAll();
  delay(2000);

  Serial.println(F("Цикл завершен. Пауза 3 секунды...\n"));
  delay(3000);
}
