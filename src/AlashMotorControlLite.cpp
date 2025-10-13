#include "AlashMotorControlLite.h"

#if defined(ARDUINO_ARCH_ESP32)
uint8_t AlashMotorControlLite::_nextChannel = 0;
#endif

AlashMotorControlLite::AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2){
  _mode = mode;
  _pin1 = pin1;
  _pin2 = pin2;
  _currentSpeed = 0;

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

#if defined(ARDUINO_ARCH_ESP32)
  if (_mode == PWM_PWM) {
    _pwm_channel1 = _nextChannel++;
    _pwm_channel2 = _nextChannel++;

    #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      // Новый API для ESP32 3.x
      ledcAttach(_pin1, 5000, 8);
      ledcAttach(_pin2, 5000, 8);
      ledcWrite(_pin1, 0);
      ledcWrite(_pin2, 0);
    #else
      // Старый API для ESP32 2.x
      ledcSetup(_pwm_channel1, 5000, 8);
      ledcSetup(_pwm_channel2, 5000, 8);
      ledcAttachPin(_pin1, _pwm_channel1);
      ledcAttachPin(_pin2, _pwm_channel2);
      ledcWrite(_pwm_channel1, 0);
      ledcWrite(_pwm_channel2, 0);
    #endif
  } else {
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
  }
#else
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
#endif
}

AlashMotorControlLite::AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2, uint8_t pin_pwm){
  _mode = mode;
  _pin1 = pin1;
  _pin2 = pin2;
  _pin_pwm = pin_pwm;
  _currentSpeed = 0;

  pinMode(_pin_pwm, OUTPUT);
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

#if defined(ARDUINO_ARCH_ESP32)
  _pwm_channel = _nextChannel++;

  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
    // Новый API для ESP32 3.x
    ledcAttach(_pin_pwm, 5000, 8);
    ledcWrite(_pin_pwm, 0);
  #else
    // Старый API для ESP32 2.x
    ledcSetup(_pwm_channel, 5000, 8);
    ledcAttachPin(_pin_pwm, _pwm_channel);
    ledcWrite(_pwm_channel, 0);
  #endif
#else
  analogWrite(_pin_pwm, 0);
#endif
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void AlashMotorControlLite::brake(){

switch (_mode){
    case DIR_PWM:
      digitalWrite(_pin1, HIGH);
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin_pwm, 0);
  #else
      ledcWrite(_pwm_channel, 0);
  #endif
#else
      analogWrite(_pin2, 255);
#endif
      break;
    case PWM_PWM:
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin1, 255);
      ledcWrite(_pin2, 255);
  #else
      ledcWrite(_pwm_channel1, 255);
      ledcWrite(_pwm_channel2, 255);
  #endif
#else
      analogWrite(_pin1, 255);
      analogWrite(_pin2, 255);
#endif
      break;
    case DIR_DIR_PWM:
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin_pwm, 255);
  #else
      ledcWrite(_pwm_channel, 255);
  #endif
#else
      analogWrite(_pin_pwm, 255);
#endif
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, HIGH);
      break;

    case DIR_DIR:
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, HIGH);
      break;
  }
  _currentSpeed = 0;
}

void AlashMotorControlLite::stop(){
  switch (_mode){
    case DIR_PWM:
      digitalWrite(_pin1, LOW);
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin_pwm, 0);
  #else
      ledcWrite(_pwm_channel, 0);
  #endif
#else
      analogWrite(_pin2, 0);
#endif
      break;
    case PWM_PWM:
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin1, 0);
      ledcWrite(_pin2, 0);
  #else
      ledcWrite(_pwm_channel1, 0);
      ledcWrite(_pwm_channel2, 0);
  #endif
#else
      analogWrite(_pin1, 0);
      analogWrite(_pin2, 0);
#endif
      break;
    case DIR_DIR_PWM:
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
      ledcWrite(_pin_pwm, 0);
  #else
      ledcWrite(_pwm_channel, 0);
  #endif
#else
      analogWrite(_pin_pwm, 0);
#endif
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, LOW);
      break;

    case DIR_DIR:
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, LOW);
      break;
  }
  _currentSpeed = 0;
}

void AlashMotorControlLite::setSpeed(int16_t speed){
  // Make sure the speed is within the limit.
  if (speed > 100){
    speed = 100;
  }
  else if (speed < -100){
    speed = -100;
  }

  _currentSpeed = speed;
  speed = map(speed, -100, 100, -255, 255);

  // Set the speed and direction.
  switch (_mode){
    case DIR_PWM:
      if (speed >= 0){
        digitalWrite(_pin1, LOW);
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin_pwm, speed);
  #else
        ledcWrite(_pwm_channel, speed);
  #endif
#else
        analogWrite(_pin2, speed);
#endif
      }
      else{
        digitalWrite(_pin1, HIGH);
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin_pwm, -speed);
  #else
        ledcWrite(_pwm_channel, -speed);
  #endif
#else
        analogWrite(_pin2, -speed);
#endif
      }
      break;

    case PWM_PWM:
      if (speed >= 0){
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin1, 0);
        ledcWrite(_pin2, speed);
  #else
        ledcWrite(_pwm_channel1, 0);
        ledcWrite(_pwm_channel2, speed);
  #endif
#else
        analogWrite(_pin1, 0);
        analogWrite(_pin2, speed);
#endif
      }
      else{
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin1, -speed);
        ledcWrite(_pin2, 0);
  #else
        ledcWrite(_pwm_channel1, -speed);
        ledcWrite(_pwm_channel2, 0);
  #endif
#else
        analogWrite(_pin1, -speed);
        analogWrite(_pin2, 0);
#endif
      }
      break;


    case DIR_DIR_PWM:
      if (speed >= 0){
#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin_pwm, speed);
  #else
        ledcWrite(_pwm_channel, speed);
  #endif
#else
        analogWrite(_pin_pwm, speed);
#endif

        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
      }
      else{

#if defined(ARDUINO_ARCH_ESP32)
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(_pin_pwm, -speed);
  #else
        ledcWrite(_pwm_channel, -speed);
  #endif
#else
        analogWrite(_pin_pwm, -speed);
#endif
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, HIGH);
      }
      break;

    case DIR_DIR:
      if (speed >= 0){
        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
      }
      else{
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, HIGH);
      }
      break;
  }
}

int16_t AlashMotorControlLite::getSpeed() const {
  return _currentSpeed;
}

MODE AlashMotorControlLite::getMode() const {
  return _mode;
}
