#include "AlashMotorControlLite.h"

AlashMotorControlLite::AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2){
  _mode = mode;
  _pin1 = pin1;
  _pin2 = pin2;

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

AlashMotorControlLite::AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2, uint8_t pin_pwm){
  _mode = mode;
  _pin1 = pin1;
  _pin2 = pin2;
  _pin_pwm = pin_pwm;

  pinMode(_pin_pwm, OUTPUT);
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

  analogWrite(_pin_pwm, 0);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void AlashMotorControlLite::brake(){

switch (_mode){
    case DIR_PWM:
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin2, 0);
#else
        analogWrite(_pin2, 255);
#endif
        digitalWrite(_pin1, LOW);
      break;
    case PWM_PWM:
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin1, 0);
        ledcWrite(_pin2, 0);
#else
        analogWrite(_pin1, 0);
        analogWrite(_pin2, 0);
#endif
      break;
    case DIR_DIR_PWM:
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin_pwm, 255);
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

}
void AlashMotorControlLite::setSpeed(int16_t speed){
  // Make sure the speed is within the limit.
  if (speed > 100){
    speed = 100;
  }
  else if (speed < -100){
    speed = -100;
  }
  speed=map(speed,-100,100,-255,255);
  // Set the speed and direction.
  switch (_mode){
    case DIR_PWM:
      if (speed >= 0){
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin1, speed);
#else
        analogWrite(_pin2, speed);
#endif

        digitalWrite(_pin1, LOW);
      }
      else{

#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin1, -speed);
#else
        analogWrite(_pin2, -speed);
#endif

        digitalWrite(_pin1, HIGH);
      }
      break;

    case PWM_PWM:
      if (speed >= 0){
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin2, speed);
        ledcWrite(_pin1, 0);
#else
        analogWrite(_pin2, speed);
        analogWrite(_pin1, 0);
#endif
      }
      else{
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin2, 0);
        ledcWrite(_pin1, speed);
#else
        analogWrite(_pin2, 0);
        analogWrite(_pin1, speed);
#endif
      }
      break;


    case DIR_DIR_PWM:
      if (speed >= 0){
#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin_pwm, speed);
#else
        analogWrite(_pin_pwm, speed);
#endif

        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
      }
      else{

#if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_pin_pwm, -speed);
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
