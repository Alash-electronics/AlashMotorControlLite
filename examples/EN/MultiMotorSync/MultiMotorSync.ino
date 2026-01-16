// Language: English | Русский: ../RU/MultiMotorSync/ | Қазақ: ../KZ/MultiMotorSync/

/*
 * Example demonstrates synchronization of multiple motors
 *
 * When working with multiple motors, it's important to:
 * - Synchronize start and stop
 * - Coordinate speeds
 * - Create functions for group control
 * - Properly organize code
 *
 * This example shows best practices for controlling
 * multiple motors simultaneously.
 *
 * Wiring for 2 motors:
 * Arduino:
 *   Motor 1: DIR -> Pin 4, PWM -> Pin 3
 *   Motor 2: DIR -> Pin 7, PWM -> Pin 6
 *
 * ESP32:
 *   Motor 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 *   Motor 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Create motor objects
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32 - PWM_PWM mode
  AlashMotorControlLite motorLeft(PWM_PWM, 32, 33);
  AlashMotorControlLite motorRight(PWM_PWM, 25, 26);
#else
  // Arduino - DIR_PWM mode
  AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
  AlashMotorControlLite motorRight(DIR_PWM, 7, 6);
#endif

// ========== GROUP CONTROL FUNCTIONS ==========

// Synchronized speed setting for both motors
void setBothMotors(int leftSpeed, int rightSpeed) {
  motorLeft.setSpeed(leftSpeed);
  motorRight.setSpeed(rightSpeed);
}

// Stop all motors
void stopAllMotors() {
  motorLeft.stop();
  motorRight.stop();
}

// Brake all motors
void brakeAllMotors() {
  motorLeft.brake();
  motorRight.brake();
}

// Smooth speed change for both motors
void smoothBothMotors(int leftTarget, int rightTarget, unsigned long rampTime) {
  int leftCurrent = motorLeft.getSpeed();
  int rightCurrent = motorRight.getSpeed();

  int leftDiff = leftTarget - leftCurrent;
  int rightDiff = rightTarget - rightCurrent;

  int maxSteps = max(abs(leftDiff), abs(rightDiff));
  if (maxSteps == 0) return;

  unsigned long stepDelay = rampTime / maxSteps;

  for (int step = 1; step <= maxSteps; step++) {
    // Calculate current speed for each motor
    int leftSpeed = leftCurrent + (leftDiff * step / maxSteps);
    int rightSpeed = rightCurrent + (rightDiff * step / maxSteps);

    motorLeft.setSpeed(leftSpeed);
    motorRight.setSpeed(rightSpeed);

    delay(stepDelay);
  }

  // Guarantee exact target values
  motorLeft.setSpeed(leftTarget);
  motorRight.setSpeed(rightTarget);
}

// Move forward
void moveForward(int speed) {
  setBothMotors(speed, speed);
}

// Move backward
void moveBackward(int speed) {
  setBothMotors(-speed, -speed);
}

// Turn in place right
void turnRight(int speed) {
  setBothMotors(speed, -speed);
}

// Turn in place left
void turnLeft(int speed) {
  setBothMotors(-speed, speed);
}

// Smooth turn (arc) right
void arcRight(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed - turnAmount;
  setBothMotors(leftSpeed, rightSpeed);
}

// Smooth turn (arc) left
void arcLeft(int baseSpeed, int turnAmount) {
  int leftSpeed = baseSpeed - turnAmount;
  int rightSpeed = baseSpeed;
  setBothMotors(leftSpeed, rightSpeed);
}

// Print status of all motors
void printMotorStatus() {
  Serial.print(F("Left: "));
  Serial.print(motorLeft.getSpeed());
  Serial.print(F("  |  Right: "));
  Serial.println(motorRight.getSpeed());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  MULTIPLE MOTOR SYNCHRONIZATION               ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== BASIC SYNCHRONIZATION ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("BASIC SYNCHRONIZATION"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Simultaneous start of both motors\n"));

  Serial.println(F("BAD - motors start one by one:"));
  Serial.println(F("  motorLeft.setSpeed(80);"));
  Serial.println(F("  delay(100);  // Left is already running!"));
  Serial.println(F("  motorRight.setSpeed(80);\n"));

  Serial.println(F("GOOD - motors start synchronously:"));
  Serial.println(F("  motorLeft.setSpeed(80);"));
  Serial.println(F("  motorRight.setSpeed(80);  // Right after left\n"));

  Serial.println(F("Starting synchronously:"));
  setBothMotors(70, 70);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Simultaneous stop"));
  stopAllMotors();
  printMotorStatus();
  delay(2000);

  // ========== DIFFERENT SPEEDS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("COORDINATING DIFFERENT SPEEDS"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Left 80%, Right 40% (turning)"));
  setBothMotors(80, 40);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Left 40%, Right 80% (turning)"));
  setBothMotors(40, 80);
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== USING MOVEMENT FUNCTIONS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("MOVEMENT FUNCTIONS"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Forward at 60%"));
  moveForward(60);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Backward at 50%"));
  moveBackward(50);
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Turn in place right"));
  turnRight(50);
  printMotorStatus();
  delay(1500);

  Serial.println(F("\n→ Turn in place left"));
  turnLeft(50);
  printMotorStatus();
  delay(1500);

  stopAllMotors();
  delay(1000);

  // ========== SMOOTH TURNS (ARCS) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("SMOOTH TURNS (ARCS)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Arc right (base speed 70)"));
  arcRight(70, 30);  // Right motor at 40 (70-30)
  printMotorStatus();
  delay(2000);

  Serial.println(F("\n→ Arc left (base speed 70)"));
  arcLeft(70, 30);   // Left motor at 40 (70-30)
  printMotorStatus();
  delay(2000);

  stopAllMotors();
  delay(1000);

  // ========== SYNCHRONIZED SMOOTH SPEED CHANGE ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("SYNCHRONIZED SMOOTH CHANGE"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Smooth acceleration: 0 → 80 in 2 seconds"));
  smoothBothMotors(80, 80, 2000);
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Smooth deceleration: 80 → 30 in 1.5 seconds"));
  smoothBothMotors(30, 30, 1500);
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Smooth stop: 30 → 0 in 1 second"));
  smoothBothMotors(0, 0, 1000);
  printMotorStatus();
  delay(1000);

  // ========== COMPLEX MANEUVERS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("COMPLEX MANEUVERS"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Maneuver 1: Square\n"));

  for (int side = 1; side <= 4; side++) {
    Serial.print(F("  Side "));
    Serial.print(side);
    Serial.println(F(": Forward"));
    moveForward(60);
    delay(1500);

    Serial.println(F("  Turn 90 degrees"));
    turnRight(50);
    delay(750);  // Approximately 90 degrees

    stopAllMotors();
    delay(300);
  }

  delay(1000);

  Serial.println(F("\nManeuver 2: Figure Eight\n"));

  Serial.println(F("  Right circle:"));
  for (int i = 0; i < 4; i++) {
    arcRight(60, 40);
    delay(750);
  }

  Serial.println(F("  Left circle:"));
  for (int i = 0; i < 4; i++) {
    arcLeft(60, 40);
    delay(750);
  }

  stopAllMotors();
  delay(2000);

  // ========== INDEPENDENT CONTROL ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("INDEPENDENT CONTROL"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Left smoothly accelerates, right stays still"));
  for (int speed = 0; speed <= 80; speed += 5) {
    motorLeft.setSpeed(speed);
    // motorRight stays at 0
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Right catches up to left"));
  for (int speed = 0; speed <= 80; speed += 5) {
    motorRight.setSpeed(speed);
    delay(100);
  }
  printMotorStatus();
  delay(1000);

  Serial.println(F("\n→ Both smoothly stop"));
  smoothBothMotors(0, 0, 1500);
  delay(1000);

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║      SYNCHRONIZATION BEST PRACTICES           ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  1. Create functions for frequent operations: ║"));
  Serial.println(F("║     • moveForward(speed)                      ║"));
  Serial.println(F("║     • turnLeft(speed)                         ║"));
  Serial.println(F("║     • stopAllMotors()                         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  2. Set speeds sequentially:                  ║"));
  Serial.println(F("║     motorLeft.setSpeed(speed);                ║"));
  Serial.println(F("║     motorRight.setSpeed(speed);               ║"));
  Serial.println(F("║     // DON'T use delay() between them!        ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  3. For smooth movements use:                 ║"));
  Serial.println(F("║     • Common smoothBothMotors() function      ║"));
  Serial.println(F("║     • Synchronized speed changes              ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  4. Always check current state:               ║"));
  Serial.println(F("║     • Use getSpeed()                          ║"));
  Serial.println(F("║     • Print to Serial for debugging           ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  5. For robots create Robot class:            ║"));
  Serial.println(F("║     class Robot {                             ║"));
  Serial.println(F("║       AlashMotorControlLite left, right;      ║"));
  Serial.println(F("║       void forward(int speed);                ║"));
  Serial.println(F("║       void turn(int angle);                   ║"));
  Serial.println(F("║     }                                          ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
