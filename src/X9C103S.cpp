#include "X9C103S.h"

#if defined(USE_PCF8574)
X9C103S::X9C103S(int inc_pin, int ud_pin, int cs_pin, PCF8574 *pcf8574) {
    _inc_pin = inc_pin;
    _ud_pin = ud_pin;
    _cs_pin = cs_pin;

    this->pcf8574 = pcf8574;
}

void X9C103S::initializePot()
{
	this->pcf8574->pinMode(_inc_pin, OUTPUT);
	this->pcf8574->pinMode(_ud_pin, OUTPUT);
	this->pcf8574->pinMode(_cs_pin, OUTPUT);
	this->pcf8574->digitalWrite(_cs_pin, HIGH);
	_resistance = 1;

	this->pcf8574->digitalWrite(_ud_pin, LOW);
	this->pcf8574->digitalWrite(_cs_pin, LOW);

	for (uint8_t i = 0; i < 101; i++)
	{
    	this->pcf8574->digitalWrite(_inc_pin, LOW);
	    delay(1);
    	this->pcf8574->digitalWrite(_inc_pin, HIGH);
	    delay(1);
	}
	this->pcf8574->digitalWrite(_cs_pin, HIGH);
}

void X9C103S::setResistance(int value) {
    int _value = value;
    if (_value != _resistance) {
        if (_value < 1) {
            _value = 1;
        }
        if (_value > 100) {
            _value = 100;
        }
        int diff = _value - _resistance;

		if (diff > 0) {
        	this->pcf8574->digitalWrite(_ud_pin, HIGH);  // Set direction to increment
		} else {
			diff *= -1;
	        this->pcf8574->digitalWrite(_ud_pin, LOW);  // Set direction to decrement
		}
        this->pcf8574->digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
        for (int i = 0; i < diff; i++) {
            this->pcf8574->digitalWrite(_inc_pin, LOW);
            delay(1);
            this->pcf8574->digitalWrite(_inc_pin, HIGH);
            delay(1);
        }
        this->pcf8574->digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
        _resistance = _value;  // Update the private variable
    }
}

void X9C103S::increaseResistance(int value) {
    this->pcf8574->digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
    this->pcf8574->digitalWrite(_ud_pin, HIGH);  // Set direction to increment
    for (int i = 0; i < value; i++) {
        this->pcf8574->digitalWrite(_inc_pin, LOW);
        delay(1);
        this->pcf8574->digitalWrite(_inc_pin, HIGH);
        delay(1);
    }
    this->pcf8574->digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
    _resistance += value;  // Update the private variable
    for (; _resistance > 100;) {
        if (_resistance > 100) {
            _resistance -= 100;
        }
    }
}

void X9C103S::decreaseResistance(int value) {
    this->pcf8574->digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
    this->pcf8574->digitalWrite(_ud_pin, LOW);  // Set direction to decrement
    for (int i = 0; i < value; i++) {
        this->pcf8574->digitalWrite(_inc_pin, LOW);
        delay(1);
        this->pcf8574->digitalWrite(_inc_pin, HIGH);
        delay(1);
    }
    this->pcf8574->digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
    _resistance -= value;  // Update the private variable
    for (; _resistance < 1;) {
        if (_resistance < 1) {
            _resistance += 100;
        }
    }
}

void X9C103S::setToHighest(){
    if (_resistance != 100) {
	int pulses = 100 - _resistance;
	this->pcf8574->digitalWrite(_ud_pin, HIGH);  // Set direction to increment
	this->pcf8574->digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
	for (int i = 0; i < pulses; i++) {
		this->pcf8574->digitalWrite(_inc_pin, LOW);
    	    	delay(1);
        	this->pcf8574->digitalWrite(_inc_pin, HIGH);
	       	delay(1);
    	}
	_resistance = 100;
    }
}

void X9C103S::setToLowest(){
    for (uint8_t i = 0; i < 101; i++)
	{
    	this->pcf8574->digitalWrite(_inc_pin, LOW);
	    delay(1);
    	this->pcf8574->digitalWrite(_inc_pin, HIGH);
	    delay(1);
	}
}
#else
X9C103S::X9C103S(int inc_pin, int ud_pin, int cs_pin) {
    _inc_pin = inc_pin;
    _ud_pin = ud_pin;
    _cs_pin = cs_pin;
}

void X9C103S::initializePot()
{
	pinMode(_inc_pin, OUTPUT);
	pinMode(_ud_pin, OUTPUT);
	pinMode(_cs_pin, OUTPUT);
	digitalWrite(_cs_pin, HIGH);
	_resistance = 1;

	digitalWrite(_ud_pin, LOW);
	digitalWrite(_cs_pin, LOW);

	for (uint8_t i = 0; i < 101; i++)
	{
    	digitalWrite(_inc_pin, LOW);
	    delay(1);
    	digitalWrite(_inc_pin, HIGH);
	    delay(1);
	}
	digitalWrite(_cs_pin, HIGH);
}

void X9C103S::setResistance(int value) {
    int _value = value;
    if (_value != _resistance) {
        if (_value < 1) {
            _value = 1;
        }
        if (_value > 100) {
            _value = 100;
        }
        int diff = _value - _resistance;

		if (diff > 0) {
        	digitalWrite(_ud_pin, HIGH);  // Set direction to increment
		} else {
			diff *= -1;
	        digitalWrite(_ud_pin, LOW);  // Set direction to decrement
		}
        digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
        for (int i = 0; i < diff; i++) {
            digitalWrite(_inc_pin, LOW);
            delay(1);
            digitalWrite(_inc_pin, HIGH);
            delay(1);
        }
        digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
        _resistance = _value;  // Update the private variable
    }
}

void X9C103S::increaseResistance(int value) {
    digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
    digitalWrite(_ud_pin, HIGH);  // Set direction to increment
    for (int i = 0; i < value; i++) {
        digitalWrite(_inc_pin, LOW);
        delay(1);
        digitalWrite(_inc_pin, HIGH);
        delay(1);
    }
    digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
    _resistance += value;  // Update the private variable
    for (; _resistance > 100;) {
        if (_resistance > 100) {
            _resistance -= 100;
        }
    }
}

void X9C103S::decreaseResistance(int value) {
    digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
    digitalWrite(_ud_pin, LOW);  // Set direction to decrement
    for (int i = 0; i < value; i++) {
        digitalWrite(_inc_pin, LOW);
        delay(1);
        digitalWrite(_inc_pin, HIGH);
        delay(1);
    }
    digitalWrite(_cs_pin, HIGH);  // Disable the potentiometer
    _resistance -= value;  // Update the private variable
    for (; _resistance < 1;) {
        if (_resistance < 1) {
            _resistance += 100;
        }
    }
}

void X9C103S::setToHighest(){
    if (_resistance != 100) {
	int pulses = 100 - _resistance;
	digitalWrite(_ud_pin, HIGH);  // Set direction to increment
	digitalWrite(_cs_pin, LOW);  // Enable the potentiometer
	for (int i = 0; i < pulses; i++) {
		digitalWrite(_inc_pin, LOW);
    	    	delay(1);
        	digitalWrite(_inc_pin, HIGH);
	       	delay(1);
    	}
	_resistance = 100;
    }
}

void X9C103S::setToLowest(){
    for (uint8_t i = 0; i < 101; i++)
	{
    	digitalWrite(_inc_pin, LOW);
	    delay(1);
    	digitalWrite(_inc_pin, HIGH);
	    delay(1);
	}
}
#endif

int X9C103S::getResistance() {
    return _resistance;  // Return the value of the private variable
}
