/* 
* Adc.cpp
*
* Author: bobak
*/


#include "Adc.h"

// default constructor
Adc::Adc()
{
	cbi(PRR,PRADC);							/* enable ADC */
} 

// default destructor
Adc::~Adc()
{
	sbi(PRR,PRADC);							/* disable ADC */
}

void Adc::init(uint8_t clock, bool mode)
{
	clock=clock&0x7;						/* ADC prescaler select ADPS[2:0] , <0;7>	*/								
	ADCSRA = 0b10000000|clock;				/* ADEN, ADSC, ADATE, ADIF, ADIE,ADPS2, ADPS1, ADPS0 */
	if(mode) sbi(ADCSRA,ADATE);				/* ADATE: autotriger; */
		
}

void Adc::setChannel(uint8_t channel)		/* Channel 0 - F */
{
	channel &= 0x0F;						/* only 0-15 */
	ADMUX &= 0xF0;							/* clear 4 lower bits */
	ADMUX |= channel;						/* set channel */
}

void Adc::setRef(uint8_t ref)
{
	ref=ref & 0b00000011;					/* mask (only values : <0;3>), 0=AREF, 1=AVcc, 2=reserved, 3=internal 1.1V reference voltage  */
	ADMUX &= 0b00111111;					/* clear 2 upper bits (REFS1 , REFS0) */
	ADMUX |= (ref<<6);						/* set reference voltage */
}

int Adc::getAdc(void)
{
	cbi(ADMUX,ADLAR);						/* ADLAR=0   result is right adjusted */
	sbi(ADCSRA, ADSC);						/* start conversion */
	while((ADCSRA & (1<<ADIF))!=(1<<ADIF)){}; /* waiting for the end of conversion */
	int prev = ADCL;						/* 8 lower bits */
	prev |=ADCH<<8;							/* 2 upper bits */
	sbi(ADCSRA,ADIF);						/*ADIF is cleared by writing a logic. 1 */
	return prev;
}

uint8_t Adc::getAdc8(void)
{
	sbi(ADMUX, ADLAR);						/* result is left adjusted */
	sbi(ADCSRA, ADSC);						/* start conversion */		
	while((ADCSRA & (1<<ADIF))!=(1<<ADIF)){};
	uint8_t pom=ADCH;
	sbi(ADCSRA,ADIF);						/*ADIF is cleared by writing a logic. 1 */
	return pom;
}