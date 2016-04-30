/**
 * Team: Tezpur University (NMK, PK, DS, ZB).
 * Two day workshop on Introduction to Robotics
 * organized by Tezpur University and e-Yantra, IIT Bombay.
 * */
//Switching the buzzer on and off indefinitely.
#define F_CPU 14745600
#include<avr/io.h>
#include<util/delay.h>

/**
 * Setting the required DDR bit.
 * This ensures that the pin is set for output.
*/
void buzzer_pin_config(){
	DDRC = DDRC | 0b0000100;
}

//Initially the buzzer will be turned off.
void buzzer_init(){
	PORTC = PORTC & 0b11110111;
}

void buzzer_off(){
	PORTC &= 0b11110111;	// same as PORTC = PORTC & 0b11110111;
}

void buzzer_on(){
	PORTC |= 0b00001000;	// same as PORTC = PORTC | 0b00001000;
}

void main(){
	buzzer_pin_config();
	buzzer_init();
	//This loop 
	while(1){
		buzzer_on();
		_delay_ms(200);
		buzzer_off();
		_delay_ms(1000);
	}
}
