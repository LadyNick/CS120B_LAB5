/*	Author: Nicole Navarro
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment:LAB5 Challenge Exercise
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://youtu.be/NhltW3njE9M 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum light_states{init, inc_p, inc_r, dec_p, dec_r}light_state;

unsigned char A0;
unsigned char count;

void Tick(){
	switch(light_state){
		case init:
			if(A0){
				count = 0;
				light_state = inc_p;
			}
			break;
		case inc_p:
			if(count == 0){
				PORTB = 0X01;
			}
			else if(count == 1 ){
				PORTB = 0x03;
			}
			else if(count == 2){
				PORTB = 0x07;
			}
			else if(count == 3){
				PORTB = 0X0F;
			}
			else if(count == 4){
				PORTB = 0x1F;
			}
			else if(count == 5){
				PORTB = 0X3F;
			}
			if(!A0){
				++count;
				light_state = inc_r;
			}
			else{
				light_state = inc_p;
			}
			break;
		case inc_r:
			if(A0 && (count < 6)){
				light_state = inc_p;
			}
			else if(A0 && (count >= 6)){
				count = 0;
				light_state = dec_p;
			}
			else{
				light_state = inc_r;
			}
			break;
		case dec_p:
			if(count == 0){
				PORTB = 0x1f;
			}
			else if(count == 1){
				PORTB = 0x0f;
			}
			else if(count == 2){
				PORTB = 0x07;
			}
			else if(count == 3){
				PORTB = 0x03;
			}
			else if(count == 4){
				PORTB = 0x01;
			}
			else if(count == 5){
				PORTB = 0x00;
			}
			if(!A0){
				++count;
				light_state = dec_r;
			}
			else{
				light_state = dec_p;
			}
			break;
		case dec_r:
			if(A0 && (count < 6)){
				light_state = dec_p;
			}
			else if(A0 && (count >= 6)){
				count = 0;
				light_state = inc_p;
			}
			else{
				light_state = dec_r;
			}
			break;
		default:
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PINA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;

    /* Insert your solution below */

	light_state = init;
	count = 0;

    while (1){
	A0 = ~PINA & 0x01;
	Tick();


    }
    return 1;
}
