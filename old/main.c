#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void){
    DDRD |= (1 << DDD4);                // set GPIO D4 as Output
    DDRB |= (1 << DDB5);                // set GPIO B5 as Output

    DDRD |= ~(1 << DDD2);               // set GPIO D2 as Input
    EICRA |= (1 << ISC01);              // The falling edge of INT0 generates an interrupt request.
    EIMSK |= (1 << INT0);               // External Interrupt Request 0 Enable
    sei();                              // Enable Interrupts Global

    while(1){
        PORTD |= (1 << PORTD4);            
        PORTB |= (1<< PORTB5);          // set GPIO D4 and B5 HIGH
        _delay_ms(500);
        PORTD = PORTD & ~(1 << PORTD4); 
        PORTB &= ~(1<< PORTB5);         // set GPIO D4 and B5 LOW
        _delay_ms(500);
    }
}