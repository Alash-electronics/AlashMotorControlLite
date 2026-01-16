// Language: English | Русский: ../RU/ESP32_Mecanum_4WD_Demo/ | Қазақ: ../KZ/ESP32_Mecanum_4WD_Demo/

/*
 * Control of mecanum wheel robot (4 motors) on ESP32 with ZK-5AD driver
 *
 * Mecanum wheels allow the robot to move in any direction:
 * - Forward/backward
 * - Left/right (strafing)
 * - Diagonal movement
 * - Rotation in place
 *
 * Motor wiring (PWM_PWM mode):
 * Motor 1 (Front Left):  IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2 (Front Right): IN1 -> GPIO 25, IN2 -> GPIO 26
 * Motor 3 (Rear Left):   IN1 -> GPIO 19, IN2 -> GPIO 18
 * Motor 4 (Rear Right):  IN1 -> GPIO 17, IN2 -> GPIO 16
 *
 * Wheel layout (top view):
 *     FRONT
 *    M1 ↗     ↖ M2
 *         [ ]
 *    M3 ↖     ↗ M4
 *     REAR
 *
 * Mecanum wheel roller direction:
 * M1: / (diagonal right)
 * M2: \ (diagonal left)
 * M3: \ (diagonal left)
 * M4: / (diagonal right)
 *
 * Driver power supply:
 * VCC -> 5V or 3.3V
 * GND -> GND
 * VM -> Motor power (6-12V)
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Create objects for 4 motors in PWM_PWM mode
AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Front Left
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Front Right
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Rear Left
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Rear Right

// Function for mecanum wheel control
// vx: forward/backward speed (-100 to 100)
// vy: left/right speed (-100 to 100)
// rotation: rotation speed (-100 to 100)
void mecanumDrive(int vx, int vy, int rotation) {
  // Mecanum wheel formulas
  int speedFL = vx + vy + rotation;  // Front Left
  int speedFR = vx - vy - rotation;  // Front Right
  int speedRL = vx - vy + rotation;  // Rear Left
  int speedRR = vx + vy - rotation;  // Rear Right

  // Constrain speeds to -100 to 100 range
  speedFL = constrain(speedFL, -100, 100);
  speedFR = constrain(speedFR, -100, 100);
  speedRL = constrain(speedRL, -100, 100);
  speedRR = constrain(speedRR, -100, 100);

  // Set motor speeds
  motorFL.setSpeed(speedFL);
  motorFR.setSpeed(speedFR);
  motorRL.setSpeed(speedRL);
  motorRR.setSpeed(speedRR);
}

// Function to stop all motors
void stopAll() {
  motorFL.stop();
  motorFR.stop();
  motorRL.stop();
  motorRR.stop();
}

// Function to brake all motors
void brakeAll() {
  motorFL.brake();
  motorFR.brake();
  motorRL.brake();
  motorRR.brake();
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 Mecanum 4WD Robot Control"));
  Serial.println(F("Initialization complete"));
  delay(2000);
}

void loop() {
  // ==================== Forward movement ====================
  Serial.println(F("1. Forward movement (50% speed)"));
  mecanumDrive(50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("2. Forward movement (100% speed)"));
  mecanumDrive(100, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Backward movement ====================
  Serial.println(F("3. Backward movement (50% speed)"));
  mecanumDrive(-50, 0, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Strafing left ====================
  Serial.println(F("4. Strafing left (sideways movement)"));
  mecanumDrive(0, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Strafing right ====================
  Serial.println(F("5. Strafing right (sideways movement)"));
  mecanumDrive(0, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Diagonal movement ====================
  Serial.println(F("6. Diagonal movement (forward-left)"));
  mecanumDrive(50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("7. Diagonal movement (forward-right)"));
  mecanumDrive(50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("8. Diagonal movement (backward-left)"));
  mecanumDrive(-50, 50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  Serial.println(F("9. Diagonal movement (backward-right)"));
  mecanumDrive(-50, -50, 0);
  delay(2000);

  stopAll();
  delay(1000);

  // ==================== Rotation in place ====================
  Serial.println(F("10. Rotation in place clockwise"));
  mecanumDrive(0, 0, 50);
  delay(2000);

  brakeAll();
  delay(1000);

  Serial.println(F("11. Rotation in place counterclockwise"));
  mecanumDrive(0, 0, -50);
  delay(2000);

  brakeAll();
  delay(1000);

  // ==================== Combined movement ====================
  Serial.println(F("12. Moving in circle (forward + rotation)"));
  mecanumDrive(60, 0, 30);
  delay(3000);

  stopAll();
  delay(1000);

  Serial.println(F("13. Arc movement (forward-left + rotation)"));
  mecanumDrive(50, 30, 20);
  delay(3000);

  stopAll();
  delay(1000);

  // ==================== Complex trajectory ====================
  Serial.println(F("14. Square trajectory"));

  // Forward
  Serial.println(F("  - Forward"));
  mecanumDrive(70, 0, 0);
  delay(1500);

  // Strafe right
  Serial.println(F("  - Right"));
  mecanumDrive(0, -70, 0);
  delay(1500);

  // Backward
  Serial.println(F("  - Backward"));
  mecanumDrive(-70, 0, 0);
  delay(1500);

  // Strafe left
  Serial.println(F("  - Left"));
  mecanumDrive(0, 70, 0);
  delay(1500);

  brakeAll();
  delay(2000);

  Serial.println(F("Cycle complete. Pause 3 seconds...\n"));
  delay(3000);
}
