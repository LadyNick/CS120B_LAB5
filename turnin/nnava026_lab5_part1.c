/*	Author: lab
 *  Partner(s) Name: N/A
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void) {
    DDRA = 0x00; PINA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char tmpC = 0x00;
    unsigned char tmpA = 0x00;

    while (1) {

	tmpA = PINA & 0x0f;	    


	if(tmpA > 0x00){
		tmpC = 0x01;
		tmpC = tmpC << 5;
	}
	if(tmpA > 0x02){
		tmpC = tmpC + 0x10;
	}
	if(tmpA > 0x04){
		tmpC = tmpC + 0x08;
	}
	if(tmpA > 0x06){
		tmpC = tmpC + 0x04;
	}
	if(tmpA > 0x09){
		tmpC = tmpC + 0x02;
	}
	if(tmpA > 0x0C){
		tmpC = tmpC + 0x01;
	}
	if(tmpA <= 0x04){
		tmpC = tmpC | (0x01 << 6);
	}

	PORTC = tmpC;

    }
    return 1;
}
