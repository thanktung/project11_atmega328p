/*
 * MotorInterface.h
 *
 * Created: 9/30/2024 10:12:03 PM
 *  Author: Vuong Thanh Tung
 */ 


#ifndef MOTORINTERFACE_H
#define MOTORINTERFACE_H

#include <avr/io.h>

static inline void motor_init_pwm()
{
	// Set up Timer0 for PWM
	TCCR0A |= (1<<WGM01) | (1<<WGM00); // Waveform Generation Mode
	TCCR0B |= (1<<CS01) | (1<<CS00);   // Clock Select
	TCCR0A |= (1<<COM0A1);             // Non-inverting mode
	DDRD |= (1<<DDD6);                 // OC0A is output (PWM on PD6)
	
	// Set PD4 and PD5 as output for motor direction control
	DDRD |= (1<<DDD4) | (1<<DDD5);     // IN1 (PD4) and IN2 (PD5) as output
}

static inline void motor_set_pwm(uint8_t value)
{
	OCR0A = value; // Set PWM value
}

static inline void set_motor(int x)
{
	if (x > 0)
	{
		PORTD |= (1<<PORTD4);  // IN1 = 1
		PORTD &= ~(1<<PORTD5); // IN2 = 0
		motor_set_pwm(x);      // Set PWM to positive value
	}
	else if (x < 0)
	{
		PORTD &= ~(1<<PORTD4); // IN1 = 0
		PORTD |= (1<<PORTD5);  // IN2 = 1
		motor_set_pwm(-x);     // Set PWM to positive value (absolute of x)
	}
	else
	{
	
		PORTD &= ~(1<<PORTD4); // IN1 = 0
		PORTD &= ~(1<<PORTD5); // IN2 = 0
		motor_set_pwm(0);      // Set PWM to 0
	}
}

#endif // MOTORINTERFACE_H
