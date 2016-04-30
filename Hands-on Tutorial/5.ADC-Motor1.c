#define F_CPU 14745600

#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"

void adc_port_config(){
	DDRF = 0x00;
	DDRK = 0x00;
}

void adc_init(){
	ADCSRA = 0x86;
	ADCSRB = 0x00;
	ADMUX = 0x20;
	ACSR = 0x80;
}

unsigned char adc_conversion(unsigned char channel){
	if(channel > 7)
		ADCSRB |= 0x08;

	ADMUX |= (channel & 0x07);

	//Start conversion: S6 bit
	ADCSRA |= 0x40;

	//Wait while interrupt flag is 0
	//(0 means end of conversion)
	while((ADCSRA & 0x10) == 0)
		;
	unsigned char my_mobile = ADCH;
	adc_init();
	return my_mobile;
}



void motor_pin_config(){
	DDRA = DDRA | 0b00001111;
	DDRL = DDRL | 0b00011000;   //2 pins of port L are connected to IC enable pins.
}

void motor_init(){
	PORTL = PORTL | 0b00011000;
	PORTA = PORTA & 0b11110000;
}

void forward(){
	PORTA = 0b00000110;
}

void backard(){
	PORTA = 0b00001001;
}

void rotateleft(){
	PORTA = 0b00000101;
}

void rotateright(){
	PORTA = 0b00001010;
}

void backward(){
	PORTA = 0b00001001;
}

void stop(){
	PORTA = 0b00000000;
}


int main(){
	int value = 0;
	lcd_init();
	adc_port_config();
	adc_init();

	motor_pin_config();
	motor_init();
	while(1){
		value = adc_conversion(11);
		lcd_print(1, 6, value, 3);
		if(value > 80)
			forward();
		else
			backward();
		_delay_ms(150);
	/*
		forward();
		_delay_ms(500);
		stop();
		_delay_ms(500);
		rotateleft();
		_delay_ms(500);
		rotateright();
		_delay_ms(500);
		backward();
		_delay_ms(500);
		*/
	}
	return 0;
}
