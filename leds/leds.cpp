#include <avr/io.h>
#include <util/delay.h>

#define GREEN_LED   0
#define YELLOW_LED  1
#define RED_LED     2

int main(void)
{
    DDRB = (1 << GREEN_LED) | (1 << YELLOW_LED) | (1 << RED_LED);
    PORTB = 0x00;
    while(1){
        PORTB = (1 << GREEN_LED);
        _delay_ms(200);
        PORTB = (1 << YELLOW_LED);
        _delay_ms(200);
        PORTB = (1 << RED_LED);
        _delay_ms(200);
    }

    return 0;
}
