#define F_CPU 14745600
#include<avr/io.h>
#include<util/delay.h>

void buzzer_pin_config(){
	DDRC = DDRC | 0b0000100;
}

void buzzer_init(){
	PORTC = PORTC & 0b11110111;
}

void buzzer_off(){
	PORTC = PORTC & 0b11110111;
}

void buzzer_on(){
	PORTC = PORTC | 0b00001000;
}

void main(){
	buzzer_pin_config();
	buzzer_init();
	
	while(1){
		buzzer_on();
		_delay_ms(200);
		buzzer_off();
		_delay_ms(1000);
	}
}
