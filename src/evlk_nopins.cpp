#include "evlk_nopins.h"

namespace _EVLK_NOPINS_ {
nopin_size_t::nopin_size_t(pin_size_t pin) : Port(NULL), Idx(pin) {};
nopin_size_t::nopin_size_t(nopinRegister &port, pin_size_t idx) : Port(&port), Idx(idx) {};

void pinMode(nopin_size_t pin, PinMode mode) {
    return !pin.Port ? ::pinMode(pin.Idx, mode) : pin.Port->pinMode(pin.Idx, mode);
};
void digitalWrite(nopin_size_t pin, PinStatus val) {
    return !pin.Port ? ::digitalWrite(pin.Idx, val) : pin.Port->digitalWrite(pin.Idx, val);
};
PinStatus digitalRead(nopin_size_t pin) {
    return !pin.Port ? ::digitalRead(pin.Idx) : pin.Port->digitalRead(pin.Idx);
};
void analogWrite(nopin_size_t pin, int val) {
    return !pin.Port ? ::analogWrite(pin.Idx, val) : pin.Port->analogWrite(pin.Idx, val);
};
void analogReference(nopinRegister &reg, uint8_t mode) { reg.analogReference(mode); };
int analogRead(nopin_size_t pin) {
    return !pin.Port ? ::analogRead(pin.Idx) : pin.Port->analogRead(pin.Idx);
};

#ifndef ARDUINO_API_H
void pinMode(nopin_size_t pin, int mode) {
    return !pin.Port ? ::pinMode(pin.Idx, mode) : pin.Port->pinMode(pin.Idx, mode);
};
void digitalWrite(nopin_size_t pin, int status) {
    return !pin.Port ? ::digitalWrite(pin.Idx, status) : pin.Port->digitalWrite(pin.Idx, status);
};
#else
void pinMode(nopin_size_t pin, int mode) {
    return !pin.Port ? arduino::pinMode(pin.Idx, mode) : pin.Port->pinMode(pin.Idx, mode);
};
void digitalWrite(nopin_size_t pin, int status) {
    return !pin.Port ? arduino::digitalWrite(pin.Idx, status)
                     : pin.Port->digitalWrite(pin.Idx, status);
};
#endif

void nopinRegister::pinMode(pin_size_t pin, int mode) { return this->pinMode(pin, (PinMode)mode); };
void nopinRegister::digitalWrite(pin_size_t pin, int status) {
    return this->digitalWrite(pin, (PinStatus)status);
};
void nopinRegister::digitalWrite(uint8_t mask[], int n, int status) {
    for (size_t i = 0; i < n; i++)
        for (int j = 0, m = mask[n - i - 1]; j < 8; j++, m >>= 1)
            if ((m >> j) & 1)
                this->digitalWrite(i * 8 + j, status);
};
void nopinRegister::analogReadResolution(int bits) { analogResolution = bits; };
const nopin_size_t nopinRegister::operator[](int i) { return nopin_size_t(*this, i); };
} // namespace _EVLK_NOPINS_
