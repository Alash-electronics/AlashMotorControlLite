/*
 * Пример демонстрирует синхронизацию нескольких моторов
 *
 * При работе с несколькими моторами важно:
 * - Синхронизировать запуск и остановку
 * - Координировать скорости
 * - Создавать функции для группового управления
 * - Правильно организовать код
 *
 * Этот пример показывает лучшие практики для управления
 * несколькими моторами одновременно.
 *
 * Подключение для 2 моторов:
 * Arduino:
 *   Motor 1: DIR -> Pin 4, PWM -> Pin 3
 *   Motor 2: DIR -> Pin 7, PWM -> Pin 6
 *
 * ESP32:
 *   Motor 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 *   Motor 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Создаем объекты моторов
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32 - режим PWM_PWM
  AlashMotorControlLite motorLeft(PWM_PWM, 32, 33);
  AlashMotorControlLite motorRight(PWM_PWM, 25, 26);
#else
  // Arduino - режим DIR_PWM
  AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
  AlashMotorControlLite motorRight(DIR_PWM, 7, 6);
#endif

// ========== ФУНКЦИИ ДЛЯ ГРУППОВОГО УПРАВЛЕНИЯ ==========

// Синхронная установка скорости обоих моторов
void setBothMotors(int leftSpeed, int rightSpeed) {
  motorLeft.setSpeed(leftSpeed);
  motorRight.setSpeed(rightSpeed);
}

// Остановка всех моторов
void stopAllMotors() {
  motorLeft.stop();
  motorRight.stop();
}

// Торможение всех моторов
void brakeAllMotors() {
  motorLeft.brake();
  motorRight.brake();
}

// Плавное изменение скорости обоих моторов
void smoothBothMotors(int leftTarget, int rightTarget, unsigned long rampTime) {
  int leftCurrent = motorLeft.getSpeed();
  int rightCurrent = motorRight.getSpeed();

  int leftDiff = leftTarget - leftCurrent;
  int rightDiff = rightTarget - rightCurrent;

  int maxSteps = max(abs(leftDiff), abs(rightDiff));
  if (maxSteps == 0) return;

  unsigned long stepDelay = rampTime / maxSteps;

  for (int step = 1; step <= maxSteps; step++) {
    // Вычисляем текущую скорость для каждого мотора
    int leftSpeed = leftCurrent + (leftDiff * step / maxSteps);
    int rightSpeed = rightCurrent + (rightDiff * step / maxSteps);

    motorLeft.setSpeed(leftSpeed);
    motorRight.setSpeed(rightSpeed);

    delay(stepDelay);
  }

  // Гарантируем точное достижение целевых значений
  motorLeft.setSpeed(leftTarget);
  motorRight.setSpeed(rightTarget);
}

// Движение вперед
void moveForward(int speed) {
  setBothMotors(speed, speed);
}

// Движение назад
void moveBackward(int speed) {
  setBothMotors(-speed, -speed);
}

// Поворот на месте вправо
void turnRight(int speed) {
  setBothMotors(speed, -speed);
}

// Поворот на месте влево
void turnLeft(int speed) {
  setBothMotors(-speed, speed);
}

// Плавный поворот (дуга) вправо
void arcRight(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed - turnAmount;
  setBothMotors(leftSpeed, rightSpeed);
}

// Плавный поворот (дуга) влево
void arcLeft(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed - turnAmount;
  int rightSpeed = baseSpeed;
  setBothMotors(leftSpeed, rightSpeed);
}

// Вывод состояния всех моторов
void printMotorStatus() {
  Serial.print("Левый: ");
  Serial.print(motorLeft.getSpeed());
  Serial.print("  |  Правый: ");
  Serial.println(motorRight.getSpeed());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  СИНХРОНИЗАЦИЯ НЕСКОЛЬКИХ МОТОРОВ             ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== БАЗОВАЯ СИНХРОНИЗАЦИЯ ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("БАЗОВАЯ СИНХРОНИЗАЦИЯ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Одновременный запуск обоих моторов\n");

  Serial.println("ПЛОХО - моторы запускаются по очереди:");
  Serial.println("  motorLeft.setSpeed(80);");
  Serial.println("  delay(100);  // Левый уже работает!");
  Serial.println("  motorRight.setSpeed(80);\n");

  Serial.println("ХОРОШО - моторы запускаются синхронно:");
  Serial.println("  motorLeft.setSpeed(80);");
  Serial.println("  motorRight.setSpeed(80);  // Сразу после левого\n");

  Serial.println("Запускаем синхронно:");
  setBothMotors(70, 70);
  printMotorStatus();
  delay(2000);

  Serial.println("\n→ Одновременная остановка");
  stopAllMotors();
  printMotorStatus();
  delay(2000);

  // ========== РАЗНЫЕ СКОРОСТИ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("КООРДИНАЦИЯ РАЗНЫХ СКОРОСТЕЙ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Левый 80%, Правый 40% (поворот)");
  setBothMotors(80, 40);
  printMotorStatus();
  delay(2000);

  Serial.println("\n→ Левый 40%, Правый 80% (поворот)");
  setBothMotors(40, 80);
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== ИСПОЛЬЗОВАНИЕ ФУНКЦИЙ ДВИЖЕНИЯ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ФУНКЦИИ ДВИЖЕНИЯ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Вперед на 60%");
  moveForward(60);
  printMotorStatus();
  delay(2000);

  Serial.println("\n→ Назад на 50%");
  moveBackward(50);
  printMotorStatus();
  delay(2000);

  Serial.println("\n→ Поворот на месте вправо");
  turnRight(50);
  printMotorStatus();
  delay(1500);

  Serial.println("\n→ Поворот на месте влево");
  turnLeft(50);
  printMotorStatus();
  delay(1500);

  stopAllMotors();
  delay(1000);

  // ========== ПЛАВНЫЕ ПОВОРОТЫ (ДУГИ) ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ПЛАВНЫЕ ПОВОРОТЫ (ДУГИ)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Дуга вправо (базовая скорость 70)");
  arcRight(70, 30);  // Правый мотор на 40 (70-30)
  printMotorStatus();
  delay(2000);

  Serial.println("\n→ Дуга влево (базовая скорость 70)");
  arcLeft(70, 30);   // Левый мотор на 40 (70-30)
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== СИНХРОННАЯ ПЛАВНАЯ СМЕНА СКОРОСТИ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("СИНХРОННОЕ ПЛАВНОЕ ИЗМЕНЕНИЕ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Плавный разгон: 0 → 80 за 2 секунды");
  smoothBothMotors(80, 80, 2000);
  printMotorStatus();
  delay(1000);

  Serial.println("\n→ Плавное замедление: 80 → 30 за 1.5 секунды");
  smoothBothMotors(30, 30, 1500);
  printMotorStatus();
  delay(1000);

  Serial.println("\n→ Плавная остановка: 30 → 0 за 1 секунду");
  smoothBothMotors(0, 0, 1000);
  printMotorStatus();
  delay(1000);

  // ========== СЛОЖНЫЕ МАНЕВРЫ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("СЛОЖНЫЕ МАНЕВРЫ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Маневр 1: Квадрат\n");

  for (int side = 1; side <= 4; side++) {
    Serial.print("  Сторона ");
    Serial.print(side);
    Serial.println(": Вперед");
    moveForward(60);
    delay(1500);

    Serial.println("  Поворот на 90°");
    turnRight(50);
    delay(750);  // Примерно 90 градусов

    stopAllMotors();
    delay(300);
  }

  delay(1000);

  Serial.println("\nМаневр 2: Восьмерка\n");

  Serial.println("  Правый круг:");
  for (int i = 0; i < 4; i++) {
    arcRight(60, 40);
    delay(750);
  }

  Serial.println("  Левый круг:");
  for (int i = 0; i < 4; i++) {
    arcLeft(60, 40);
    delay(750);
  }

  stopAllMotors();
  delay(2000);

  // ========== НЕЗАВИСИМОЕ УПРАВЛЕНИЕ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("НЕЗАВИСИМОЕ УПРАВЛЕНИЕ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Левый плавно разгоняется, правый стоит");
  for (int speed = 0; speed <= 80; speed += 5) {
    motorLeft.setSpeed(speed);
    // motorRight остается на 0
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println("\n→ Правый догоняет левый");
  for (int speed = 0; speed <= 80; speed += 5) {
    motorRight.setSpeed(speed);
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println("\n→ Оба плавно останавливаются");
  smoothBothMotors(0, 0, 1500);
  delay(1000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("\n╔═══════════════════════════════════════════════╗");
  Serial.println("║      ЛУЧШИЕ ПРАКТИКИ СИНХРОНИЗАЦИИ            ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  1. Создавайте функции для частых операций:   ║");
  Serial.println("║     • moveForward(speed)                      ║");
  Serial.println("║     • turnLeft(speed)                         ║");
  Serial.println("║     • stopAllMotors()                         ║");
  Serial.println("║                                                ║");
  Serial.println("║  2. Устанавливайте скорости последовательно:  ║");
  Serial.println("║     motorLeft.setSpeed(speed);                ║");
  Serial.println("║     motorRight.setSpeed(speed);               ║");
  Serial.println("║     // НЕ используйте delay() между ними!     ║");
  Serial.println("║                                                ║");
  Serial.println("║  3. Для плавных движений используйте:         ║");
  Serial.println("║     • Общую функцию smoothBothMotors()        ║");
  Serial.println("║     • Синхронное изменение скоростей          ║");
  Serial.println("║                                                ║");
  Serial.println("║  4. Всегда проверяйте текущее состояние:      ║");
  Serial.println("║     • Используйте getSpeed()                  ║");
  Serial.println("║     • Выводите в Serial для отладки           ║");
  Serial.println("║                                                ║");
  Serial.println("║  5. Для роботов создайте класс Robot:         ║");
  Serial.println("║     class Robot {                             ║");
  Serial.println("║       AlashMotorControlLite left, right;      ║");
  Serial.println("║       void forward(int speed);                ║");
  Serial.println("║       void turn(int angle);                   ║");
  Serial.println("║     }                                          ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("Цикл завершен. Повтор через 5 секунд...\n\n");
  delay(5000);
}
