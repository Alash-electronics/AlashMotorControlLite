/*
 * Интерактивное управление роботом с меканум колесами через Serial Monitor
 *
 * Подключение моторов (режим PWM_PWM):
 * Motor 1 (Передний левый):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Передний правый): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Задний левый):    IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Задний правый):    IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Команды управления через Serial Monitor:
 * w - вперед        q - диагональ вперед-влево    e - диагональ вперед-вправо
 * s - назад         z - диагональ назад-влево     c - диагональ назад-вправо
 * a - влево
 * d - вправо
 * j - поворот против часовой    l - поворот по часовой
 * x - стоп (свободная остановка)
 * b - тормоз (активное торможение)
 * + - увеличить скорость
 * - - уменьшить скорость
 * h - помощь (список команд)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Создаем объекты для 4 моторов
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Front Left
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Front Right
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Rear Left
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Rear Right

int speed = 60;  // Текущая скорость (0-100)

// Функция для управления меканум-колесами
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
  Serial.println("\n╔══════════════════════════════════════════════════╗");
  Serial.println("║   УПРАВЛЕНИЕ МЕКАНУМ РОБОТОМ - КОМАНДЫ          ║");
  Serial.println("╠══════════════════════════════════════════════════╣");
  Serial.println("║  БАЗОВЫЕ ДВИЖЕНИЯ:                              ║");
  Serial.println("║    w - Вперед          s - Назад                ║");
  Serial.println("║    a - Влево           d - Вправо               ║");
  Serial.println("║                                                  ║");
  Serial.println("║  ДИАГОНАЛЬНЫЕ ДВИЖЕНИЯ:                         ║");
  Serial.println("║    q - Вперед-влево    e - Вперед-вправо        ║");
  Serial.println("║    z - Назад-влево     c - Назад-вправо         ║");
  Serial.println("║                                                  ║");
  Serial.println("║  ВРАЩЕНИЕ:                                       ║");
  Serial.println("║    j - Против часовой  l - По часовой           ║");
  Serial.println("║                                                  ║");
  Serial.println("║  ОСТАНОВКА:                                      ║");
  Serial.println("║    x - Стоп (свободная)                         ║");
  Serial.println("║    b - Тормоз (активное торможение)             ║");
  Serial.println("║                                                  ║");
  Serial.println("║  УПРАВЛЕНИЕ СКОРОСТЬЮ:                          ║");
  Serial.println("║    + - Увеличить скорость                       ║");
  Serial.println("║    - - Уменьшить скорость                       ║");
  Serial.println("║                                                  ║");
  Serial.println("║    h - Показать эту помощь                      ║");
  Serial.println("╚══════════════════════════════════════════════════╝");
  Serial.print("\nТекущая скорость: ");
  Serial.print(speed);
  Serial.println("%\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n╔══════════════════════════════════════════════════╗");
  Serial.println("║  ESP32 MECANUM 4WD ROBOT - SERIAL CONTROL       ║");
  Serial.println("║  Драйвер: ZK-5AD                                 ║");
  Serial.println("╚══════════════════════════════════════════════════╝\n");

  printHelp();

  Serial.println("Готов к работе! Введите команду...");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch(command) {
      // Базовые движения
      case 'w': case 'W':
        Serial.print("▲ Вперед [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(speed, 0, 0);
        break;

      case 's': case 'S':
        Serial.print("▼ Назад [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(-speed, 0, 0);
        break;

      case 'a': case 'A':
        Serial.print("◄ Влево [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(0, speed, 0);
        break;

      case 'd': case 'D':
        Serial.print("► Вправо [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(0, -speed, 0);
        break;

      // Диагональные движения
      case 'q': case 'Q':
        Serial.print("↖ Вперед-влево [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(speed, speed, 0);
        break;

      case 'e': case 'E':
        Serial.print("↗ Вперед-вправо [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(speed, -speed, 0);
        break;

      case 'z': case 'Z':
        Serial.print("↙ Назад-влево [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(-speed, speed, 0);
        break;

      case 'c': case 'C':
        Serial.print("↘ Назад-вправо [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(-speed, -speed, 0);
        break;

      // Вращение
      case 'j': case 'J':
        Serial.print("↺ Поворот против часовой [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(0, 0, -speed);
        break;

      case 'l': case 'L':
        Serial.print("↻ Поворот по часовой [");
        Serial.print(speed);
        Serial.println("%]");
        mecanumDrive(0, 0, speed);
        break;

      // Остановка
      case 'x': case 'X':
        Serial.println("■ Стоп");
        stopAll();
        break;

      case 'b': case 'B':
        Serial.println("⊠ Тормоз");
        brakeAll();
        break;

      // Управление скоростью
      case '+':
        speed = constrain(speed + 10, 0, 100);
        Serial.print("Скорость увеличена: ");
        Serial.print(speed);
        Serial.println("%");
        break;

      case '-':
        speed = constrain(speed - 10, 0, 100);
        Serial.print("Скорость уменьшена: ");
        Serial.print(speed);
        Serial.println("%");
        break;

      // Помощь
      case 'h': case 'H':
        printHelp();
        break;

      case '\n':
      case '\r':
        // Игнорируем символы новой строки
        break;

      default:
        Serial.print("Неизвестная команда: ");
        Serial.println(command);
        Serial.println("Нажмите 'h' для помощи");
        break;
    }
  }
}
