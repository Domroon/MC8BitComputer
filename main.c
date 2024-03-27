#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRD |= (1 << DDD4);
    DDRB |= (1 << DDB5);
    
    while(1){
        PORTD |= (1 << PORTD4);
        PORTB |= (1<< PORTB5);
        _delay_ms(500);
        PORTD = PORTD & ~(1 << PORTD4);
        PORTB &= ~(1<< PORTB5);
        _delay_ms(500);
    }
}
