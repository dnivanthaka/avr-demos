/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301, USA.
 
 ---
 Copyright (C) 2016, Dinusha Nivanthaka Amerasinghe <nivanthaka@gmail.com>
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "uart.h"

void USART::printstr(const char *str)
{
    while(*str){
        if(*str == '\n')
            transmit('\r'); 
        transmit(*str++);        
    }
}

/*
void USART_Init(unsigned int ubrr)
{
    // Setting baud rate
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    //Enable receiver and transmitter
    UCSRB = (1 << RXEN) | (1 << TXEN);
    // Setting frame format, 8bit data, 1stop bit
    //UCSRC = (1 << USBS) | (3 << UCSZ0);
    //UCSRC = (0 << USBS) | (3 << UCSZ0);
    UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}
*/

USART::USART(unsigned int baudrate, unsigned char parity_bits)
{
    unsigned int ubrr = (F_CPU/16/baudrate) - 1;

    // Setting baud rate
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    //Enable receiver and transmitter
    UCSRB = (1 << RXEN) | (1 << TXEN);
    
    if(parity_bits == 1){
        // Setting frame format, 8bit data, 1stop bit
        UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
    }else if(parity_bits == 2){
        // Setting frame format, 8bit data, 2stop bit
        UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1)|(1 << USBS);
    }
}

void USART::transmit(unsigned char data)
{
    while( !(UCSRA & (1 << UDRE)) );
    UDR = data;
}

unsigned char USART::receive(void)
{
    while( !(UCSRA & (1 << RXC)) );
    return UDR;
}
