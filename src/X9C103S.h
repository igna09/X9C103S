#ifndef X9C103S_H
#define X9C103S_H

/**
 * Decomment below line to enable PCF8574
*/
#define USE_PCF8574

#if defined(USE_PCF8574)
#include <PCF8574.h>
#endif

#include <Arduino.h>

class X9C103S {
public:
    #if defined(USE_PCF8574)
    X9C103S(int inc_pin, int ud_pin, int cs_pin, PCF8574 *pcf8574);
    #else
    X9C103S(int inc_pin, int ud_pin, int cs_pin);
    #endif
    void initializePot();
    void setResistance(int value);
    void increaseResistance(int value);
    void decreaseResistance(int value);
    void setToHighest();
    void setToLowest();
    int getResistance();

private:
    int _inc_pin;
    int _ud_pin;
    int _cs_pin;
    int _resistance; // Private variable to store the resistance value

    #if defined(USE_PCF8574)
    PCF8574 *pcf8574;
    #endif
};

#endif
