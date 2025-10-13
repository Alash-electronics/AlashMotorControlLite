/*
 * Пример демонстрирует использование getter-методов библиотеки:
 * - getSpeed() - получить текущую скорость мотора
 * - getMode()  - получить режим работы драйвера
 *
 * Эти методы полезны для:
 * - Мониторинга состояния моторов
 * - Отладки программы
 * - Создания телеметрии
 * - Условной логики на основе состояния
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

// Функция для вывода текущего состояния мотора
void printMotorStatus() {
  int16_t currentSpeed = motor.getSpeed();
  MODE currentMode = motor.getMode();

  Serial.print("┌─────────────────────────────────┐\n");
  Serial.print("│ СОСТОЯНИЕ МОТОРА                │\n");
  Serial.print("├─────────────────────────────────┤\n");
  Serial.print("│ Скорость: ");
  Serial.print(currentSpeed);
  Serial.print(" ");

  // Индикатор направления
  if (currentSpeed > 0) {
    Serial.print("→ Вперед");
  } else if (currentSpeed < 0) {
    Serial.print("← Назад");
  } else {
    Serial.print("■ Остановлен");
  }

  // Дополняем пробелами для выравнивания
  int spaces = 15 - String(currentSpeed).length();
  if (currentSpeed >= 0) spaces -= 8;  // "→ Вперед"
  else spaces -= 7;                     // "← Назад"
  if (currentSpeed == 0) spaces = 7;    // "■ Остановлен"

  for (int i = 0; i < spaces; i++) {
    Serial.print(" ");
  }
  Serial.print("│\n");

  Serial.print("│ Режим:    ");

  switch(currentMode) {
    case DIR_PWM:
      Serial.print("DIR_PWM");
      Serial.print("          ");
      break;
    case PWM_PWM:
      Serial.print("PWM_PWM");
      Serial.print("          ");
      break;
    case DIR_DIR_PWM:
      Serial.print("DIR_DIR_PWM");
      Serial.print("      ");
      break;
    case DIR_DIR:
      Serial.print("DIR_DIR");
      Serial.print("          ");
      break;
  }

  Serial.print("│\n");
  Serial.print("└─────────────────────────────────┘\n\n");
}

// Функция для отображения графика скорости
void printSpeedGraph() {
  int16_t speed = motor.getSpeed();
  Serial.print("График: ");

  // Отображаем график от -100 до +100
  if (speed < 0) {
    // Движение назад
    int bars = map(abs(speed), 0, 100, 0, 20);
    for (int i = 20; i > bars; i--) Serial.print(" ");
    for (int i = 0; i < bars; i++) Serial.print("◄");
    Serial.print("|");
    for (int i = 0; i < 20; i++) Serial.print(" ");
  } else if (speed > 0) {
    // Движение вперед
    for (int i = 0; i < 20; i++) Serial.print(" ");
    Serial.print("|");
    int bars = map(speed, 0, 100, 0, 20);
    for (int i = 0; i < bars; i++) Serial.print("►");
  } else {
    // Остановка
    for (int i = 0; i < 20; i++) Serial.print(" ");
    Serial.print("|");
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  ДЕМОНСТРАЦИЯ GETTER-МЕТОДОВ                  ║");
  Serial.println("║  getSpeed() и getMode()                       ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== ДЕМОНСТРАЦИЯ getSpeed() ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("ДЕМОНСТРАЦИЯ getSpeed()");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Постепенное увеличение скорости вперед\n");

  for (int speed = 0; speed <= 100; speed += 20) {
    motor.setSpeed(speed);

    Serial.print("motor.setSpeed(");
    Serial.print(speed);
    Serial.print(") → getSpeed() возвращает: ");
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  delay(1000);

  Serial.println("\n→ Постепенное увеличение скорости назад\n");

  for (int speed = 0; speed >= -100; speed -= 20) {
    motor.setSpeed(speed);

    Serial.print("motor.setSpeed(");
    Serial.print(speed);
    Serial.print(") → getSpeed() возвращает: ");
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  motor.stop();
  delay(2000);

  // ========== ДЕМОНСТРАЦИЯ МОНИТОРИНГА ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("МОНИТОРИНГ СОСТОЯНИЯ МОТОРА");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Разгон до 75%");
  motor.setSpeed(75);
  delay(500);
  printMotorStatus();

  Serial.println("→ Снижение до 50%");
  motor.setSpeed(50);
  delay(500);
  printMotorStatus();

  Serial.println("→ Реверс до -80%");
  motor.setSpeed(-80);
  delay(500);
  printMotorStatus();

  Serial.println("→ Остановка");
  motor.stop();
  delay(500);
  printMotorStatus();

  // ========== УСЛОВНАЯ ЛОГИКА ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("УСЛОВНАЯ ЛОГИКА НА ОСНОВЕ getSpeed()");
  Serial.println("═══════════════════════════════════════════════\n");

  motor.setSpeed(100);
  delay(500);

  if (motor.getSpeed() > 50) {
    Serial.println("✓ Скорость высокая (>50), включаем светодиод");
  }

  if (motor.getSpeed() > 0) {
    Serial.println("✓ Мотор движется вперед");
  } else if (motor.getSpeed() < 0) {
    Serial.println("✓ Мотор движется назад");
  } else {
    Serial.println("✓ Мотор остановлен");
  }

  delay(2000);
  motor.setSpeed(-60);
  delay(500);

  if (motor.getSpeed() < -50) {
    Serial.println("⚠ Высокая скорость назад, осторожно!");
  }

  delay(2000);
  motor.brake();
  delay(500);

  if (motor.getSpeed() == 0) {
    Serial.println("✓ Мотор полностью остановлен");
  }

  // ========== ДЕМОНСТРАЦИЯ getMode() ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ДЕМОНСТРАЦИЯ getMode()");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Текущий режим работы драйвера:");
  printMotorStatus();

  Serial.println("Режим устанавливается при создании объекта мотора");
  Serial.println("и не может быть изменен во время работы.\n");

  Serial.println("Режим полезен для:");
  Serial.println("  • Отладки подключения");
  Serial.println("  • Автоматической настройки параметров");
  Serial.println("  • Документирования конфигурации\n");

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("\n╔═══════════════════════════════════════════════╗");
  Serial.println("║         ПРИМЕНЕНИЕ GETTER-МЕТОДОВ             ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  getSpeed():                                  ║");
  Serial.println("║    • Мониторинг текущей скорости              ║");
  Serial.println("║    • Условная логика                          ║");
  Serial.println("║    • Телеметрия и логирование                 ║");
  Serial.println("║    • Проверка состояния                       ║");
  Serial.println("║                                                ║");
  Serial.println("║  getMode():                                    ║");
  Serial.println("║    • Проверка конфигурации                    ║");
  Serial.println("║    • Отладка                                  ║");
  Serial.println("║    • Универсальные функции                    ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("Цикл завершен. Повтор через 5 секунд...\n\n");
  delay(5000);
}
