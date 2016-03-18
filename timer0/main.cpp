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
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "uart.h"

#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1

//static unsigned char sPORTB = 0;


USART uart(BAUD, 1);

void setup()
{
  //uart = new UART();
  // Setting pin0 as output
  DDRB = (1 << DDB0);
  // Enabling pull up on PORTB1
  PORTB = (1 << PORTB1);
  //PORTB = sPORTB;
  
  //uart.USART_Init(BAUD, 1);
  TIMSK |= 1 << TOIE0;
  //Global interrupts enable
  sei();
  //Prescaled to clk/1024
  TCCR0 = (1 << CS02 | 0 << CS01 | 1 << CS00);
}

ISR(TIMER0_OVF_vect)
{
  PORTB = 1 << PORTB0;
}

int main(void)
{
  //const char *str = "TEST STRING\n";
  char buffer[15];
  setup();
  
  for(;;){
    
    //if(PINB & (1 << PINB1)){
     //PORTB &= (0 << PORTB0 | 1 << PORTB1);
    //}else{
     //_delay_ms(200);
     //PORTB |= (1 << PORTB0 | 1 << PORTB1);
     //_delay_ms(200);
    //}
    //PORTB = 1 << PORTB0;
    
    //USART_Transmit('X');
     unsigned int timer0 = TCNT0;
     //uart.printstr(str);
     itoa(timer0, buffer, 10);
     uart.printstr( buffer );
     uart.printstr( "\n" );
     _delay_ms(100);
    
    //PORTB = sPORTB;
  }

  return 0;
}


