#define F_CPU 14745600

#include<avr/io.h>
#include<util/delay.h>

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
	motor_pin_config();
	motor_init();
	while(1){
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
	}
	return 0;
}
