#include <avr/io.h>
#include <util/delay.h>

#define RELAY1   0
#define RELAY2   1

int main(void)
{
    DDRB = (1 << RELAY1) | (1 << RELAY2);
    PORTB = 0x00;
    while(1){
        //Relay 1 ON Relay 2 OFF
        PORTB |= (1 << RELAY1);
        PORTB &= ~(1 << RELAY2);
        _delay_ms(500);
        
        //Relay 1 OFF Relay 2 ON
        PORTB &= ~(1 << RELAY1);
        PORTB |= (1 << RELAY2);
        _delay_ms(500);
    }

    return 0;
}
