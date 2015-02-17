# Arduino Simple Buttons Library

## Description

A library for the Arduino Uno to facilitate the use of external buttons.

## Reference

```C
void simple_interrupt(uint8_t pin, uint8_t trig, volatile void *flag)
```

| Parameter | Description |
| :--- | :--- |
| pin | the number of pin that the button is connected to (can only be 2 or 3 on Arduino Uno) |
| trig | defines when the interrupt should be triggered (LOW, CHANGE, RISING, or FALLING) |
| flag | the variable whose flag should be set to true when the interrupt is triggered |

## Example

```C
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