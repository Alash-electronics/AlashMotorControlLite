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

  Serial.print("Плавное изменение: ");
  Serial.print(currentSpeed);
  Serial.print(" → ");
  Serial.print(targetSpeed);
  Serial.print(" за ");
  Serial.print(rampTime);
  Serial.println(" мс");

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

  Serial.println("  ✓ Достигнута целевая скорость\n");
}

// Функция для плавного изменения скорости с заданным ускорением
// targetSpeed: целевая скорость (-100 до 100)
// acceleration: ускорение (единиц скорости за шаг)
// stepDelay: задержка между шагами в миллисекундах
void smoothSetSpeedAccel(int targetSpeed, int acceleration, unsigned long stepDelay) {
  int currentSpeed = motor.getSpeed();

  Serial.print("Плавное изменение с ускорением ");
  Serial.print(acceleration);
  Serial.print(": ");
  Serial.print(currentSpeed);
  Serial.print(" → ");
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

  Serial.println("  ✓ Достигнута целевая скорость\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  ПЛАВНОЕ ИЗМЕНЕНИЕ СКОРОСТИ (RAMPING)         ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== СРАВНЕНИЕ: Резкое VS Плавное ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("СРАВНЕНИЕ: Резкое vs Плавное изменение");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("❌ РЕЗКОЕ изменение (может повредить механику):");
  motor.setSpeed(0);
  delay(500);
  Serial.println("motor.setSpeed(100) - мгновенный рывок!");
  motor.setSpeed(100);
  delay(2000);

  motor.stop();
  delay(1000);

  Serial.println("\n✓ ПЛАВНОЕ изменение (безопасно для механики):");
  motor.setSpeed(0);
  delay(500);
  smoothSetSpeed(100, 2000);  // Плавный разгон за 2 секунды
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== РАЗНЫЕ ВРЕМЕНА РАЗГОНА ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РАЗНЫЕ ВРЕМЕНА РАЗГОНА");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Быстрый разгон (1 секунда):");
  smoothSetSpeed(80, 1000);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println("→ Средний разгон (2 секунды):");
  smoothSetSpeed(80, 2000);
  delay(1000);
  smoothSetSpeed(0, 2000);
  delay(1000);

  Serial.println("→ Медленный разгон (3 секунды):");
  smoothSetSpeed(80, 3000);
  delay(1000);
  smoothSetSpeed(0, 3000);
  delay(2000);

  // ========== УСКОРЕНИЕ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("УПРАВЛЕНИЕ УСКОРЕНИЕМ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Малое ускорение (плавно):");
  smoothSetSpeedAccel(90, 2, 50);  // +2 единицы каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 2, 50);
  delay(1000);

  Serial.println("→ Среднее ускорение:");
  smoothSetSpeedAccel(90, 5, 50);  // +5 единиц каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 5, 50);
  delay(1000);

  Serial.println("→ Большое ускорение (быстро):");
  smoothSetSpeedAccel(90, 10, 50);  // +10 единиц каждые 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 10, 50);
  delay(2000);

  // ========== РЕВЕРС ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ПЛАВНЫЙ РЕВЕРС");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Разгон вперед:");
  smoothSetSpeed(70, 2000);
  delay(1000);

  Serial.println("→ Плавная остановка:");
  smoothSetSpeed(0, 1500);
  delay(500);

  Serial.println("→ Разгон назад:");
  smoothSetSpeed(-70, 2000);
  delay(1000);

  Serial.println("→ Плавная остановка:");
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ПРЯМОЙ РЕВЕРС ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ПРЯМОЙ РЕВЕРС (через ноль)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Вперед 60%:");
  smoothSetSpeed(60, 1500);
  delay(1000);

  Serial.println("→ Прямой переход на -60% (через 0):");
  smoothSetSpeed(-60, 3000);  // Плавно проходим через 0
  delay(1000);

  Serial.println("→ Остановка:");
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== S-ОБРАЗНАЯ КРИВАЯ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("S-ОБРАЗНАЯ КРИВАЯ (продвинутая техника)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Медленный старт → быстрое ускорение → плавная остановка\n");

  // Медленный старт
  Serial.println("  Фаза 1: Медленный старт");
  smoothSetSpeedAccel(30, 1, 100);
  delay(500);

  // Быстрое ускорение
  Serial.println("  Фаза 2: Быстрое ускорение");
  smoothSetSpeedAccel(90, 5, 50);
  delay(1000);

  // Плавное замедление
  Serial.println("  Фаза 3: Плавное замедление");
  smoothSetSpeedAccel(30, 3, 70);
  delay(500);

  // Мягкая остановка
  Serial.println("  Фаза 4: Мягкая остановка");
  smoothSetSpeedAccel(0, 1, 100);
  delay(2000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("\n╔═══════════════════════════════════════════════╗");
  Serial.println("║        РЕКОМЕНДАЦИИ ПО ИСПОЛЬЗОВАНИЮ          ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  ВСЕГДА используйте плавное изменение для:    ║");
  Serial.println("║    ✓ Старта с места (0 → скорость)            ║");
  Serial.println("║    ✓ Остановки (скорость → 0)                 ║");
  Serial.println("║    ✓ Реверса (+ → -)                          ║");
  Serial.println("║    ✓ Высоких скоростей                        ║");
  Serial.println("║                                                ║");
  Serial.println("║  Рекомендуемые времена разгона:               ║");
  Serial.println("║    • Легкие роботы: 1-2 секунды               ║");
  Serial.println("║    • Средние роботы: 2-3 секунды              ║");
  Serial.println("║    • Тяжелые роботы: 3-5 секунд               ║");
  Serial.println("║                                                ║");
  Serial.println("║  Преимущества:                                ║");
  Serial.println("║    • Защита механики от износа                ║");
  Serial.println("║    • Снижение пикового тока                   ║");
  Serial.println("║    • Лучшее сцепление колес                   ║");
  Serial.println("║    • Плавное движение                         ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("Цикл завершен. Повтор через 5 секунд...\n\n");
  delay(5000);
}
