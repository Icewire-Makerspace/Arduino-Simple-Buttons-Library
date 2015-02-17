# Arduino Simple Buttons Library

## Description

A library for the Arduino Uno to make using external button interrupts and debouncing easier.

## Examples

```
#include "simple_interrupts.h"

volatile boolean pressed;

void setup() {
	Serial.begin(9600);
	pinMode(2, INPUT);
	pressed = false;
	simple_interrupt(2, RISING, &pressed);
}

void loop() {
	if (pressed) {
		Serial.println("Button was pressed");
		simple_debounce(2, LOW);
		pressed = false;
	}
}
```