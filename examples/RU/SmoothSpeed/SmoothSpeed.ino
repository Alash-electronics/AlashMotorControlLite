// Language: Русский | English: ../EN/SmoothSpeed/ | Қазақ: ../KZ/SmoothSpeed/
/*
 * Пример демонстрирует плавное изменение скорости (Ramping)
 *
 * Плавное изменение скорости важно для:
 * - Защиты механики от рывков и ударных нагрузок
 * - Продления срока службы моторов и редукторов
 * - Предотвращения проскальзывания колес
 * - Плавного движения робота
 * - Снижения пикового потребления тока
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

// Функция для плавного изменения скорости
// targetSpeed: целевая скорость (-100 до 100)
// rampTime: время разгона/торможения в миллисекундах
void smoothSetSpeed(int targetSpeed, unsigned long rampTime) {
  int currentSpeed = motor.getSpeed();
  int speedDiff = targetSpeed - currentSpeed;
  int steps = abs(speedDiff);

  if (steps == 0) return;  // Уже на целевой скорости

  unsigned long stepDelay = rampTime / steps;

  Serial.print(F("Плавное изменение: "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.print(targetSpeed);
  Serial.print(F(" за "));
  Serial.print(rampTime);
  Serial.println(F(" мс"));

  if (speedDiff > 0) {
    // Увеличиваем скорость
    for (int speed = currentSpeed + 1; speed <= targetSpeed; speed++) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  } else {
    // Уменьшаем скорость
    for (int speed = currentSpeed - 1; speed >= targetSpeed; speed--) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  }

  Serial.println(F("  ✓ Достигнута целевая скорость\n"));
}

// Функция для плавного изменения скорости с заданным ускорением
// targetSpeed: целевая скорость (-100 до 100)
// acceleration: ускорение (единиц скорости за шаг)
// stepDelay: задержка между шагами в миллисекундах
void smoothSetSpeedAccel(int targetSpeed, int acceleration, unsigned long stepDelay) {
  int currentSpeed = motor.getSpeed();

  Serial.print(F("Плавное изменение с ускорением "));
  Serial.print(acceleration);
  Serial.print(F(": "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.println(targetSpeed);

  while (currentSpeed != targetSpeed) {
    int diff = targetSpeed - currentSpeed;

    if (abs(diff) <= acceleration) {
      // Достигаем целевой скорости
      currentSpeed = targetSpeed;
    } else if (diff > 0) {
      // Увеличиваем скорость
      currentSpeed += acceleration;
    } else {
      // Уменьшаем скорость
      currentSpeed -= acceleration;
    }

    motor.setSpeed(currentSpeed);
    delay(stepDelay);
  }

  Serial.println(F("  ✓ Достигнута целевая скорость\n"));
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  ПЛАВНОЕ ИЗМЕНЕНИЕ СКОРОСТИ (RAMPING)         ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== СРАВНЕНИЕ: Резкое VS Плавное ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СРАВНЕНИЕ: Резкое vs Плавное изменение"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("❌ РЕЗКОЕ изменение (может повредить механику):"));
  motor.setSpeed(0);
  delay(500);
  Serial.println(F("motor.setSpeed(100) - мгновенный рывок!"));
  motor.setSpeed(100);
  delay(2000);

  motor.stop();
  delay(1000);

  Serial.println(F("\n✓ ПЛАВНОЕ изменение (безопасно для механики):"));
  motor.setSpeed(0);
  delay(500);
  smoothSetSpeed(100, 2000);  // Плавный разгон за 2 секунды
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== РАЗНЫЕ ВРЕМЕНА РАЗГОНА ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РАЗНЫЕ ВРЕМЕНА РАЗГОНА"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Быстрый разгон (1 секунда):"));
  smoothSetSpeed(80, 1000);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("→ Средний разгон (2 секунды):"));
  smoothSetSpeed(80, 2000);
  delay(1000);
  smoothSetSpeed(0, 2000);
  delay(1000);

  Serial.println(F("→ Медленный разгон (3 секунды):"));
  smoothSetSpeed(80, 3000);
  delay(1000);
  smoothSetSpeed(0, 3000);
  delay(2000);

  // ========== УСКОРЕНИЕ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("УПРАВЛЕНИЕ УСКОРЕНИЕМ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Малое ускорение (плавно):"));
  smoothSetSpeedAccel(90, 2, 50);  // +2 единицы каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 2, 50);
  delay(1000);

  Serial.println(F("→ Среднее ускорение:"));
  smoothSetSpeedAccel(90, 5, 50);  // +5 единиц каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 5, 50);
  delay(1000);

  Serial.println(F("→ Большое ускорение (быстро):"));
  smoothSetSpeedAccel(90, 10, 50);  // +10 единиц каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 10, 50);
  delay(2000);

  // ========== РЕВЕРС ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ПЛАВНЫЙ РЕВЕРС"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Разгон вперед:"));
  smoothSetSpeed(70, 2000);
  delay(1000);

  Serial.println(F("→ Плавная остановка:"));
  smoothSetSpeed(0, 1500);
  delay(500);

  Serial.println(F("→ Разгон назад:"));
  smoothSetSpeed(-70, 2000);
  delay(1000);

  Serial.println(F("→ Плавная остановка:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ПРЯМОЙ РЕВЕРС ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ПРЯМОЙ РЕВЕРС (через ноль)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Вперед 60%:"));
  smoothSetSpeed(60, 1500);
  delay(1000);

  Serial.println(F("→ Прямой переход на -60% (через 0):"));
  smoothSetSpeed(-60, 3000);  // Плавно проходим через 0
  delay(1000);

  Serial.println(F("→ Остановка:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== S-ОБРАЗНАЯ КРИВАЯ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("S-ОБРАЗНАЯ КРИВАЯ (продвинутая техника)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Медленный старт → быстрое ускорение → плавная остановка\n"));

  // Медленный старт
  Serial.println(F("  Фаза 1: Медленный старт"));
  smoothSetSpeedAccel(30, 1, 100);
  delay(500);

  // Быстрое ускорение
  Serial.println(F("  Фаза 2: Быстрое ускорение"));
  smoothSetSpeedAccel(90, 5, 50);
  delay(1000);

  // Плавное замедление
  Serial.println(F("  Фаза 3: Плавное замедление"));
  smoothSetSpeedAccel(30, 3, 70);
  delay(500);

  // Мягкая остановка
  Serial.println(F("  Фаза 4: Мягкая остановка"));
  smoothSetSpeedAccel(0, 1, 100);
  delay(2000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        РЕКОМЕНДАЦИИ ПО ИСПОЛЬЗОВАНИЮ          ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  ВСЕГДА используйте плавное изменение для:    ║"));
  Serial.println(F("║    ✓ Старта с места (0 → скорость)            ║"));
  Serial.println(F("║    ✓ Остановки (скорость → 0)                 ║"));
  Serial.println(F("║    ✓ Реверса (+ → -)                          ║"));
  Serial.println(F("║    ✓ Высоких скоростей                        ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Рекомендуемые времена разгона:               ║"));
  Serial.println(F("║    • Легкие роботы: 1-2 секунды               ║"));
  Serial.println(F("║    • Средние роботы: 2-3 секунды              ║"));
  Serial.println(F("║    • Тяжелые роботы: 3-5 секунд               ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Преимущества:                                ║"));
  Serial.println(F("║    • Защита механики от износа                ║"));
  Serial.println(F("║    • Снижение пикового тока                   ║"));
  Serial.println(F("║    • Лучшее сцепление колес                   ║"));
  Serial.println(F("║    • Плавное движение                         ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл завершен. Повтор через 5 секунд...\n\n"));
  delay(5000);
}
