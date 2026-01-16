// Language: English | Русский: ../RU/ESP32_Mecanum_Serial/ | Қазақ: ../KZ/ESP32_Mecanum_Serial/

/*
 * Interactive control of mecanum wheel robot via Serial Monitor
 *
 * Motor wiring (PWM_PWM mode):
 * Motor 1 (Front Left):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Front Right): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Rear Left):   IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Rear Right):  IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Control commands via Serial Monitor:
 * w - forward        q - diagonal forward-left    e - diagonal forward-right
 * s - backward       z - diagonal backward-left   c - diagonal backward-right
 * a - left
 * d - right
 * j - rotate counterclockwise    l - rotate clockwise
 * x - stop (coast stop)
 * b - brake (active braking)
 * + - increase speed
 * - - decrease speed
 * h - help (command list)
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Create objects for 4 motors
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Front Left
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Front Right
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Rear Left
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Rear Right

int speed = 60;  // Current speed (0-100)

// Function for mecanum wheel control
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
  Serial.println(F("\n╔══════════════════════════════════════════════════╗"));
  Serial.println(F("║   MECANUM ROBOT CONTROL - COMMANDS              ║"));
  Serial.println(F("╠══════════════════════════════════════════════════╣"));
  Serial.println(F("║  BASIC MOVEMENTS:                               ║"));
  Serial.println(F("║    w - Forward         s - Backward             ║"));
  Serial.println(F("║    a - Left            d - Right                ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  DIAGONAL MOVEMENTS:                            ║"));
  Serial.println(F("║    q - Forward-left    e - Forward-right        ║"));
  Serial.println(F("║    z - Backward-left   c - Backward-right       ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  ROTATION:                                       ║"));
  Serial.println(F("║    j - Counterclockwise  l - Clockwise          ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  STOP:                                           ║"));
  Serial.println(F("║    x - Stop (coast)                             ║"));
  Serial.println(F("║    b - Brake (active braking)                   ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║  SPEED CONTROL:                                  ║"));
  Serial.println(F("║    + - Increase speed                           ║"));
  Serial.println(F("║    - - Decrease speed                           ║"));
  Serial.println(F("║                                                  ║"));
  Serial.println(F("║    h - Show this help                           ║"));
  Serial.println(F("╚══════════════════════════════════════════════════╝"));
  Serial.print(F("\nCurrent speed: "));
  Serial.print(speed);
  Serial.println(F("%\n"));
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("\n╔══════════════════════════════════════════════════╗"));
  Serial.println(F("║  ESP32 MECANUM 4WD ROBOT - SERIAL CONTROL       ║"));
  Serial.println(F("║  Driver: ZK-5AD                                  ║"));
  Serial.println(F("╚══════════════════════════════════════════════════╝\n"));

  printHelp();

  Serial.println(F("Ready! Enter command..."));
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch(command) {
      // Basic movements
      case 'w': case 'W':
        Serial.print(F("▲ Forward ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, 0, 0);
        break;

      case 's': case 'S':
        Serial.print(F("▼ Backward ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, 0, 0);
        break;

      case 'a': case 'A':
        Serial.print(F("◄ Left ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, speed, 0);
        break;

      case 'd': case 'D':
        Serial.print(F("► Right ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, -speed, 0);
        break;

      // Diagonal movements
      case 'q': case 'Q':
        Serial.print(F("↖ Forward-left ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, speed, 0);
        break;

      case 'e': case 'E':
        Serial.print(F("↗ Forward-right ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(speed, -speed, 0);
        break;

      case 'z': case 'Z':
        Serial.print(F("↙ Backward-left ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, speed, 0);
        break;

      case 'c': case 'C':
        Serial.print(F("↘ Backward-right ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(-speed, -speed, 0);
        break;

      // Rotation
      case 'j': case 'J':
        Serial.print(F("↺ Rotate counterclockwise ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, 0, -speed);
        break;

      case 'l': case 'L':
        Serial.print(F("↻ Rotate clockwise ["));
        Serial.print(speed);
        Serial.println(F("%]"));
        mecanumDrive(0, 0, speed);
        break;

      // Stop
      case 'x': case 'X':
        Serial.println(F("■ Stop"));
        stopAll();
        break;

      case 'b': case 'B':
        Serial.println(F("⊠ Brake"));
        brakeAll();
        break;

      // Speed control
      case '+':
        speed = constrain(speed + 10, 0, 100);
        Serial.print(F("Speed increased: "));
        Serial.print(speed);
        Serial.println(F("%"));
        break;

      case '-':
        speed = constrain(speed - 10, 0, 100);
        Serial.print(F("Speed decreased: "));
        Serial.print(speed);
        Serial.println(F("%"));
        break;

      // Help
      case 'h': case 'H':
        printHelp();
        break;

      case '\n':
      case '\r':
        // Ignore newline characters
        break;

      default:
        Serial.print(F("Unknown command: "));
        Serial.println(command);
        Serial.println(F("Press 'h' for help"));
        break;
    }
  }
}
