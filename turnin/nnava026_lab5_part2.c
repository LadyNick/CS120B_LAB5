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

enum count_states{init, inc_p, inc_r, dec_p, dec_r, reset_p, reset_r, release} count_state;

//unsigned char not_pina;
unsigned char A0;
unsigned char A1;

void Tick_Count(){
	switch (count_state){
		case init:
			if( A0 && !A1 ){
				count_state = inc_p;
			}
			else if( !A0 && A1){
				count_state = dec_p;
			}
			else if( A0 && A1 ){
				count_state = reset_p;
			}
			else{
				count_state = init;
			}
			break;
		case inc_p:
			if( A0 && A1 ){
				count_state = reset_p;
			}
			else{
				count_state = inc_r;
			}
			break;
		case inc_r: 
			if( A0 && A1 ){
				count_state = reset_p;
			}
			else if( A0 && !A1 ){
				count_state = inc_r;
			}
			else if( !A0 && !A1 ){
				count_state = release;
			}
			break;
		case dec_p:
			if( A0 && A1 ) {
				count_state = reset_p;
			}
			else{
				count_state = dec_r;
			}
			break;
		case dec_r:
			if(A0 && A1 ){
				count_state = reset_p;
			}
			else if( A1 && !A0){
				count_state = dec_r;
			}
			else if( !A1 && !A0){
				count_state = release;
			}
		case reset_p:
			count_state = reset_r;
			break;
		case reset_r:
			if( !A0 && !A1 ){
				count_state = release;
			}
			else{
				count_state = reset_r;
			}
			break;
		case release:
			if( A0 && !A1 ){
                                count_state = inc_p;
                        }
                        else if( !A0  && A1){
                                count_state = dec_p;
                        }
                        else if( A0 && A1 ){
                                count_state = reset_p;
                        }
			else{
				count_state = release;	
			}
                        break;
		default:
			count_state = init;
	}

	switch (count_state){
		default:
			break;
		case init:
			PORTC = 0x07;
			break;
		case inc_p:
			if((PORTC < 0x09)){
				PORTC = PORTC + 1;
			}
			break;
		case dec_p:
			if((PORTC > 0)){
				PORTC = PORTC - 1;
			}
			break;
		case reset_p:
			PORTC = 0x00;
			break;
	}
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PINA = 0xFF;

    /* Insert your solution below */
	PORTC = 0x07;
	count_state = init;
	PORTC = 0x07;
	
    while (1){
	//not_pina = ~PINA;
	A0 = (~PINA & 0x01);
	A1 = (~PINA & 0x02) > 0;

	Tick_Count();
    }
    return 1;
}
