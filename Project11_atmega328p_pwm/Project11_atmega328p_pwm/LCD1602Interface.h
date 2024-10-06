#ifndef LCD1602INTERFACE_H
#define LCD1602INTERFACE_H

#define F_CPU 16e6
#include <avr/io.h>
#include <util/delay.h>

#define LCD_Dir  DDRC
#define LCD_Port PORTC
#define RS PC0
#define EN PC1

void LCD_Command(unsigned char cmnd) {
	LCD_Port = (LCD_Port & 0x03) | ((cmnd & 0xF0) >> 2);
	LCD_Port &= ~(1 << RS);
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~(1 << EN);
	_delay_us(200);
	
	LCD_Port = (LCD_Port & 0x03) | ((cmnd & 0x0F) << 2);
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~(1 << EN);
	_delay_ms(2);
}

void LCD_Char(unsigned char data) {
	LCD_Port = (LCD_Port & 0x03) | ((data & 0xF0) >> 2);
	LCD_Port |= (1 << RS);
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~(1 << EN);
	_delay_us(200);
	
	LCD_Port = (LCD_Port & 0x03) | ((data & 0x0F) << 2);
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~(1 << EN);
	_delay_ms(2);
}

void LCD_Init(void) {
	LCD_Dir = 0xFF;
	_delay_ms(20);
	
	LCD_Command(0x02);
	LCD_Command(0x28);
	LCD_Command(0x0c);
	LCD_Command(0x06);
	LCD_Command(0x01);
	_delay_ms(2);
}

void LCD_String(char *str) {
	for (int i = 0; str[i] != 0; i++) {
		LCD_Char(str[i]);
	}
}

void LCD_String_xy(char row, char pos, char *str) {
	if (row == 0 && pos < 16)
	LCD_Command((pos & 0x0F) | 0x80);
	else if (row == 1 && pos < 16)
	LCD_Command((pos & 0x0F) | 0xC0);
	LCD_String(str);
}

void LCD_Clear(void) {
	LCD_Command(0x01);
	_delay_ms(2);
	LCD_Command(0x80);
}

#endif /* LCD1602INTERFACE_H */
