/*
 * Пример демонстрирует автоматическое ограничение скорости
 *
 * Библиотека автоматически ограничивает значения скорости в диапазоне -100 до 100:
 * - Значения > 100 автоматически устанавливаются как 100
 * - Значения < -100 автоматически устанавливаются как -100
 * - Это защищает от ошибок программирования
 *
 * Этот пример показывает, как работает защита и как правильно
 * использовать диапазон скоростей.
 *
 * Подключение:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (режим DIR_PWM)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (режим PWM_PWM)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Выберите режим для вашей платформы:
#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

void testSpeed(int requestedSpeed) {
  motor.setSpeed(requestedSpeed);
  int actualSpeed = motor.getSpeed();

  Serial.print("Запрошено: ");
  if (requestedSpeed >= 0) Serial.print(" ");
  Serial.print(requestedSpeed);
  Serial.print("  →  Установлено: ");
  if (actualSpeed >= 0) Serial.print(" ");
  Serial.print(actualSpeed);

  if (requestedSpeed != actualSpeed) {
    Serial.print("  ⚠ ОГРАНИЧЕНО!");
  } else {
    Serial.print("  ✓");
  }

  Serial.println();
  delay(500);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  АВТОМАТИЧЕСКОЕ ОГРАНИЧЕНИЕ СКОРОСТИ          ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== ТЕСТИРОВАНИЕ ДОПУСТИМЫХ ЗНАЧЕНИЙ ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("ДОПУСТИМЫЕ ЗНАЧЕНИЯ (от -100 до 100)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Тестирование положительных скоростей:");
  testSpeed(0);
  testSpeed(25);
  testSpeed(50);
  testSpeed(75);
  testSpeed(100);

  Serial.println("\nТестирование отрицательных скоростей:");
  testSpeed(0);
  testSpeed(-25);
  testSpeed(-50);
  testSpeed(-75);
  testSpeed(-100);

  motor.stop();
  delay(2000);

  // ========== ТЕСТИРОВАНИЕ ВЫХОДА ЗА ПРЕДЕЛЫ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ВЫХОД ЗА ВЕРХНИЙ ПРЕДЕЛ (+100)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Библиотека автоматически ограничит значения:\n");

  testSpeed(100);   // Норма
  testSpeed(101);   // Будет ограничено до 100
  testSpeed(120);   // Будет ограничено до 100
  testSpeed(150);   // Будет ограничено до 100
  testSpeed(200);   // Будет ограничено до 100
  testSpeed(255);   // Будет ограничено до 100
  testSpeed(500);   // Будет ограничено до 100
  testSpeed(1000);  // Будет ограничено до 100
  testSpeed(32767); // Будет ограничено до 100

  motor.stop();
  delay(2000);

  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ВЫХОД ЗА НИЖНИЙ ПРЕДЕЛ (-100)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Библиотека автоматически ограничит значения:\n");

  testSpeed(-100);   // Норма
  testSpeed(-101);   // Будет ограничено до -100
  testSpeed(-120);   // Будет ограничено до -100
  testSpeed(-150);   // Будет ограничено до -100
  testSpeed(-200);   // Будет ограничено до -100
  testSpeed(-255);   // Будет ограничено до -100
  testSpeed(-500);   // Будет ограничено до -100
  testSpeed(-1000);  // Будет ограничено до -100
  testSpeed(-32768); // Будет ограничено до -100

  motor.stop();
  delay(2000);

  // ========== ПРАКТИЧЕСКИЕ ПРИМЕРЫ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ПРАКТИЧЕСКИЕ ПРИМЕРЫ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Пример 1: Безопасное суммирование скоростей\n");

  Serial.println("int baseSpeed = 80;");
  Serial.println("int boost = 30;");
  Serial.println("motor.setSpeed(baseSpeed + boost);  // 80 + 30 = 110\n");

  int baseSpeed = 80;
  int boost = 30;

  Serial.print("Результат: ");
  testSpeed(baseSpeed + boost);  // Автоматически ограничится до 100

  Serial.println("\nБиблиотека защищает от превышения!\n");
  delay(2000);

  Serial.println("Пример 2: Использование процентов\n");

  Serial.println("int userInput = 150;  // Пользователь ввел 150%");
  Serial.println("motor.setSpeed(userInput);\n");

  int userInput = 150;
  Serial.print("Результат: ");
  testSpeed(userInput);  // Автоматически ограничится до 100

  Serial.println("\nДаже неправильный ввод безопасен!\n");
  delay(2000);

  Serial.println("Пример 3: Математические вычисления\n");

  Serial.println("int sensorValue = analogRead(A0);  // 0-1023");
  Serial.println("int speed = map(sensorValue, 0, 1023, -200, 200);");
  Serial.println("motor.setSpeed(speed);\n");

  // Симулируем разные значения датчика
  Serial.println("При sensorValue = 0:");
  testSpeed(-200);  // Ограничится до -100

  Serial.println("При sensorValue = 512:");
  testSpeed(0);     // Середина

  Serial.println("При sensorValue = 1023:");
  testSpeed(200);   // Ограничится до 100

  Serial.println("\nДаже при неправильном map() защита работает!\n");

  motor.stop();
  delay(2000);

  // ========== ГРАНИЧНЫЕ ЗНАЧЕНИЯ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ГРАНИЧНЫЕ ЗНАЧЕНИЯ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Точные границы диапазона:\n");

  testSpeed(99);    // Последнее допустимое перед максимумом
  testSpeed(100);   // Максимум
  testSpeed(101);   // Первое ограничиваемое

  Serial.println();

  testSpeed(-99);   // Последнее допустимое перед минимумом
  testSpeed(-100);  // Минимум
  testSpeed(-101);  // Первое ограничиваемое

  motor.stop();
  delay(2000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("\n╔═══════════════════════════════════════════════╗");
  Serial.println("║        РЕКОМЕНДАЦИИ ПО ИСПОЛЬЗОВАНИЮ          ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  Диапазон скорости: -100 до 100               ║");
  Serial.println("║                                                ║");
  Serial.println("║  Значения:                                     ║");
  Serial.println("║    -100 = Полная скорость назад               ║");
  Serial.println("║      -50 = 50% назад                          ║");
  Serial.println("║        0 = Остановка                          ║");
  Serial.println("║      +50 = 50% вперед                         ║");
  Serial.println("║     +100 = Полная скорость вперед             ║");
  Serial.println("║                                                ║");
  Serial.println("║  Защита работает автоматически:               ║");
  Serial.println("║    • Значения > 100 → устанавливается 100     ║");
  Serial.println("║    • Значения < -100 → устанавливается -100   ║");
  Serial.println("║                                                ║");
  Serial.println("║  Хорошая практика:                            ║");
  Serial.println("║    ✓ Используйте constrain() перед setSpeed() ║");
  Serial.println("║    ✓ Проверяйте map() для корректности       ║");
  Serial.println("║    ✓ Валидируйте пользовательский ввод       ║");
  Serial.println("║                                                ║");
  Serial.println("║  Но даже если забудете - защита сработает!   ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  // ========== КОД-ПРИМЕР ==========
  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║              ПРИМЕРЫ КОДА                     ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("// Правильно: с проверкой");
  Serial.println("int speed = analogRead(A0);");
  Serial.println("speed = map(speed, 0, 1023, -100, 100);");
  Serial.println("motor.setSpeed(speed);\n");

  Serial.println("// Тоже работает: библиотека защитит");
  Serial.println("int speed = analogRead(A0);");
  Serial.println("speed = map(speed, 0, 1023, -200, 200);");
  Serial.println("motor.setSpeed(speed);  // Ограничится автоматически\n");

  Serial.println("// С дополнительной защитой:");
  Serial.println("int speed = getUserInput();");
  Serial.println("speed = constrain(speed, -100, 100);");
  Serial.println("motor.setSpeed(speed);  // Двойная защита\n");

  Serial.println("Цикл завершен. Повтор через 5 секунд...\n\n");
  delay(5000);
}
