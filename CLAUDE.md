# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**AlashMotorControlLite** is an Arduino library for controlling DC motors through various motor driver chips. The library provides a unified API that abstracts different motor driver configurations, supporting both Arduino and ESP32 platforms.

**Current Version:** 1.1.0
**Repository:** https://github.com/Alash-electronics/AlashMotorControlLite
**License:** MIT
**Status:** Ready for Arduino Library Manager

**Key Design Goals:**
- Simple, intuitive speed control (-100 to 100 range)
- Support for multiple motor driver types through MODE enum
- Cross-platform compatibility (Arduino, ESP32)
- Protection against incorrect usage (automatic speed limiting, copy prevention)
- ESP32 Arduino Core 2.x and 3.x compatibility
- Multilingual support (English, Russian, Kazakh)
- Comprehensive examples (17 total × 3 languages) from basic to advanced

## Core Architecture

### MODE System

The library uses a MODE enum to handle 4 different motor driver configurations:

1. **DIR_PWM** (2 pins): 1 direction pin + 1 PWM pin
   - Compatible with: L298N (most common)
   - pin1 = Direction (IN1/DIR)
   - pin2 = PWM speed control (ENA/PWM)
   - Most common Arduino setup

2. **PWM_PWM** (2 pins): 2 PWM pins for bidirectional control
   - Compatible with: TB6612FNG, ZK-5AD, DRV8833
   - pin1 = First PWM (IN1)
   - pin2 = Second PWM (IN2)
   - Recommended for ESP32 (abundant PWM channels)
   - Better control and braking

3. **DIR_DIR_PWM** (3 pins): 2 direction pins + 1 PWM enable pin
   - Compatible with: L293D, some L298N configurations
   - pin1 = First direction (IN1)
   - pin2 = Second direction (IN2)
   - pin_pwm = PWM enable (EN)
   - Clear separation of direction and speed

4. **DIR_DIR** (2 pins): 2 digital pins, no PWM (on/off only)
   - For relay modules or drivers without PWM input
   - pin1 = First control pin
   - pin2 = Second control pin
   - Speed value ignored, only direction matters

**Constructor Signatures:**
```cpp
// 2-pin constructor (DIR_PWM, PWM_PWM, DIR_DIR)
AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2);

// 3-pin constructor (DIR_DIR_PWM only)
AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2, uint8_t pin_pwm);
```

**CRITICAL:** Parameter order is `(mode, pin1, pin2, [pin_pwm])` - this was corrected in v1.0.7

### ESP32 Dual PWM API Support

The library supports both ESP32 Arduino Core versions:

- **ESP32 2.x** (old API): `ledcSetup()` + `ledcAttachPin()` + `ledcWrite(channel, duty)`
- **ESP32 3.x** (new API): `ledcAttach(pin, freq, res)` + `ledcWrite(pin, duty)`

This is handled via `ESP_ARDUINO_VERSION` macro checks throughout the codebase. When adding ESP32 PWM code, always include both API branches.

**ESP32 PWM Channel Management:**
- Static `_nextChannel` counter auto-assigns channels (ESP32 2.x only)
- PWM frequency: 5000 Hz, 8-bit resolution
- PWM_PWM mode uses 2 channels per motor instance

### Speed System

**User-facing API:** Speed range is -100 to 100
- Negative values = backward
- Positive values = forward
- Zero = stopped

**Internal implementation:** Speeds are mapped to 0-255 PWM duty cycle using Arduino's `map()` function.

**Automatic Protection:**
- Values > 100 are clamped to 100
- Values < -100 are clamped to -100
- `_currentSpeed` tracks the user-specified speed (not PWM value)

### Stop vs Brake

Two stopping methods with different behaviors:

- **stop()**: Coast stop - disables motor, allows free spinning
- **brake()**: Active braking - shorts motor terminals, rapid stop

Implementation varies by MODE but generally:
- `stop()`: Sets all control pins to LOW or PWM to 0
- `brake()`: Sets specific pin combinations that short the H-bridge

## Public API Methods

