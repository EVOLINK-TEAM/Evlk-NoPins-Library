#ifndef _EVLK_NOPINS_H_
#define _EVLK_NOPINS_H_

#include "Arduino.h"
#include <cstdint>

#ifndef ARDUINO_API_H
#ifdef EXTENDED_PIN_MODE
typedef uint32_t pin_size_t;
#else
typedef uint8_t pin_size_t;
#endif
typedef uint8_t PinMode;
typedef uint8_t PinStatus;
#endif

namespace _EVLK_NOPINS_ {

class nopinRegister;

struct nopin_size_t {
  private:
    nopinRegister *const Port;
    const pin_size_t Idx;

  public:
    nopin_size_t(pin_size_t pin);
    nopin_size_t(nopinRegister &port, pin_size_t idx);

    friend void pinMode(nopin_size_t pin, PinMode mode);
    friend void digitalWrite(nopin_size_t pin, PinStatus val);
    friend PinStatus digitalRead(nopin_size_t pin);
    friend void analogWrite(nopin_size_t pin, int val);
    friend void analogReference(nopinRegister &reg, uint8_t mode);
    friend int analogRead(nopin_size_t pin);
    friend void pinMode(nopin_size_t pin, int mode);
    friend void digitalWrite(nopin_size_t pin, int status);
};

void pinMode(nopin_size_t pin, PinMode mode);
void digitalWrite(nopin_size_t pin, PinStatus val);
PinStatus digitalRead(nopin_size_t pin);
void analogWrite(nopin_size_t pin, int val);
void analogReference(nopinRegister &reg, uint8_t mode);
int analogRead(nopin_size_t pin);
void pinMode(nopin_size_t pin, int mode);
void digitalWrite(nopin_size_t pin, int status);

class nopinRegister {
  protected:
    int analogResolution;

  public:
    virtual void pinMode(pin_size_t pin, PinMode mode)       = 0;
    virtual void digitalWrite(pin_size_t pin, PinStatus val) = 0;
    virtual PinStatus digitalRead(pin_size_t pin)            = 0;
    virtual void analogWrite(pin_size_t pin, int val)        = 0;
    virtual void analogReference(uint8_t mode)               = 0;
    virtual int analogRead(pin_size_t pin)                   = 0;
    virtual void pinMode(pin_size_t pin, int mode);
    virtual void digitalWrite(pin_size_t pin, int status);
    virtual void digitalWrite(uint8_t mask[], int n, int status); // 小端
    virtual void analogReadResolution(int bits);

    const nopin_size_t operator[](int i);
};

} // namespace _EVLK_NOPINS_

#endif
