// Language: Русский | English: ../EN/GettersDemo/ | Қазақ: ../KZ/GettersDemo/
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

  Serial.print(F("┌─────────────────────────────────┐\n"));
  Serial.print(F("│ СОСТОЯНИЕ МОТОРА                │\n"));
  Serial.print(F("├─────────────────────────────────┤\n"));
  Serial.print(F("│ Скорость: "));
  Serial.print(currentSpeed);
  Serial.print(F(" "));

  // Индикатор направления
  if (currentSpeed > 0) {
    Serial.print(F("→ Вперед"));
  } else if (currentSpeed < 0) {
    Serial.print(F("← Назад"));
  } else {
    Serial.print(F("■ Остановлен"));
  }

  // Дополняем пробелами для выравнивания
  int spaces = 15 - String(currentSpeed).length();
  if (currentSpeed >= 0) spaces -= 8;  // "→ Вперед"
  else spaces -= 7;                     // "← Назад"
  if (currentSpeed == 0) spaces = 7;    // "■ Остановлен"

  for (int i = 0; i < spaces; i++) {
    Serial.print(F(" "));
  }
  Serial.print(F("│\n"));

  Serial.print(F("│ Режим:    "));

  switch(currentMode) {
    case DIR_PWM:
      Serial.print(F("DIR_PWM"));
      Serial.print(F("          "));
      break;
    case PWM_PWM:
      Serial.print(F("PWM_PWM"));
      Serial.print(F("          "));
      break;
    case DIR_DIR_PWM:
      Serial.print(F("DIR_DIR_PWM"));
      Serial.print(F("      "));
      break;
    case DIR_DIR:
      Serial.print(F("DIR_DIR"));
      Serial.print(F("          "));
      break;
  }

  Serial.print(F("│\n"));
  Serial.print(F("└─────────────────────────────────┘\n\n"));
}

// Функция для отображения графика скорости
void printSpeedGraph() {
  int16_t speed = motor.getSpeed();
  Serial.print(F("График: "));

  // Отображаем график от -100 до +100
  if (speed < 0) {
    // Движение назад
    int bars = map(abs(speed), 0, 100, 0, 20);
    for (int i = 20; i > bars; i--) Serial.print(F(" "));
    for (int i = 0; i < bars; i++) Serial.print(F("◄"));
    Serial.print(F("|"));
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
  } else if (speed > 0) {
    // Движение вперед
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
    int bars = map(speed, 0, 100, 0, 20);
    for (int i = 0; i < bars; i++) Serial.print(F("►"));
  } else {
    // Остановка
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  ДЕМОНСТРАЦИЯ GETTER-МЕТОДОВ                  ║"));
  Serial.println(F("║  getSpeed() и getMode()                       ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== ДЕМОНСТРАЦИЯ getSpeed() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("ДЕМОНСТРАЦИЯ getSpeed()"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Постепенное увеличение скорости вперед\n"));

  for (int speed = 0; speed <= 100; speed += 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() возвращает: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  delay(1000);

  Serial.println(F("\n→ Постепенное увеличение скорости назад\n"));

  for (int speed = 0; speed >= -100; speed -= 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() возвращает: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  motor.stop();
  delay(2000);

  // ========== ДЕМОНСТРАЦИЯ МОНИТОРИНГА ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("МОНИТОРИНГ СОСТОЯНИЯ МОТОРА"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Разгон до 75%"));
  motor.setSpeed(75);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Снижение до 50%"));
  motor.setSpeed(50);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Реверс до -80%"));
  motor.setSpeed(-80);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Остановка"));
  motor.stop();
  delay(500);
  printMotorStatus();

  // ========== УСЛОВНАЯ ЛОГИКА ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("УСЛОВНАЯ ЛОГИКА НА ОСНОВЕ getSpeed()"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  motor.setSpeed(100);
  delay(500);

  if (motor.getSpeed() > 50) {
    Serial.println(F("✓ Скорость высокая (>50), включаем светодиод"));
  }

  if (motor.getSpeed() > 0) {
    Serial.println(F("✓ Мотор движется вперед"));
  } else if (motor.getSpeed() < 0) {
    Serial.println(F("✓ Мотор движется назад"));
  } else {
    Serial.println(F("✓ Мотор остановлен"));
  }

  delay(2000);
  motor.setSpeed(-60);
  delay(500);

  if (motor.getSpeed() < -50) {
    Serial.println(F("⚠ Высокая скорость назад, осторожно!"));
  }

  delay(2000);
  motor.brake();
  delay(500);

  if (motor.getSpeed() == 0) {
    Serial.println(F("✓ Мотор полностью остановлен"));
  }

  // ========== ДЕМОНСТРАЦИЯ getMode() ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ДЕМОНСТРАЦИЯ getMode()"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Текущий режим работы драйвера:"));
  printMotorStatus();

  Serial.println(F("Режим устанавливается при создании объекта мотора"));
  Serial.println(F("и не может быть изменен во время работы.\n"));

  Serial.println(F("Режим полезен для:"));
  Serial.println(F("  • Отладки подключения"));
  Serial.println(F("  • Автоматической настройки параметров"));
  Serial.println(F("  • Документирования конфигурации\n"));

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║         ПРИМЕНЕНИЕ GETTER-МЕТОДОВ             ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  getSpeed():                                  ║"));
  Serial.println(F("║    • Мониторинг текущей скорости              ║"));
  Serial.println(F("║    • Условная логика                          ║"));
  Serial.println(F("║    • Телеметрия и логирование                 ║"));
  Serial.println(F("║    • Проверка состояния                       ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  getMode():                                    ║"));
  Serial.println(F("║    • Проверка конфигурации                    ║"));
  Serial.println(F("║    • Отладка                                  ║"));
  Serial.println(F("║    • Универсальные функции                    ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл завершен. Повтор через 5 секунд...\n\n"));
  delay(5000);
}
