/* 
* Adc.h
*
* Author: bobak
*/


#ifndef __ADC_H__
#define __ADC_H__

#include "Board.h"

class Adc
{
//variables
public:
protected:
private:

//functions
public:
	Adc();
	~Adc();
	void init(uint8_t clock, bool mode);
	void setChannel(uint8_t channel);
	void setRef(uint8_t ref);
	int getAdc(void);
	uint8_t getAdc8(void);
protected:
private:


}; //Adc

#endif //__ADC_H__
