#ifndef _EVLK_NOPINS_H_
#define _EVLK_NOPINS_H_

#include "Arduino.h"

namespace _EVLK_NOPINS_
{
    class nopinRegister;

    class nopin_size_t
    {
    public:
        nopinRegister *const Port;
        const pin_size_t Idx;
        const pin_size_t Map;

    public:
        nopin_size_t(pin_size_t pin);
        nopin_size_t(nopinRegister &port, pin_size_t idx, pin_size_t map);
        nopin_size_t(const nopin_size_t &nopin);

        void mode(PinMode mode);
        void dwrite(PinStatus val);
        PinStatus dread();
        void awrite(int val);
        int aread();
    };

    void pinMode(nopin_size_t pin, PinMode mode);
    void digitalWrite(nopin_size_t pin, PinStatus val);
    PinStatus digitalRead(nopin_size_t pin);
    void analogWrite(nopin_size_t pin, int val);
    void analogReference(nopinRegister &reg, uint8_t mode);
    int analogRead(nopin_size_t pin);
    void pinMode(nopin_size_t pin, int mode);
    void digitalWrite(nopin_size_t pin, int status);

    class nopinRegister
    {
    private:
        nopin_size_t **creatPinArr(uint8_t groupNum, pin_size_t unitNum);
        nopin_size_t **creatPinArr(uint8_t groupNum, pin_size_t unitNum, pin_size_t *maps);
        nopin_size_t **creatPinArr(uint8_t groupNum, pin_size_t unitNum, pin_size_t maphead);

        nopin_size_t **const pins;

    protected:
        int analogResolution;

    public:
        const uint8_t GroupNum;
        const pin_size_t UnitNum;
        nopinRegister(uint8_t groupNum, pin_size_t unitNum);
        nopinRegister(uint8_t groupNum, pin_size_t unitNum, pin_size_t *maps);
        nopinRegister(uint8_t groupNum, pin_size_t unitNum, pin_size_t maphead);
        virtual ~nopinRegister();

        virtual void pinMode(nopin_size_t pin, PinMode mode) = 0;
        virtual void digitalWrite(nopin_size_t pin, PinStatus val) = 0;
        virtual PinStatus digitalRead(nopin_size_t pin) = 0;
        virtual void analogWrite(nopin_size_t pin, int val) = 0;
        virtual void analogReference(uint8_t mode) = 0;
        virtual int analogRead(nopin_size_t pin) = 0;
        void analogReadResolution(int bits);
        void pinMode(nopin_size_t pin, int mode);
        void digitalWrite(nopin_size_t pin, int status);

        bool isIn(const nopin_size_t &pin);
        pin_size_t groupNum(nopin_size_t &pin);
        pin_size_t unitNum(nopin_size_t &pin);
        nopin_size_t *const operator[](int g);
    };

    class o2nopin : public nopinRegister
    {
    public:
        o2nopin() : nopinRegister(0, 0){};
        void pinMode(nopin_size_t pin, PinMode mode) override;
        void digitalWrite(nopin_size_t pin, PinStatus val) override;
        PinStatus digitalRead(nopin_size_t pin) override;
        void analogWrite(nopin_size_t pin, int val) override;
        void analogReference(uint8_t mode) override;
        int analogRead(nopin_size_t pin) override;
    };

    extern o2nopin O2nopin;
}

#endif