#ifndef ENCODERINTERFACE_H_
#define ENCODERINTERFACE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int phaseA = 0;
volatile int phaseB = 0;
volatile int count = 0;

void encoder_init(void) {
	EICRA |= (1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // Trigger on any change for INT0 and INT1
	EIMSK |= (1<<INT1) | (1<<INT0); // Enable INT0 and INT1 interrupts
	DDRD &= (~(1 << DDD2)) & (~(1 << DDD3)); // Set PD2 and PD3 as inputs
	PORTD |= (1 << PORTD2) | (1 << PORTD3);  // Enable pull-up resistors for PD2 and PD3
	
	sei();
}

ISR(INT0_vect) { // Triggered by changes on PD2 (phase B)
	phaseA = (PIND & (1 << PIND3)) >> PIND3; // Read phase A
	phaseB = (PIND & (1 << PIND2)) >> PIND2; // Read phase B
	
	if (phaseA == 1) {
		count--;
		} else {
		count++;
	}
	
}

ISR(INT1_vect) { // Triggered by changes on PD3 (phase A)
	phaseA = (PIND & (1 << PIND3)) >> PIND3; // Read phase A
	phaseB = (PIND & (1 << PIND2)) >> PIND2; // Read phase B
	
	if (phaseB == 1) {
		count++;
		} else {
		count--;
	}

	
}

#endif /* ENCODERINTERFACE_H_ */
