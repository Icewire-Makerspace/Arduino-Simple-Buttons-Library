#include "simple_buttons.h"

/*
  Arduino Uno external interrupts:
  Pin 2: int_0
  Pin 3: int_1
*/

volatile boolean *d2flag = false;
volatile boolean *d3flag = false;

void simple_interrupt(uint8_t pin, uint8_t trig, volatile void *flag) {
	d2flag = flag;

	switch (pin) {
	case 2:
		/* D2 */
		EIFR &= ~bit(INTF0);	/* Clear D2 interrupt flag */
		EICRA &= ~bit(ISC00);	/* Clear control register */
		EICRA &= ~bit(ISC01);
		switch (trig) {
		case LOW:
			break;
		case CHANGE:
			EICRA |= bit(ISC00);	/* Trigger on change */
			break;
		case FALLING:
			EICRA |= bit(ISC01);	/* Trigger on falling edge */
			break;
		case RISING:
			EICRA |= bit(ISC00) | bit(ISC01);	/* Trigger on rising edge */
			break;
		}
		EIMSK |= bit(INT0);	/* Enable INT0 interrupt */
		break;
	case 3:
		/* D3 */
		EIFR &= ~bit(INTF1);	/* Clear D3 interrupt flag */
		EICRA &= ~bit(ISC10);	/* Clear control register */
		EICRA &= ~bit(ISC11);
		switch (trig) {
		case LOW:
			break;
		case CHANGE:
			EICRA |= bit(ISC10);	/* Trigger on change */
			break;
		case FALLING:
			EICRA |= bit(ISC11);	/* Trigger on falling edge */
			break;
		case RISING:
			EICRA |= bit(ISC10) | bit(ISC11);	/* Trigger on rising edge */
			break;
		}
		EIMSK |= bit(INT1);	/* Enable INT0 interrupt */
		break;
	}

	/* Enable interrupts */
	interrupts();
}

void simple_debounce(uint8_t pin, boolean state) {
	delay(20);
	while (digitalRead(pin) != state);
}

ISR(INT0_vect) {
	*d2flag = true;
}

ISR(INT1_vect) {
	*d2flag = true;
}
