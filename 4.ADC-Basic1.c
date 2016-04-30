#define F_CPU 14745600

#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"
//Hitachi HD44780 LCD

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

int main(){
	lcd_init();
	adc_port_config();
	adc_init();
	while(1){
		//11 is the channel number
		lcd_print(1, 6, adc_conversion(11), 3);
		_delay_ms(500);
	}
	
}
