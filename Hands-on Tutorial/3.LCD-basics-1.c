#define F_CPU 14745600

#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"
//Hitachi HD44780 LCD
void clear_line(int n)
{
	lcd_cursor(n,1);
	lcd_string("                ");
}

int main(){
	lcd_init();
	lcd_cursor(1, 1);
	lcd_string("Tezpur University");
	while(1){
		lcd_cursor(2, 4);
		lcd_string("ECE");
		_delay_ms(500);
		clear_line(2);
		lcd_cursor(2, 4);
		lcd_string("CSE");
		_delay_ms(500);
		clear_line(2);
		lcd_cursor(2, 4);
		lcd_string("Mech");
		_delay_ms(500);
		clear_line(2);
		/*Rote solution for clearing!!
		//lcd_wr_command(0x01);
		//lcd_cursor(1, 1);
		//lcd_string("Tezpur University");
		*/

		}
	return 0;
}
