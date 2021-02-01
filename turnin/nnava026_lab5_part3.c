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
#include "RIMS.h"
#endif

enum light_states{init, blinkslow1, blinkslow2 blinknorm1, blinknorm2, switchseq1, switchseq2}light_state;

unsigned char count = 1;
unsigned char slowcount = 0;
volatile unsigned char TimerFlag = 0;
void TimerISR() {TimerFlag = 1;}

void Tick(){
	switch(light_state){
		case init:
			slowcount = 0;
			count = 1;
			light_state = blinkslow1;
			break;
		case blinkslow1:
			PORTB = 0XFF;
			++slowcount;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = blinknorm1;
			}
			if(slowcount == 2){
				slowcount = 0;
				light_state = blinkslow2;
			}
			else{
				light_state = blinkslow1;
			}
			break;
		case blinkslow2:
			PORTB = 0X00;
			++slowcount;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = blinknorm1;
			}
			if(slowcount == 2){
				slowcount = 0;
				light_state = blinkslow1;
			}
			else{
				light_state = blinkslow2;
			}
			break;
		case blinknorm1:
			PORTB = 0XFF;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = switchseq1;
			}
			light_state = blinknorm2;
			break;
		case blinknorm2:
			PORTB = 0X00;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = switchseq1;
			}
			light_state = blinknorm1;
			break;
		case switchseq1:
			PORTB = 0X15;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = blinkslow1;
			}
			light_state = switchseq2;
			break;
		case switchseq2:
			PORTB = 0X2A;
			if(!A0){
				++count;
			}
			else if(A0 && (count != 0)){
				count = 0;
				light_state = blinkslow1;
			}
			light_state = switchseq2;
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PINA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;

    /* Insert your solution below */

	light_state = light_states;
	TimerSet(1000);
	TimerOn();
	count = 1;
	slowcount = 0;

    while (1){
	Tick();
	    while(!TimerFlag){}
	    TimerFlag = 0;

    }
    return 1;
}
