/*	Author: lab
 *  Partner(s) Name: 
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

enum States {Start, initialLights, buttonWait1, switchedLights, buttonWait2} State; 
unsigned char tmpA;
unsigned char tmpB;

void TickFct(){
    switch(State){
        case Start:
            State = initialLights;
            break;

        case initialLights:
            if((tmpA & 0x01) == 0x00){
                State = buttonWait1;
            }else{
                State = initialLights;
            }

        case buttonWait1:
            if((tmpA & 0x01) == 0x01){
                State = switchedLights;
            }else{
                State = buttonWait1;
            }
            break;

        case switchedLights:
            if((tmpA & 0x01) == 0x00){
                State = buttonWait2;
            }else{
                State = switchedLights;
            }
            break;

        case buttonWait2:
            if((tmpA & 0x01) == 0x01){
                State = initialLights;
            }else{
                State = buttonWait2;
            }
            break;
        
        default:
            State = initialLights;
            break;
    }

        switch(State){
            case initialLights:
                tmpB = (tmpB | 0x01);
                break;

            case buttonWait1:
                break;

            case switchedLights:
                tmpB = (tmpB | 0x02);
                break;

            case buttonWait2:
                break;

            default:
                tmpB = (tmpB | 0x01);
        }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    State = Start;
    while (1) {
        tmpA = PINA;
        TickFct();
        PORTB = tmpB;
    }
    return 1;
}
