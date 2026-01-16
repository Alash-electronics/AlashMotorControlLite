# AlashMotorControlLite

> 🌐 **English** | **[Русский](README_ru.md)**

[![Arduino](https://img.shields.io/badge/Arduino-Compatible-blue.svg)](https://www.arduino.cc/)
[![ESP32](https://img.shields.io/badge/ESP32-Supported-green.svg)](https://www.espressif.com/)
[![Version](https://img.shields.io/badge/version-1.0.9-orange.svg)](https://github.com/Alash-electronics/AlashMotorControlLite)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

**Simple and powerful library for controlling DC motors on Arduino and ESP32**

AlashMotorControlLite provides a universal interface for controlling DC motors through various drivers (L298N, TB6612, ZK-5AD, DRV8833, BTS7960, and others). Supports Arduino, ESP32, and compatible platforms.

## 🚀 Key Features

- ✅ **Simple API** - Speed control from -100 to 100
- ✅ **4 driver modes** - Support for all popular H-Bridge chips
- ✅ **Cross-platform** - Arduino, ESP32, compatible boards
- ✅ **Error protection** - Automatic speed limiting
- ✅ **ESP32 3.x ready** - Support for new PWM API
- ✅ **17 examples** - From basic to advanced (mecanum wheels)
- ✅ **Bilingual documentation** - English and Русский

## 📦 Installation

### Via Arduino Library Manager (recommended)

1. Open Arduino IDE
2. **Sketch** → **Include Library** → **Manage Libraries**
3. Search for `AlashMotorControlLite`
4. Click **Install**
5. Restart Arduino IDE

### Manual installation

1. Download the [latest release](https://github.com/Alash-electronics/AlashMotorControlLite/releases)
2. Extract to `Arduino/libraries/` folder
3. Restart Arduino IDE

## 🎯 Quick Start

### Simple example (Arduino + L298N)

```cpp
#include "AlashMotorControlLite.h"

// DIR_DIR_PWM mode: IN1=4, IN2=5, EN=6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);

void setup() {
  // No initialization required
}

void loop() {
  motor.setSpeed(75);    // Forward at 75%
  delay(2000);

  motor.setSpeed(-50);   // Reverse at 50%
  delay(2000);

  motor.stop();          // Stop
  delay(1000);
}
```

### ESP32 + ZK-5AD (PWM_PWM mode)

```cpp
#include "AlashMotorControlLite.h"

// PWM_PWM mode: IN1=GPIO32, IN2=GPIO33
AlashMotorControlLite motor(PWM_PWM, 32, 33);

void setup() {
  Serial.begin(115200);
}

void loop() {
  motor.setSpeed(100);   // Full speed forward
  delay(2000);

  motor.brake();         // Active braking
  delay(500);

  motor.setSpeed(-100);  // Full speed reverse
  delay(2000);

  motor.stop();          // Coast stop
  delay(1000);
}
```

## 🎛️ Driver Modes (MODE)

The library supports 4 modes for different driver types:

| Mode | Pins | PWM | Drivers | Description |
|------|------|-----|---------|-------------|
| **DIR_PWM** | 2 | 1 | TB6612FNG, DRV8833 | 1 direction + 1 speed pin |
| **PWM_PWM** | 2 | 2 | ZK-5AD, L298N, BTS7960 | 2 PWM for bidirectional control |
| **DIR_DIR_PWM** | 3 | 1 | L298N (with EN), L293D | 2 direction + 1 speed pin |
| **DIR_DIR** | 2 | 0 | Relays, simple drivers | On/off only, no PWM |

### Wiring Examples

#### L298N driver (DIR_DIR_PWM)
```cpp
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
// PIN 4 → IN1 (direction 1)
// PIN 5 → IN2 (direction 2)
// PIN 6 → EN  (PWM speed)
```

#### TB6612FNG driver (DIR_PWM)
```cpp
AlashMotorControlLite motor(DIR_PWM, 4, 3);
// PIN 4 → IN1 (direction)
// PIN 3 → PWM (speed)
```

#### ZK-5AD driver for ESP32 (PWM_PWM)
```cpp
AlashMotorControlLite motor(PWM_PWM, 32, 33);
// GPIO 32 → IN1 (PWM forward)
// GPIO 33 → IN2 (PWM reverse)
```

## 📚 API Documentation

### Constructors

```cpp
// For modes: DIR_PWM, PWM_PWM, DIR_DIR (2 pins)
AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2);

// For mode: DIR_DIR_PWM (3 pins)
AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2, uint8_t pin_pwm);
```

### Core Methods

#### `void setSpeed(int16_t speed)`
Set motor speed and direction

**Parameters:**
- `speed` - Speed from **-100 to 100**
  - `-100` to `-1` = reverse motion
  - `0` = stop
  - `1` to `100` = forward motion

**Example:**
```cpp
motor.setSpeed(75);    // Forward at 75%
motor.setSpeed(-50);   // Reverse at 50%
motor.setSpeed(0);     // Stop
```

#### `void stop()`
Coast stop (free-running stop)

Motor is disabled and stops by inertia. Used for:
- Smooth stop without mechanical stress
- Energy saving
- Normal stop at end of movement

**Example:**
```cpp
motor.setSpeed(100);
delay(2000);
motor.stop();  // Smooth stop
```

#### `void brake()`
Active braking

Motor actively brakes (short-circuit winding). Used for:
- Quick stop
- Position holding under load
- Precise stopping

**Example:**
```cpp
motor.setSpeed(100);
delay(2000);
motor.brake();  // Hard brake
```

#### `int16_t getSpeed()`
Get current motor speed

**Returns:** Current speed from -100 to 100

**Example:**
```cpp
motor.setSpeed(75);
int speed = motor.getSpeed();  // Returns 75
Serial.println(speed);
```

#### `MODE getMode()`
Get current driver mode

**Returns:** MODE enum value

**Example:**
```cpp
MODE mode = motor.getMode();
if (mode == PWM_PWM) {
  Serial.println("PWM_PWM mode");
}
```

## 🔌 Wiring Diagrams

### Arduino Uno + L298N

```
Arduino Uno          L298N Driver
─────────────────────────────────
PIN 4      →  IN1
PIN 5      →  IN2
PIN 6      →  ENA (PWM)
5V         →  5V
GND        →  GND

            Motor Output
            ─────────────
            OUT1 → Motor +
            OUT2 → Motor -
            12V  → Power Supply +
            GND  → Power Supply -
```

### ESP32 + ZK-5AD (2 motors)

```
ESP32              ZK-5AD Driver
──────────────────────────────────
GPIO 32   →  Motor1 IN1
GPIO 33   →  Motor1 IN2
GPIO 25   →  Motor2 IN1
GPIO 26   →  Motor2 IN2
5V        →  VCC
GND       →  GND

            Motor Outputs
            ──────────────
            M1+/M1- → Motor 1
            M2+/M2- → Motor 2
            VM      → 6-12V Power
            GND     → Power GND
```

## 💡 Usage Examples

### Smooth acceleration and deceleration

```cpp
#include "AlashMotorControlLite.h"

AlashMotorControlLite motor(DIR_PWM, 4, 3);

void smoothSpeed(int target, int delayMs) {
  int current = motor.getSpeed();
  int step = (target > current) ? 1 : -1;

  for (int speed = current; speed != target; speed += step) {
    motor.setSpeed(speed);
    delay(delayMs);
  }
}

void setup() {}

void loop() {
  smoothSpeed(100, 20);   // Smooth acceleration over 2 seconds
  delay(2000);
  smoothSpeed(0, 20);     // Smooth deceleration
  delay(1000);
}
```

### Two motor control (robot)

```cpp
#include "AlashMotorControlLite.h"

AlashMotorControlLite motorLeft(PWM_PWM, 32, 33);
AlashMotorControlLite motorRight(PWM_PWM, 25, 26);

void moveForward(int speed) {
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed);
}

void turnRight(int speed) {
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(-speed);
}

void stopAll() {
  motorLeft.stop();
  motorRight.stop();
}

void setup() {}

void loop() {
  moveForward(70);    // Forward
  delay(2000);

  turnRight(50);      // Turn right
  delay(1000);

  stopAll();          // Stop
  delay(1000);
}
```

### Mecanum wheels (4WD)

```cpp
#include "AlashMotorControlLite.h"

AlashMotorControlLite motorFL(PWM_PWM, 32, 33);  // Front Left
AlashMotorControlLite motorFR(PWM_PWM, 25, 26);  // Front Right
AlashMotorControlLite motorRL(PWM_PWM, 19, 18);  // Rear Left
AlashMotorControlLite motorRR(PWM_PWM, 17, 16);  // Rear Right

void mecanumDrive(int vx, int vy, int rotation) {
  int speedFL = vx + vy + rotation;
  int speedFR = vx - vy - rotation;
  int speedRL = vx - vy + rotation;
  int speedRR = vx + vy - rotation;

  motorFL.setSpeed(constrain(speedFL, -100, 100));
  motorFR.setSpeed(constrain(speedFR, -100, 100));
  motorRL.setSpeed(constrain(speedRL, -100, 100));
  motorRR.setSpeed(constrain(speedRR, -100, 100));
}

void setup() {}

void loop() {
  mecanumDrive(50, 0, 0);     // Forward
  delay(2000);

  mecanumDrive(0, 50, 0);     // Strafe left
  delay(2000);

  mecanumDrive(0, 0, 30);     // Rotate in place
  delay(2000);
}
```

## 📖 Built-in Examples

After installing the library, examples are available in Arduino IDE:
**File → Examples → AlashMotorControlLite**

> 💡 **Note:** All examples are available in both English and Russian. Look for files with `_ru` suffix for Russian versions.

### Basic Examples (learning API)

| Example | Description |
|---------|-------------|
| **StopVsBrake** | Difference between stop() and brake() |
| **GettersDemo** | Using getSpeed() and getMode() |
| **SmoothSpeed** | Smooth speed changes (ramping) |
| **AllModesDemo** | Comparison of all 4 driver modes |
| **SpeedLimits** | Speed clamping and boundary testing |
| **DirectionChange** | Safe direction reversal techniques |
| **MultiMotorSync** | Synchronizing multiple motors |

### Driver-Specific Examples

| Example | Mode | Driver |
|---------|------|---------|
| **DIR_PWM** | DIR_PWM | TB6612FNG, DRV8833 |
| **DIR_PWM_DualMotor** | DIR_PWM | 2 motors TB6612FNG |
| **PWM_PWM_DualMotor** | PWM_PWM | 2 motors common |
| **DIR_DIR_PWM** | DIR_DIR_PWM | L298N |
| **DIR_DIR_PWM_DualMotor** | DIR_DIR_PWM | 2 motors L298N |
| **DIR_DIR_PWM_pot** | DIR_DIR_PWM | Potentiometer control |

### ESP32 Specialized

| Example | Description |
|---------|-------------|
| **ESP32_ZK5AD_SingleMotor** | 1 motor on ESP32 + ZK-5AD |
| **ESP32_ZK5AD_DualMotor** | 2 motors on ESP32 + ZK-5AD |
| **ESP32_Mecanum_4WD_Demo** | Mecanum robot (auto demo) |
| **ESP32_Mecanum_Serial** | Mecanum robot (manual control) |

## ❓ FAQ (Frequently Asked Questions)

### Which mode should I choose for my driver?

- **L298N** → `DIR_DIR_PWM` (if using EN pin) or `PWM_PWM`
- **TB6612FNG** → `DIR_PWM`
- **ZK-5AD** → `PWM_PWM`
- **DRV8833** → `DIR_PWM`
- **BTS7960** → `PWM_PWM`
- **Relays** → `DIR_DIR`

### Why isn't my motor rotating?

1. Check driver power supply (must be sufficient for the motor)
2. Make sure the correct MODE is selected
3. Check pin connections
4. On ESP32: ensure you're not using input-only pins
5. Try setSpeed(100) for maximum speed

### Motor rotates in the wrong direction

Swap motor wires (M+ and M-) or swap pin1 and pin2 in the constructor:

```cpp
// Was
AlashMotorControlLite motor(PWM_PWM, 32, 33);

// Now (inverted)
AlashMotorControlLite motor(PWM_PWM, 33, 32);
```

### How to control more than 2 motors?

Create multiple objects:

```cpp
AlashMotorControlLite motor1(PWM_PWM, 32, 33);
AlashMotorControlLite motor2(PWM_PWM, 25, 26);
AlashMotorControlLite motor3(PWM_PWM, 19, 18);
AlashMotorControlLite motor4(PWM_PWM, 17, 16);
```

ESP32 supports up to 16 PWM channels.

### What's the difference between stop() and brake()?

- **stop()** - Coast stop (inertia), less stress
- **brake()** - Active braking (quick stop), more stress

Use `stop()` for normal stopping, `brake()` when quick stop is needed.

### Is ESP32-S3 / ESP32-C3 supported?

Yes, the library works on all ESP32 variants (ESP32, ESP32-S2, ESP32-S3, ESP32-C3, ESP32-C6).

### Can I use it with the Servo library?

Yes, but on Arduino be careful with PWM pins - Servo and PWM may conflict on the same timers. On ESP32 there are no issues.

## 🔧 Advanced Features

### Smooth reverse (safe direction change)

```cpp
void safeReverse(int newSpeed) {
  // Current speed
  int current = motor.getSpeed();

  // If different signs - need reverse
  if ((current > 0 && newSpeed < 0) || (current < 0 && newSpeed > 0)) {
    // Smoothly to zero
    while (abs(motor.getSpeed()) > 0) {
      int speed = motor.getSpeed();
      motor.setSpeed(speed > 0 ? speed - 1 : speed + 1);
      delay(10);
    }

    // Active braking
    motor.brake();
    delay(300);

    // Pause
    motor.stop();
    delay(200);
  }

  // Smoothly to new speed
  while (motor.getSpeed() != newSpeed) {
    int speed = motor.getSpeed();
    int step = (newSpeed > speed) ? 1 : -1;
    motor.setSpeed(speed + step);
    delay(10);
  }
}
```

### Automatic calibration (finding minimum speed)

```cpp
void findMinSpeed() {
  Serial.println("Finding minimum speed...");

  for (int speed = 0; speed <= 100; speed++) {
    motor.setSpeed(speed);
    delay(100);

    // Here you can add encoder check
    // if motor started rotating - this is minimum
    Serial.print("Test: ");
    Serial.println(speed);
  }

  motor.stop();
}
```

## 🛠️ Compatibility

### Supported Platforms

- ✅ Arduino Uno, Nano, Mega
- ✅ Arduino Leonardo, Pro Mini
- ✅ ESP32 (all variants)
- ✅ ESP8266
- ✅ STM32 (with Arduino Core)
- ✅ Teensy
- ✅ Other Arduino-compatible boards

### Supported Drivers

- ✅ L298N, L293D
- ✅ TB6612FNG
- ✅ DRV8833, DRV8835
- ✅ ZK-5AD, ZK-5AD-V2
- ✅ BTS7960
- ✅ MX1508, MX1919
- ✅ VNH2SP30, VNH5019
- ✅ Any H-Bridge drivers

## 📝 Changelog

### Version 1.0.9
- ✅ Bilingual library support (English/Русский)
- ✅ All examples available in two languages
- ✅ Improved documentation

### Version 1.0.7
- ✅ ESP32 Arduino Core 3.x support (new PWM API)
- ✅ Added getSpeed() and getMode() methods
- ✅ Added stop() method (separate from brake)
- ✅ Copy protection for class
- ✅ Fixed constructor parameter order
- ✅ 17 examples (including mecanum wheels)
- ✅ Improved documentation

### Version 1.0.6
- Basic functionality
- Support for 4 modes
- ESP32 2.x support

## 🤝 Support and Contacts

- 🌐 **Website:** [alash-electronics.kz](https://alash-electronics.kz/)
- 💬 **GitHub:** [Issues](https://github.com/Alash-electronics/AlashMotorControlLite/issues)
- 📧 **Email:** support@alash-electronics.kz
- 📖 **Documentation:** [Wiki](https://github.com/Alash-electronics/AlashMotorControlLite/wiki)
- 🎓 **Tutorials:** [Projects and tutorials](https://alash-electronics.kz/blogs/wiki)

## 📄 License

MIT License - see [LICENSE](LICENSE) file

## 🌟 Acknowledgments

Thanks to everyone using and improving this library!

---

**Made with ❤️ in Kazakhstan | Alash Engineering**

## Keywords for search

Arduino motor control, ESP32 motor driver, DC motor library, L298N Arduino, TB6612FNG library, PWM motor control, H-bridge Arduino, motor driver library, Arduino robot, ESP32 robot control, mecanum wheels, dual motor control, Arduino motor shield, ZK-5AD driver, DRV8833 Arduino, BTS7960 library, motor control library, Arduino DC motor, ESP32 PWM, motor speed control
