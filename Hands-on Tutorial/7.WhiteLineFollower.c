#define F_CPU 14745600

#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"

int values[3];

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


///using TIMER
void timer5_init(){
	TCCR5A = 0xa9;
	TCCR5B = 0x0b;
	TCNT5L = 0x00;
	OCR5AL = 0xff;
	OCR5BL = 0xff;
}

void velocity(unsigned char left_vel, unsigned char right_vel){
	OCR5AL = left_vel;
	OCR5BL = right_vel;
}

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
	DDRL = DDRL | 0b00011000;   //two pins of port L are connected to IC enable pins.
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

int isWhiteOrBlack(int value){
	if(value < 40)
		return 1;
	else
		return 0;
}

int findCurrentState(){
	if(values[0] ==0 && values[1] == 1 && values[2] == 0)
		return 1;
	else 	if(values[0] ==1 && values[1] == 1 && values[2] == 0)
		return 2;
	else 	if(values[0] ==0 && values[1] == 1 && values[2] == 1)
		return 3;
	else 	if(values[0] ==0 && values[1] == 0 && values[2] == 1)
		return 4;
	else if(values[0] ==1 && values[1] == 0 && values[2] == 0)
		return 5;
	return -1;
}

int main(){

	unsigned char currentState;

	buzzer_pin_config();
	buzzer_init();

	lcd_init();
	adc_port_config();
	adc_init();
	
	timer5_init();
	motor_pin_config();
	motor_init();
	
	while(1){
		values[0] = isWhiteOrBlack(adc_conversion(1));
		values[1] = isWhiteOrBlack(adc_conversion(2));
		values[2] = isWhiteOrBlack(adc_conversion(3));
		lcd_print(1, 1, values[2], 3);
		lcd_print(1, 6, values[1], 3);
		lcd_print(1, 13, values[0], 3);
		currentState = findCurrentState();
		switch(currentState) {
			case 1  : //Forward
				velocity(180, 180);				   		
				forward();
				break; 
			case 2:	//SoftRight
				velocity(180, 120);				   		
				forward();
				break;
 			case 3: //Left
				velocity(120, 180);				   		
				forward();
				break;
			case 4: //FastLeft
				velocity(120, 180);				   		
				forward();
				break;
			case 5: //RightFast
				velocity(180, 120);				   		
				forward();
				break;
			//default:
				//stop();
			}
			if(adc_conversion(11) > 80){
					stop();
					buzzer_on();
					_delay_ms(200);
					buzzer_off();
			}
	}
		
	return 0;
}
