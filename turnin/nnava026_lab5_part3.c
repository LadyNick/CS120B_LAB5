/*	Author: Nicole Navarro
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment:
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum light_states{init, odd_p, odd_r, even_p, even_r}light_state;

unsigned char A0;

void Tick(){
	switch(light_state){
		case init:
			if(A0){
				light_state = odd_p;
			}
			else{
				light_state = init;
			}
			break;
		case odd_p:
			PORTB = 0x55;
			if(!A0){
				light_state = odd_r;
			}
			else{
				light_state = odd_p;
			}
			break;
		case odd_r:
			if(A0){
				light_state = even_p;
			}
			else{
				light_state = odd_r;
			}
			break;
		case even_p:
			PORTB = 0xAA;
			if(!A0){
				light_state = even_r;
			}
			else{
				light_state = even_p;
			}
			break;
		case even_r:
			if(A0){
				light_state = odd_p;
			}
			else{
				light_state = even_r;
			}
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PINA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;

    /* Insert your solution below */

	light_state = init;

    while (1){
	A0 = ~PINA & 0x01;
	Tick();


    }
    return 1;
}
