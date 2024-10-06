#ifndef F_CPU
#define F_CPU 16e6
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "MotorInterface.h"
#include "EncoderInterface.h"
#include "LCD1602Interface.h"

void button_init();
int check_button();

int main()
{
	motor_init_pwm();
	button_init();
	LCD_Init();

	int button_value = 0;
	int pwm = 250;
	int speed = 0;          // Assuming you will calculate or get the motor speed
	char pwm_str[10];
	char speed_str[10];

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

		itoa(pwm, pwm_str, 10);    // Convert PWM to string
		speed = 50; // Function to get motor speed (assumed)
		itoa(speed, speed_str, 10); // Convert speed to string

		// Display PWM on LCD (first line)
		LCD_String_xy(0, 0, "PWM: ");
		LCD_String_xy(0, 5, pwm_str);  // Display PWM value at position 5

		// Display Speed on LCD (second line)
		LCD_String_xy(1, 0, "SPEED: ");
		LCD_String_xy(1, 7, speed_str);  // Display speed value at position 7

		_delay_ms(100);  // Small delay to avoid rapid button presses
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
		_delay_ms(100);            // Debounce delay
		x = -1;                    // Decrease PWM when PB0 is pressed
	}
	
	if (!(PINB & (1 << PINB1))) {  // Check if button PB1 is pressed
		_delay_ms(100);            // Debounce delay
		x = 1;                     // Increase PWM when PB1 is pressed
	}
	
	return x;
}
