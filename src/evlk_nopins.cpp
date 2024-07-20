#include "evlk_nopins.h"

namespace _EVLK_NOPINS_
{
    nopin_size_t::nopin_size_t(pin_size_t pin) : Port(&O2nopin), Idx(-1), Map(pin){};
    nopin_size_t::nopin_size_t(nopinRegister &port, pin_size_t idx, pin_size_t map) : Port(&port), Idx(idx), Map(map){};
    nopin_size_t::nopin_size_t(const nopin_size_t &nopin) : Port(nopin.Port), Idx(nopin.Idx), Map(nopin.Map){};
    void nopin_size_t::mode(PinMode mode) { return Port->pinMode(*this, mode); };
    void nopin_size_t::dwrite(PinStatus val) { return Port->digitalWrite(*this, val); };
    PinStatus nopin_size_t::dread() { return Port->digitalRead(*this); };
    void nopin_size_t::awrite(int val) { return Port->analogWrite(*this, val); };
    int nopin_size_t::aread() { return Port->analogRead(*this); };

    void pinMode(nopin_size_t pin, PinMode mode) { return pin.mode(mode); };
    void digitalWrite(nopin_size_t pin, PinStatus val) { return pin.dwrite(val); };
    PinStatus digitalRead(nopin_size_t pin) { return pin.dread(); };
    void analogWrite(nopin_size_t pin, int val) { return pin.awrite(val); };
    void analogReference(nopinRegister &reg, uint8_t mode) { return reg.analogReference(mode); };
    int analogRead(nopin_size_t pin) { return pin.aread(); };
    void pinMode(nopin_size_t pin, int mode) { return pinMode(pin, (PinMode)mode); };
    void digitalWrite(nopin_size_t pin, int status) { return digitalWrite(pin, (PinStatus)status); };

    nopin_size_t **nopinRegister::creatPinArr(uint8_t groupNum, pin_size_t unitNum)
    {
        if (!groupNum || !unitNum)
            return NULL;
        nopin_size_t **arr = new nopin_size_t *[groupNum];
        for (int i = 0; i < groupNum; ++i)
            arr[i] = reinterpret_cast<nopin_size_t *>(new char[unitNum * sizeof(nopin_size_t)]);
        for (int i = 0; i < groupNum; ++i)
            for (int j = 0; j < unitNum; ++j)
                new (&arr[i][j]) nopin_size_t(*this, i * unitNum + j, -1);
        return arr;
    };
    nopin_size_t **nopinRegister::creatPinArr(uint8_t groupNum, pin_size_t unitNum, pin_size_t *maps)
    {
        if (!groupNum || !unitNum)
            return NULL;
        nopin_size_t **arr = new nopin_size_t *[groupNum];
        for (int i = 0; i < groupNum; ++i)
            arr[i] = reinterpret_cast<nopin_size_t *>(new char[unitNum * sizeof(nopin_size_t)]);
        for (int i = 0; i < groupNum; ++i)
            for (int j = 0; j < unitNum; ++j)
                new (&arr[i][j]) nopin_size_t(*this, i * unitNum + j, maps[i * unitNum + j]);
        return arr;
    };
    nopin_size_t **nopinRegister::creatPinArr(uint8_t groupNum, pin_size_t unitNum, pin_size_t maphead)
    {
        if (!groupNum || !unitNum)
            return NULL;
        nopin_size_t **arr = new nopin_size_t *[groupNum];
        for (int i = 0; i < groupNum; ++i)
            arr[i] = reinterpret_cast<nopin_size_t *>(new char[unitNum * sizeof(nopin_size_t)]);
        for (int i = 0; i < groupNum; ++i)
            for (int j = 0; j < unitNum; ++j)
                new (&arr[i][j]) nopin_size_t(*this, i * unitNum + j, maphead + i * unitNum + j);
        return arr;
    };
    nopinRegister::nopinRegister(uint8_t groupNum, pin_size_t unitNum)
        : GroupNum(groupNum), UnitNum(unitNum), pins(creatPinArr(groupNum, unitNum)){};
    nopinRegister::nopinRegister(uint8_t groupNum, pin_size_t unitNum, pin_size_t *maps)
        : GroupNum(groupNum), UnitNum(unitNum), pins(creatPinArr(groupNum, unitNum, maps)){};
    nopinRegister::nopinRegister(uint8_t groupNum, pin_size_t unitNum, pin_size_t maphead)
        : GroupNum(groupNum), UnitNum(unitNum), pins(creatPinArr(groupNum, unitNum, maphead)){};
    void nopinRegister::pinMode(nopin_size_t pin, int mode) { return this->pinMode(pin, (PinMode)mode); };
    void nopinRegister::digitalWrite(nopin_size_t pin, int status) { return this->digitalWrite(pin, (PinStatus)status); };
    void nopinRegister::analogReadResolution(int bits) { this->analogResolution = bits > 0 && bits <= 32 ? bits : 10; };

    bool nopinRegister::isIn(const nopin_size_t &pin) { return pin.Port == this && pin.Idx < GroupNum * UnitNum; };
    pin_size_t nopinRegister::groupNum(nopin_size_t &pin) { return pin.Idx / UnitNum; };
    pin_size_t nopinRegister::unitNum(nopin_size_t &pin) { return pin.Idx % UnitNum; };
    nopin_size_t *const nopinRegister::operator[](int g) { return pins[g]; };
    nopinRegister::~nopinRegister()
    {
        if (pins)
        {
            for (int i = 0; i < GroupNum; ++i)
            {
                for (int j = 0; j < UnitNum; ++j)
                    pins[i][j].~nopin_size_t();
                delete[] reinterpret_cast<char *>(pins[i]);
            }
            delete[] pins;
        }
    };

    void o2nopin::pinMode(nopin_size_t pin, PinMode mode) { return ::pinMode(pin.Map, mode); };
    void o2nopin::digitalWrite(nopin_size_t pin, PinStatus val) { return ::digitalWrite(pin.Map, val); };
    PinStatus o2nopin::digitalRead(nopin_size_t pin) { return ::digitalRead(pin.Map); };
    void o2nopin::analogWrite(nopin_size_t pin, int val) { return ::analogWrite(pin.Map, val); };
    void o2nopin::analogReference(uint8_t mode) { return ::analogReference(mode); };
    int o2nopin::analogRead(nopin_size_t pin) { return ::analogRead(pin.Map); };

    o2nopin O2nopin;
}