```cpp
void setSpeed(int16_t speed);     // Set speed -100 to 100 (auto-clamped)
void brake();                      // Active brake (shorts motor terminals)
void stop();                       // Coast stop (disables motor, free spin)
int16_t getSpeed() const;         // Get current user-specified speed
MODE getMode() const;             // Get driver mode configuration
```

**New in v1.0.7:**
- `stop()` - Coast stop method (different from brake)
- `getSpeed()` - Query current speed setting
- `getMode()` - Query driver configuration

## Examples Structure

The library includes **17 examples** available in **3 languages** (51 total files):

### Multilingual Organization

Examples are organized in language-specific folders that appear as separate sections in Arduino IDE:
- **examples/EN/** - English comments and Serial output
- **examples/RU/** - Russian comments and Serial output (Русский)
- **examples/KZ/** - Kazakh comments and Serial output (Қазақ)

Each language folder contains identical examples with localized comments and strings.

### Arduino IDE Display

When installed, examples appear in Arduino IDE as:
```
AlashMotorControlLite →
  ├─ EN →
  │   ├─ AllModesDemo
  │   ├─ DIR_PWM
  │   └─ ... (17 examples in English)
  ├─ RU →
  │   ├─ AllModesDemo
  │   ├─ DIR_PWM
  │   └─ ... (17 examples in Russian)
  └─ KZ →
      ├─ AllModesDemo
      ├─ DIR_PWM
      └─ ... (17 examples in Kazakh)
```

### Example Categories

**Basic Mode Examples (4):**
Demonstrate each MODE type:
- **DIR_PWM** - Most common mode (L298N-style)
- **PWM_PWM** - Dual PWM mode (TB6612FNG-style)
- **DIR_DIR_PWM** - Three-pin mode (L293D-style)
- **DIR_DIR** - Binary control (no PWM)

**Driver-Specific Examples (6):**
Practical wiring for popular drivers:
- **DIR_PWM_DualMotor** - Two motors with TB6612FNG
- **DIR_DIR_PWM_DualMotor** - Two motors with L298N
- **DIR_DIR_PWM_pot** - Potentiometer speed control
- **PWM_PWM_DualMotor** - Dual motor generic setup
- **ESP32_ZK5AD_SingleMotor** - Single motor on ESP32
- **ESP32_ZK5AD_DualMotor** - Two motors with ZK-5AD

**ESP32 Advanced Examples (2):**
Complex ESP32-specific applications:
- **ESP32_Mecanum_4WD_Demo** - 4-wheel mecanum omnidirectional robot
- **ESP32_Mecanum_Serial** - Interactive serial control for mecanum

**Educational Examples (5):**
Teaching library features and best practices:
- **StopVsBrake** - Demonstrates difference between stop() and brake()
- **GettersDemo** - Shows usage of getSpeed() and getMode()
- **SmoothSpeed** - Ramping and gradual speed changes
- **AllModesDemo** - Comprehensive comparison of all 4 modes
- **SpeedLimits** - Speed clamping and boundary testing
- **DirectionChange** - Safe direction reversal techniques
- **MultiMotorSync** - Synchronizing multiple motors

### Example Conventions

- **Multilingual support:** Each example available in EN, RU, and KZ
- **Language headers:** Each file includes navigation links to other language versions
- **Serial output at 115200 baud**
- **Platform-specific code:** Uses `#if defined(ARDUINO_ARCH_ESP32)` conditionals
- **Detailed connection diagrams** in file header comments
- **F() macro usage:** ALL string literals wrapped in F() for Arduino Uno RAM optimization
- **Box-drawing characters** for visual formatting (═, ║, ╔, ╗, ╚, ╝)
- **Demonstrate proper patterns:** Smooth ramping, synchronized multi-motor control, etc.

## Building and Testing

This is an Arduino library. No traditional build system.

**To test locally:**
1. Symlink or copy library to Arduino libraries folder:
   - Windows: `Documents\Arduino\libraries\AlashMotorControlLite`
   - macOS: `~/Documents/Arduino/libraries/AlashMotorControlLite`
   - Linux: `~/Arduino/libraries/AlashMotorControlLite`

2. Open Arduino IDE and verify any example compiles:
   - File → Examples → AlashMotorControlLite → [example]
   - Select board (Arduino Uno, ESP32 Dev Module, etc.)
   - Sketch → Verify/Compile

3. For ESP32 testing, ensure ESP32 board package is installed:
   - File → Preferences → Additional Board Manager URLs
   - Add: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`

**No automated tests exist.** Testing requires physical hardware (motor + driver + microcontroller).

## Library Metadata Files

- **library.properties**: Arduino library metadata (version, author, category)
  - Update `version` field when releasing
  - Current: 1.1.0

- **keywords.txt**: Arduino IDE syntax highlighting
  - Format: `keyword<TAB>KEYWORD_TYPE`
  - Must include all public methods and MODE enum values

## Critical Implementation Details

### Constructor Overloading
Two constructors handle 2-pin and 3-pin configurations:
- `AlashMotorControlLite(MODE, pin1, pin2)` for DIR_PWM, PWM_PWM, DIR_DIR
- `AlashMotorControlLite(MODE, pin1, pin2, pin_pwm)` for DIR_DIR_PWM

**Parameter order is critical** - do not reorder pins as it breaks compatibility.

### Copy Prevention
Class has private copy constructor and assignment operator to prevent multiple objects controlling the same pins. Arduino doesn't have proper RAII, so copying would lead to pin conflicts.

### Static Channel Counter (ESP32)
The `_nextChannel` static variable ensures each motor instance gets unique PWM channels on ESP32 2.x. This is a global counter that never resets during runtime. If creating/destroying many motor objects, be aware of the 16-channel limit on ESP32.

## Common Modifications

### Adding a new MODE
1. Add enum value to `MODE` in AlashMotorControlLite.h
2. Add case to switch statements in: `setSpeed()`, `brake()`, `stop()`
3. Update constructor initialization if needed
4. Add to keywords.txt
5. Create example demonstrating the mode
6. Update AllModesDemo example

### Supporting new PWM API (future ESP32 versions)
Add another `#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(X, Y, Z)` branch in all PWM-related code sections (both constructors, setSpeed, brake, stop).

### Adding new methods
1. Declare in public section of AlashMotorControlLite.h
2. Implement in AlashMotorControlLite.cpp
3. Add to keywords.txt with appropriate KEYWORD type
4. Create demonstration example
5. Document in existing examples where relevant

## Language and Style

- **Source code comments in English** (AlashMotorControlLite.h and .cpp)
- **Code in English** (class names, variables, functions)
- **Examples multilingual:** Available in EN (English), RU (Russian), and KZ (Kazakh) folders
- **Target audience:** International makers, Kazakhstan/Russia market (hence RU support)
- Examples use extensive Serial.println() with box-drawing characters for visual formatting
- Maintain consistent indentation (2 spaces in .cpp/.h files)
- Use descriptive variable names even if longer

## Platform-Specific Notes

**Arduino (AVR):**
- Limited PWM pins (usually 3, 5, 6, 9, 10, 11)
- Use `analogWrite()` directly
- DIR_PWM mode most common

**ESP32:**
- All pins support PWM (via LEDC peripheral)
- PWM_PWM mode recommended (2 pins instead of 1 PWM + 1 digital)
- Must handle API version differences (2.x vs 3.x)
- ZK-5AD driver popular in this ecosystem

## Repository Structure

```
AlashMotorControlLite/
├── src/
│   ├── AlashMotorControlLite.h      # Class declaration, MODE enum (English comments)
│   └── AlashMotorControlLite.cpp    # Implementation with platform ifdefs (English comments)
├── examples/                         # Multilingual examples (51 total files)
│   ├── EN/                           # English examples (17 examples)
│   │   ├── AllModesDemo/
│   │   ├── DIR_PWM/
│   │   ├── DIR_PWM_DualMotor/
│   │   ├── DIR_DIR_PWM/
│   │   ├── DIR_DIR_PWM_DualMotor/
│   │   ├── DIR_DIR_PWM_pot/
│   │   ├── PWM_PWM_DualMotor/
│   │   ├── DirectionChange/
│   │   ├── ESP32_Mecanum_4WD_Demo/
│   │   ├── ESP32_Mecanum_Serial/
│   │   ├── ESP32_ZK5AD_DualMotor/
│   │   ├── ESP32_ZK5AD_SingleMotor/
│   │   ├── GettersDemo/
│   │   ├── MultiMotorSync/
│   │   ├── SmoothSpeed/
│   │   ├── SpeedLimits/
│   │   └── StopVsBrake/
│   ├── RU/                           # Russian examples (17 examples)
│   │   └── [same 17 examples as EN/]
│   └── KZ/                           # Kazakh examples (17 examples)
│       └── [same 17 examples as EN/]
├── library.properties                # Arduino library metadata
├── keywords.txt                      # IDE syntax highlighting
├── LICENSE                           # MIT license
├── README.md                         # English documentation (primary)
├── README_ru.md                      # Russian documentation
├── CLAUDE.md                         # This file - AI assistant guide
├── PUBLISHING.md                     # Detailed Arduino Library Manager guide
└── QUICK_PUBLISH.md                  # Quick 3-step publishing guide
```

## Arduino Library Manager Registration

**Status:** Ready for publication

The library meets all Arduino Library Manager requirements:
- ✅ Correct folder structure (src/, examples/)
- ✅ Valid library.properties with detailed metadata
- ✅ MIT License file
- ✅ Comprehensive README.md
- ✅ keywords.txt for IDE syntax highlighting
- ✅ 17 working examples
- ✅ Public GitHub repository

**Publication Process:**
1. Create git tag: `git tag -a 1.1.0 -m "Version 1.1.0"`
2. Push tag: `git push origin 1.1.0`
3. Create GitHub Release with tag 1.1.0
4. Wait 24-48 hours for automatic indexing

See PUBLISHING.md for detailed step-by-step instructions.

## Common Code Patterns for AI Generation

### Creating Motor Objects

```cpp
// Arduino with L298N (DIR_PWM mode)
AlashMotorControlLite motor(DIR_PWM, 4, 3);  // pin1=DIR, pin2=PWM

// ESP32 with TB6612FNG (PWM_PWM mode)
AlashMotorControlLite motor(PWM_PWM, 32, 33);  // pin1=IN1, pin2=IN2

// Multiple motors for robot
AlashMotorControlLite motorLeft(PWM_PWM, 32, 33);
AlashMotorControlLite motorRight(PWM_PWM, 25, 26);
```

### Basic Motor Control

```cpp
motor.setSpeed(75);      // 75% forward
delay(2000);
motor.setSpeed(-50);     // 50% reverse
delay(2000);
motor.stop();            // Coast to a stop
motor.brake();           // Active brake
```

### Smooth Speed Ramping

```cpp
void rampSpeed(AlashMotorControlLite &motor, int targetSpeed, unsigned long duration) {
    int currentSpeed = motor.getSpeed();
    int steps = abs(targetSpeed - currentSpeed);
    if (steps == 0) return;

    unsigned long stepDelay = duration / steps;

    for (int i = 1; i <= steps; i++) {
        int newSpeed = currentSpeed + ((targetSpeed - currentSpeed) * i / steps);
        motor.setSpeed(newSpeed);
        delay(stepDelay);
    }
}
```

### Multi-Motor Robot Control

```cpp
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
```

### Mecanum Wheel Kinematics (4 motors)

```cpp
// vx: forward/backward, vy: strafe left/right, rotation: turn CW/CCW
void mecanumDrive(int vx, int vy, int rotation) {
    int speedFL = vx + vy + rotation;  // Front Left
    int speedFR = vx - vy - rotation;  // Front Right
    int speedRL = vx - vy + rotation;  // Rear Left
    int speedRR = vx + vy - rotation;  // Rear Right

    // Normalize if any speed exceeds 100
    int maxSpeed = max(max(abs(speedFL), abs(speedFR)),
                       max(abs(speedRL), abs(speedRR)));
    if (maxSpeed > 100) {
        speedFL = (speedFL * 100) / maxSpeed;
        speedFR = (speedFR * 100) / maxSpeed;
        speedRL = (speedRL * 100) / maxSpeed;
        speedRR = (speedRR * 100) / maxSpeed;
    }

    motorFL.setSpeed(speedFL);
    motorFR.setSpeed(speedFR);
    motorRL.setSpeed(speedRL);
    motorRR.setSpeed(speedRR);
}
```

## Supported Hardware

### Motor Drivers (Tested)
- **L298N** - Most popular, 2A per channel, 5-35V
- **TB6612FNG** - Compact, 1.2A per channel, 2.7-5.5V
- **ZK-5AD** - Dual motor, 3A per channel, 6-27V
- **DRV8833** - Low voltage, 1.5A per channel, 2.7-10.8V
- **BTS7960** - High current, 43A, 5.5-27V (single channel)
- **L293D** - Classic IC, 0.6A per channel, 4.5-36V

### Platforms (Tested)
- Arduino Uno, Mega, Nano (ATmega328P, ATmega2560)
- ESP32 (all variants) - Arduino Core 2.x and 3.x
- ESP8266
- STM32 (Arduino framework)

## Arduino Uno RAM Optimization

**CRITICAL:** Arduino Uno has only 2KB of RAM. String literals in `Serial.print("text")` consume RAM by default.

**Solution:** All examples use the `F()` macro to store strings in flash memory instead of RAM.

### Correct Usage:
```cpp
// ✓ CORRECT - String stored in flash memory
Serial.println(F("Motor forward"));

// ✗ WRONG - String consumes precious RAM
Serial.println("Motor forward");
```

### Why This Matters:
- Arduino Uno: 2048 bytes RAM
- Educational examples have 40-143 Serial.print calls
- Without F(): Can use 4000+ bytes (exceeds available RAM!)
- With F(): Uses only ~200-400 bytes RAM

### When Adding New Examples:
**ALWAYS** wrap all string literals with `F()` macro:
- `Serial.print(F("text"))`
- `Serial.println(F("text"))`
- Do NOT wrap variables: `Serial.print(motor.getSpeed())` ← correct as-is

## Version History

### v1.1.0 (Current - Multilingual Release)
- ✅ **Multilingual support:** Examples now available in EN, RU, and KZ
- ✅ **Source code in English:** All comments in .h and .cpp files translated to English
- ✅ **Bilingual README:** README.md (English primary) + README_ru.md (Russian)
- ✅ **New examples structure:** EN/, RU/, KZ/ folders (51 total example files)
- ✅ **Improved accessibility:** Users can choose their preferred language in Arduino IDE
- ✅ **F() macros preserved:** All string literals wrapped for Arduino Uno RAM optimization

### v1.0.9 (Previous)
- ✅ Library maintenance release
- ✅ Removed examples with external dependencies (Servo, IR libraries)
- ✅ Clean standalone library with 17 self-contained examples

### v1.0.7-1.0.8
- ✅ ESP32 Arduino Core 3.x support (dual PWM API)
- ✅ Added stop(), getSpeed(), getMode() methods
- ✅ Copy protection (private copy constructor)
- ✅ SEO-optimized README for humans and AI
- ✅ Publishing guides (PUBLISHING.md, QUICK_PUBLISH.md)
- ✅ Corrected constructor parameter order
- ✅ Fixed all examples to use -100 to 100 speed range
- ✅ All examples use F() macro for Arduino Uno RAM optimization

### v1.0.6 and earlier
- Basic motor control functionality
- 4 MODE types support
- ESP32 2.x compatibility

## Keywords for Search/SEO

Arduino motor control, ESP32 motor driver, DC motor library, L298N Arduino, TB6612FNG library, PWM motor control, H-bridge Arduino, motor driver library, Arduino robot, ESP32 robot control, mecanum wheels, dual motor control, Arduino motor shield, ZK-5AD driver, DRV8833 Arduino, BTS7960 library, L293D motor control, motor speed control, Arduino PWM, ESP32 PWM

## External Resources

- **Website:** https://alash-electronics.kz/
- **GitHub:** https://github.com/Alash-electronics/AlashMotorControlLite
- **Support:** support@alash-electronics.kz
- **Target Market:** Kazakhstan, Russia (hence Russian documentation)
- **License:** MIT (free for commercial and personal use)
