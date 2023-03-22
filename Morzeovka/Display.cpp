/* 
* Display.cpp
*
* Author: bobak
*/


#include "Display.h"

// default constructor
Display::Display()
{
	/* Set as outputs */
	sbi(DDRC,SER);
	sbi(DDRC,OE);
	sbi(DDRD,RCLK);
	sbi(DDRB,SRCLK);
	show(18);
} //Display

// default destructor
Display::~Display()
{
} //~Display

void Display::show(uint8_t character)
{
	uint8_t result;
	character= character & 0x1f;
	switch(character)
	{
		case 0: result=zero; break;
		case 1: result=one; break;
		case 2: result=two; break;
		case 3: result=three; break;
		case 4: result=four; break;
		case 5: result=five; break;
		case 6: result=six; break;
		case 7: result=seven; break;
		case 8: result=eight; break;
		case 9: result=nine; break;
		case 10: result=ahex; break;
		case 11: result=bhex; break;
		case 12: result=chex; break;
		case 13: result=dhex; break;
		case 14: result=ehex; break;
		case 15: result=fhex; break;
		case 16: result=dot; break;
		case 17: result=err; break;
		case 18: result=non; break;
		default: result=non;
	}	
	this->display(result);			// display(result)
}

/* private method */
void Display::display(uint8_t character)
{
	sbi(PORTC,OE);				// set output to HI (high impedance)
	for(uint8_t i=0;i<8;i++)
	{
		if((character & 0b10000000)==0b10000000) sbi(PORTC,SER);else cbi(PORTC,SER);	//data
		sbi(PORTB,SRCLK);
		cbi(PORTB,SRCLK);	// clock
		character=character<<1;
	}
	sbi(PORTD,RCLK);		//	transcript from shift register to memory
	cbi(PORTD,RCLK);		//  impulse
	cbi(PORTC,OE);			//	set output
}

void Display::circle()
{
	uint8_t pom =0b00000001;
	for (uint8_t i=0 ; i<6; i++)
	{
		display(pom);
		_delay_ms(80);
		pom = pom<<1;
	}
}