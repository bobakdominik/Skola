/*
 * Morzeovka.cpp
 *
 * Author : bobak
 */ 

#include "Board.h"
#include "Led.h"
#include "Button.h"
#include "Display.h"
#include "Uart.h"
#include "Eeprom.h"
#include "Adc.h"
#include "Photo.h"
#include "Morse.h"

int main(void)
{
	cli();						//global interrupt disabled
	
	Led rgb;							// create object of class Led
	Display dsp;						// create object of class Display
	Uart uart;							// create object of class Uart
	Photo photo;						// create object of class photo
	Morse morse(&rgb, &uart, &photo);	// create object of class Morse
	Button btn(&morse);					// create object of class Button
	
	printf ("Press button to start!\r\n");
	while(!btn.isPressed()){}	// wait until btn is pressed
	
	btn.initInterrupt(fall);
	uart.initInterrupt();
	sei();						//global interrupt enabled
	
	int funID = 0; // function ID -> 0 == Out (Transmit), 1 == IN (Receive)
	dsp.show(funID);
	while (1)
	{
		if (morse.getStop())
		{
			morse.setStop(false);
			funID = (funID + 1)%2;
			dsp.show(funID);		//Show function id on display
			printf("\n\r");
			if (funID)
			{
				printf ("Receiving data... \r\n");
			} else
			{
				printf ("Transmitting data... \r\n");
			}
		}
		
		if (funID)
		{
			morse.ReceiveData();
		} else
		{
			morse.TransmitData();
		}
	}
}
