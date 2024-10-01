#ifndef F_CPU
#define F_CPU 16e6
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "MotorInterface.h"
#include "EncoderInterface.h"
#include "LCD1602Interface.h"

void button_init();
int check_button();

int main()
{
	motor_init_pwm();
	button_init();
	//Encoder
	//lcd
	
	int button_value = 0;
	int pwm = 250;

	while (1)
	{
		button_value = check_button();
		pwm += 10 * button_value;  // Adjust PWM based on button input
		// Limit PWM within the range of 0 to 255
		if (pwm > 255) {
			pwm = 255;
			} else if (pwm < 0) {
			pwm = 0;
		}
		
		set_motor(pwm);  // Set the new motor speed
	}

	return 0;
}

void button_init(){
	DDRB &= (~(1<<DDB1)) & (~(1<<DDB0));  // Set PB1 and PB0 as input
	PORTB |= (1<<PB1) | (1<<PB0);         // Enable pull-up resistors
}

int check_button(){
	int x = 0;
	
	if (!(PINB & (1 << PINB0))) {  // Check if button PB0 is pressed
		_delay_ms(100);              // Debounce delay
		x = -1;                    // Decrease PWM when PB0 is pressed
	}
	
	if (!(PINB & (1 << PINB1))) {  // Check if button PB1 is pressed
		_delay_ms(100);              // Debounce delay
		x = 1;                     // Increase PWM when PB1 is pressed
	}
	
	return x;
}
