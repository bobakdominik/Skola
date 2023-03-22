/* 
* Photo.cpp
*
* Author: bobak
*/


#include "Photo.h"

// default constructor
Photo::Photo()
{
} //Photo

// default destructor
Photo::~Photo()
{
} //~Photo

int Photo::get_value(void)
{
	this->init(4,false);		// divider 16 (ADPS[2:0]=0b100), one conversion
	this->setChannel(0);		// set channel 0 [PC0 = ADC0]
	this->setRef(1);			// AVcc
	_delay_ms(1);
	return(this->getAdc());
}